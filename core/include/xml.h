/*
  tinyxml_c.h - Minimal DOM XML parser in pure C
  Suitable for embedded systems (OPC UA, ONVIF, etc.)
*/

#ifndef TINYXML_C_H
#define TINYXML_C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Node types */
typedef enum
{
    XML_NODE_DOCUMENT,
    XML_NODE_ELEMENT,
    XML_NODE_TEXT,
    XML_NODE_CDATA,
    XML_NODE_COMMENT
} XMLNodeType;

/* Forward declarations */
typedef struct XMLNode XMLNode;
typedef struct XMLDocument XMLDocument;

/* Document management */
XMLDocument *xml_parse_string(const char *input);
XMLDocument *xml_load_file(const char *path);
void xml_free_document(XMLDocument *doc);

/* Node navigation */
XMLNode *xml_node_first_child_element(XMLNode *node, const char *name);
XMLNode *xml_node_next_sibling_element(XMLNode *node, const char *name);
XMLNode *xml_node_parent(XMLNode *node);

/* Node info */
XMLNodeType xml_node_type(XMLNode *node);
const char *xml_node_name(XMLNode *node);
const char *xml_node_get_attr(XMLNode *node, const char *name);
const char *xml_node_get_text(XMLNode *node);

/* Debugging / output */
void xml_print_node(XMLNode *node, int indent);

#ifdef __cplusplus
}
#endif

#endif /* TINYXML_C_H */

