#include <stdlib.h>

#include "object.h"
#include "string.h"

obj * str_init(char * c, int ro) {
  obj * o = malloc(sizeof(obj));
  int len = c ? strlen(c) : 1;
  
  o->header     = STRING_T;
  o->readonly   = ro;
  o->overflowed = false;
  o->has_length = true;
  
  o->length = len;
  o->s = malloc(len);
  if (len == 1) {
    o->s[0] = '\0';
  } else if (str_load(o->s, c, len) != len) {
    fprintf(stderr, "Found unexpected null character.");
  }
  return o;
}

/* copy data from a null-terminated C-style string to a buffer within
 * a Lavender string, which knows its length. (i.e. copy everything
 * before the null terminator.)
 */
unsigned str_load(char * dest, char * src, unsigned src_len) {
  unsigned u = 0;
  for (u; u < src_len; u++) {
    if (!src[u]) {
      break;
    }
    dest[u] = src[u];
  }
  return u;
}


