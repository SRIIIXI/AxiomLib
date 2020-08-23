/*

Copyright (c) 2020, CIMCON Automation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is allowed only with prior permission from CIMCON Automation

*/

#include "ConfigurationINI.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

struct ini_t
{
  char *data;
  char *end;
};


/* Case insensitive string compare */
static int strcmpci(const char *a, const char *b)
{
  for (;;)
  {
    int d = tolower(*a) - tolower(*b);

    if (d != 0 || !*a)
    {
      return d;
    }

    a++;
    b++;
  }
}

/* Returns the next string in the split data */
static char* next(struct ini_t *ini, char *p)
{
  p += strlen(p);

  while (p < ini->end && *p == '\0')
  {
    p++;
  }
  return p;
}

static void trim_back(struct ini_t *ini, char *p)
{
  while (p >= ini->data && (*p == ' ' || *p == '\t' || *p == '\r'))
  {
    *p-- = '\0';
  }
}

static char* discard_line(struct ini_t *ini, char *p)
{
  while (p < ini->end && *p != '\n')
  {
    *p++ = '\0';
  }

  return p;
}


static char *unescape_quoted_value(struct ini_t *ini, char *p)
{
  /* Use `q` as write-head and `p` as read-head, `p` is always ahead of `q`
   * as escape sequences are always larger than their resultant data */
  char *q = p;
  p++;

  while (p < ini->end && *p != '"' && *p != '\r' && *p != '\n')
  {
    if (*p == '\\')
    {
      /* Handle escaped char */
      p++;
      switch (*p) {
        default   : *q = *p;    break;
        case 'r'  : *q = '\r';  break;
        case 'n'  : *q = '\n';  break;
        case 't'  : *q = '\t';  break;
        case '\r' :
        case '\n' :
        case '\0' : goto end;
      }

    }
    else
    {
      /* Handle normal char */
      *q = *p;
    }
    q++, p++;
  }
end:
  return q;
}


/* Splits data in place into strings containing section-headers, keys and
 * values using one or more '\0' as a delimiter. Unescapes quoted values */
static void split_data(struct ini_t *ini)
{
  char *value_start, *line_start;
  char *p = ini->data;

  while (p < ini->end)
  {
    switch (*p) {
      case '\r':
      case '\n':
      case '\t':
      case ' ':
        *p = '\0';
        /* Fall through */

      case '\0':
        p++;
        break;

      case '[':
        p += strcspn(p, "]\n");
        *p = '\0';
        break;

      case ';':
      case '#':
        p = discard_line(ini, p);
        break;

      default:
        line_start = p;
        p += strcspn(p, "=\n");

        /* Is line missing a '='? */
        if (*p != '=')
        {
          p = discard_line(ini, line_start);
          break;
        }
        trim_back(ini, p - 1);

        /* Replace '=' and whitespace after it with '\0' */
        do
        {
          *p++ = '\0';
        } while (*p == ' ' || *p == '\r' || *p == '\t');

        /* Is a value after '=' missing? */
        if (*p == '\n' || *p == '\0')
        {
          p = discard_line(ini, line_start);
          break;
        }

        if (*p == '"')
        {
          /* Handle quoted string value */
          value_start = p;
          p = unescape_quoted_value(ini, p);

          /* Was the string empty? */
          if (p == value_start) {
            p = discard_line(ini, line_start);
            break;
          }

          /* Discard the rest of the line after the string value */
          p = discard_line(ini, p);

        }
        else
        {
          /* Handle normal value */
          p += strcspn(p, "\n");
          trim_back(ini, p - 1);
        }
        break;
    }
  }
}



void* configuration_ini_load(const char *filename)
{
  struct ini_t *ini = NULL;
  FILE *fp = NULL;
  int n, sz;

  /* Init ini struct */
  ini = malloc(sizeof(*ini));

  if (!ini)
  {
    goto fail;
  }

  memset(ini, 0, sizeof(*ini));

  /* Open file */
  fp = fopen(filename, "rb");

  if (!fp)
  {
    goto fail;
  }

  /* Get file size */
  fseek(fp, 0, SEEK_END);
  sz = ftell(fp);
  rewind(fp);

  /* Load file content into memory, null terminate, init end var */
  ini->data = malloc(sz + 1);
  ini->data[sz] = '\0';
  ini->end = ini->data  + sz;
  n = fread(ini->data, 1, sz, fp);

  if (n != sz)
  {
    goto fail;
  }

  /* Prepare data */
  split_data(ini);

  /* Clean up and return */
  fclose(fp);
  return ini;

fail:
  if (fp) fclose(fp);
  if (ini) configuration_ini_free(ini);

  return NULL;
}


void configuration_ini_free(void *ptr)
{
    if(!ptr)
    {
        return;
    }

  struct ini_t* ini = (struct ini_t*)ptr;
  free(ini->data);
  free(ini);
}


const char* configuration_ini_get(void *ptr, const char *section, const char *key)
{
    if(!ptr)
    {
        return NULL;
    }

    struct ini_t* ini = (struct ini_t*)ptr;

  char *current_section = "";
  char *val;
  char *p = ini->data;

  if (*p == '\0')
  {
    p = next(ini, p);
  }

  while (p < ini->end)
  {
    if (*p == '[')
    {
      /* Handle section */
      current_section = p + 1;

    }
    else
    {
      /* Handle key */
      val = next(ini, p);
      if (!section || !strcmpci(section, current_section))
      {
        if (!strcmpci(p, key))
        {
          return val;
        }
      }
      p = val;
    }

    p = next(ini, p);
  }

  return NULL;
}


int configuration_ini_sget(void *ptr, const char *section, const char *key, const char *scanfmt, void *dst)
{
    struct ini_t* ini = (struct ini_t*)ptr;

    if(!ptr)
    {
        return INT32_MAX;
    }

  const char *val = configuration_ini_get(ini, section, key);

  if (!val)
  {
    return 0;
  }

  if (scanfmt)
  {
    sscanf(val, scanfmt, dst);
  }

  else
  {
    *((const char**) dst) = val;
  }

  return 1;
}

const char* configuration_ini_get_string(void *ptr, const char *section, const char *key)
{
    return configuration_ini_get(ptr, section, key);
}

long configuration_ini_get_number(void *ptr, const char *section, const char *key)
{
    struct ini_t* ini = (struct ini_t*)ptr;

    if(!ptr)
    {
        return INT64_MAX;
    }

    if(configuration_ini_get(ptr, section, key))
    {
        return atol(configuration_ini_get(ptr, section, key));
    }

    return INT64_MAX;
}

float configuration_ini_get_real(void *ptr, const char *section, const char *key)
{
    struct ini_t* ini = (struct ini_t*)ptr;

    if(!ptr)
    {
        return FLT_MAX;
    }

    if(configuration_ini_get(ptr, section, key))
    {
        return atof(configuration_ini_get(ptr, section, key));
    }

    return FLT_MAX;
}

bool configuration_ini_get_boolean(void *ptr, const char *section, const char *key)
{
    struct ini_t* ini = (struct ini_t*)ptr;

    if(!ptr)
    {
        return false;
    }

    char* val = configuration_ini_get(ptr, section, key);

    if(val)
    {
        if(strcmpci(val, "1") == 0)
        {
            return true;
        }

        if(strcmpci(val, "true") == 0)
        {
            return true;
        }
    }

    return false;
}
