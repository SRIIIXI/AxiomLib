/*
  tinyxml_c.c - Minimal DOM XML parser in pure C
  Works with tinyxml_c.h
  Suitable for embedded systems.
*/

#include "xml.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---------------- Internal Structures ---------------- */

typedef struct XMLAttribute
{
    char *name;
    char *value;
    struct XMLAttribute *next;
} XMLAttribute;

struct XMLNode
{
    XMLNodeType type;
    char *name;                  /* element name (NULL for text nodes) */
    char *text;                  /* text content for text/cdata/comment */
    XMLAttribute *attr;          /* linked list of attributes */
    struct XMLNode *parent;
    struct XMLNode *firstChild;
    struct XMLNode *nextSibling;
};

struct XMLDocument
{
    XMLNode *root;               /* Document node as container */
};

/* ---------------- Helpers ---------------- */

static char *xstrndup(const char *s, size_t n)
{
    char *p = (char*)malloc(n + 1);
    if (!p) return NULL;
    memcpy(p, s, n);
    p[n] = '\0';
    return p;
}

static char *xstrdup(const char *s)
{
    return s ? xstrndup(s, strlen(s)) : NULL;
}

static void skip_ws(const char **p)
{
    while (**p && isspace((unsigned char)**p))
    {
        (*p)++;
    }
}

static int is_name_char(char c)
{
    return (isalnum((unsigned char)c) || c == '_' || c == ':' || c == '-' || c == '.');
}

static char *parse_name(const char **p)
{
    const char *s = *p;
    if (!is_name_char(*s)) return NULL;
    const char *start = s++;
    while (*s && is_name_char(*s)) s++;
    *p = s;
    return xstrndup(start, s - start);
}

static char *unescape_entities(const char *src)
{
    if (!src) return NULL;
    size_t n = strlen(src);
    char *out = (char*)malloc(n + 1);
    if (!out) return NULL;

    const char *s = src;
    char *d = out;
    while (*s)
    {
        if (*s == '&')
        {
            if (strncmp(s, "&amp;", 5) == 0) { *d++ = '&'; s += 5; }
            else if (strncmp(s, "&lt;", 4) == 0) { *d++ = '<'; s += 4; }
            else if (strncmp(s, "&gt;", 4) == 0) { *d++ = '>'; s += 4; }
            else if (strncmp(s, "&quot;", 6) == 0) { *d++ = '"'; s += 6; }
            else if (strncmp(s, "&apos;", 6) == 0) { *d++ = '\''; s += 6; }
            else { *d++ = *s++; }
        }
        else
        {
            *d++ = *s++;
        }
    }
    *d = '\0';

    char *res = xstrdup(out);
    free(out);
    return res;
}

/* ---------------- Node Management ---------------- */

static XMLNode *node_new(XMLNodeType type)
{
    XMLNode *n = (XMLNode*)malloc(sizeof(XMLNode));
    if (!n) return NULL;
    n->type = type;
    n->name = NULL;
    n->text = NULL;
    n->attr = NULL;
    n->parent = NULL;
    n->firstChild = NULL;
    n->nextSibling = NULL;
    return n;
}

static void node_append_child(XMLNode *parent, XMLNode *child)
{
    if (!parent->firstChild)
    {
        parent->firstChild = child;
    }
    else
    {
        XMLNode *c = parent->firstChild;
        while (c->nextSibling) c = c->nextSibling;
        c->nextSibling = child;
    }
    child->parent = parent;
}

static void free_attrs(XMLAttribute *a)
{
    while (a)
    {
        XMLAttribute *n = a->next;
        free(a->name);
        free(a->value);
        free(a);
        a = n;
    }
}

static void free_node(XMLNode *n)
{
    if (!n) return;
    free(n->name);
    free(n->text);
    free_attrs(n->attr);

    XMLNode *c = n->firstChild;
    while (c)
    {
        XMLNode *nx = c->nextSibling;
        free_node(c);
        c = nx;
    }
    free(n);
}

/* ---------------- Parsing ---------------- */

static char *parse_quoted_value(const char **p)
{
    skip_ws(p);
    if (**p != '"' && **p != '\'') return NULL;
    char q = *(*p)++;
    const char *start = *p;
    while (**p && **p != q) (*p)++;
    const char *end = *p;
    if (**p == q) (*p)++;

    char *raw = xstrndup(start, end - start);
    char *un = unescape_entities(raw);
    free(raw);
    return un;
}

static void node_add_attr(XMLNode *node, char *name, char *value)
{
    XMLAttribute *a = (XMLAttribute*)malloc(sizeof(XMLAttribute));
    a->name = name;
    a->value = value;
    a->next = node->attr;
    node->attr = a;
}

static int parse_attributes(const char **p, XMLNode *node)
{
    for (;;)
    {
        skip_ws(p);
        if (**p == '>' || **p == '/' || !**p) break;
        char *name = parse_name(p);
        if (!name) return 0;
        skip_ws(p);
        if (**p != '=')
        {
            free(name);
            return 0;
        }
        (*p)++;
        char *value = parse_quoted_value(p);
        if (!value)
        {
            free(name);
            return 0;
        }
        node_add_attr(node, name, value);
    }
    return 1;
}

static int parse_node(const char **p, XMLNode *parent);

static int parse_element(const char **p, XMLNode *parent)
{
    (*p)++;
    char *ename = parse_name(p);
    if (!ename) return 0;

    XMLNode *elem = node_new(XML_NODE_ELEMENT);
    elem->name = ename;

    if (!parse_attributes(p, elem))
    {
        free_node(elem);
        return 0;
    }

    skip_ws(p);

    if (**p == '/' && *(*p + 1) == '>')
    {
        *p += 2;
        node_append_child(parent, elem);
        return 1;
    }

    if (**p == '>')
    {
        (*p)++;
        node_append_child(parent, elem);
        if (!parse_node(p, elem)) return 0;
        return 1;
    }

    free_node(elem);
    return 0;
}

static int parse_node(const char **p, XMLNode *parent)
{
    while (**p)
    {
        skip_ws(p);

        if (**p == '<' && *(*p + 1) == '/')
        {
            *p += 2;
            while (**p && **p != '>') (*p)++;
            if (**p == '>') (*p)++;
            return 1;
        }
        else if (**p == '<')
        {
            if (strncmp(*p, "<!--", 4) == 0)
            {
                const char *end = strstr(*p + 4, "-->");
                if (!end) return 0;
                char *txt = xstrndup(*p + 4, end - (*p + 4));
                XMLNode *n = node_new(XML_NODE_COMMENT);
                n->text = txt;
                node_append_child(parent, n);
                *p = end + 3;
            }
            else if (strncmp(*p, "<![CDATA[", 9) == 0)
            {
                const char *end = strstr(*p + 9, "]]>");
                if (!end) return 0;
                char *txt = xstrndup(*p + 9, end - (*p + 9));
                XMLNode *n = node_new(XML_NODE_CDATA);
                n->text = txt;
                node_append_child(parent, n);
                *p = end + 3;
            }
            else if (strncmp(*p, "<?", 2) == 0)
            {
                const char *end = strstr(*p + 2, "?>");
                if (!end) return 0;
                *p = end + 2;
            }
            else
            {
                if (!parse_element(p, parent)) return 0;
            }
        }
        else
        {
            const char *start = *p;
            while (**p && **p != '<') (*p)++;
            char *raw = xstrndup(start, *p - start);

            int onlyws = 1;
            for (char *t = raw; *t; t++)
            {
                if (!isspace((unsigned char)*t))
                {
                    onlyws = 0;
                    break;
                }
            }

            if (!onlyws)
            {
                XMLNode *n = node_new(XML_NODE_TEXT);
                n->text = unescape_entities(raw);
                node_append_child(parent, n);
            }
            free(raw);
        }
    }
    return 1;
}

/* ---------------- Public API ---------------- */

XMLDocument *xml_parse_string(const char *input)
{
    if (!input) return NULL;
    const char *p = input;
    XMLDocument *doc = (XMLDocument*)malloc(sizeof(XMLDocument));
    if (!doc) return NULL;

    doc->root = node_new(XML_NODE_DOCUMENT);

    if (strncmp(p, "<?xml", 5) == 0)
    {
        const char *end = strstr(p, "?>");
        if (end) p = end + 2;
    }

    if (!parse_node(&p, doc->root))
    {
        xml_free_document(doc);
        return NULL;
    }
    return doc;
}

static char *read_file_all(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = (char*)malloc(sz + 1);
    if (!buf)
    {
        fclose(f);
        return NULL;
    }

    if (fread(buf, 1, sz, f) != (size_t)sz)
    {
        free(buf);
        fclose(f);
        return NULL;
    }

    buf[sz] = '\0';
    fclose(f);
    return buf;
}

XMLDocument *xml_load_file(const char *path)
{
    char *s = read_file_all(path);
    if (!s) return NULL;
    XMLDocument *d = xml_parse_string(s);
    free(s);
    return d;
}

void xml_free_document(XMLDocument *doc)
{
    if (!doc) return;
    free_node(doc->root);
    free(doc);
}

XMLNode *xml_node_first_child_element(XMLNode *node, const char *name)
{
    if (!node) return NULL;
    XMLNode *c = node->firstChild;
    while (c)
    {
        if (c->type == XML_NODE_ELEMENT && (!name || (c->name && strcmp(c->name, name) == 0)))
        {
            return c;
        }
        c = c->nextSibling;
    }
    return NULL;
}

XMLNode *xml_node_next_sibling_element(XMLNode *node, const char *name)
{
    if (!node) return NULL;
    XMLNode *c = node->nextSibling;
    while (c)
    {
        if (c->type == XML_NODE_ELEMENT && (!name || (c->name && strcmp(c->name, name) == 0)))
        {
            return c;
        }
        c = c->nextSibling;
    }
    return NULL;
}

XMLNode *xml_node_parent(XMLNode *node)
{
    return node ? node->parent : NULL;
}

XMLNodeType xml_node_type(XMLNode *node)
{
    return node ? node->type : XML_NODE_DOCUMENT;
}

const char *xml_node_name(XMLNode *node)
{
    return (node && node->type == XML_NODE_ELEMENT) ? node->name : NULL;
}

const char *xml_node_get_attr(XMLNode *node, const char *name)
{
    if (!node || !name) return NULL;
    XMLAttribute *a = node->attr;
    while (a)
    {
        if (strcmp(a->name, name) == 0) return a->value;
        a = a->next;
    }
    return NULL;
}

const char *xml_node_get_text(XMLNode *node)
{
    if (!node) return NULL;
    XMLNode *c = node->firstChild;
    while (c)
    {
        if (c->type == XML_NODE_TEXT || c->type == XML_NODE_CDATA)
        {
            return c->text;
        }
        c = c->nextSibling;
    }
    return NULL;
}

static void print_indent(int d)
{
    while (d--) putchar(' ');
}

void xml_print_node(XMLNode *node, int indent)
{
    if (!node) return;
    switch (node->type)
    {
        case XML_NODE_DOCUMENT:
            for (XMLNode *c = node->firstChild; c; c = c->nextSibling)
            {
                xml_print_node(c, indent);
            }
            break;

        case XML_NODE_ELEMENT:
            print_indent(indent);
            printf("<%s", node->name ? node->name : "");
            for (XMLAttribute *a = node->attr; a; a = a->next)
            {
                printf(" %s=\"%s\"", a->name, a->value ? a->value : "");
            }

            if (!node->firstChild)
            {
                printf("/>\n");
            }
            else
            {
                printf(">\n");
                for (XMLNode *c = node->firstChild; c; c = c->nextSibling)
                {
                    xml_print_node(c, indent + 2);
                }
                print_indent(indent);
                printf("</%s>\n", node->name ? node->name : "");
            }
            break;

        case XML_NODE_TEXT:
            print_indent(indent);
            printf("%s\n", node->text ? node->text : "");
            break;

        case XML_NODE_CDATA:
            print_indent(indent);
            printf("<![CDATA[%s]]>\n", node->text ? node->text : "");
            break;

        case XML_NODE_COMMENT:
            print_indent(indent);
            printf("<!--%s-->\n", node->text ? node->text : "");
            break;
    }
}

