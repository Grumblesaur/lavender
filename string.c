#include <stdlib.h>

#include "object.h"
#include "string.h"

/* create a string object from a C-string,
 * determine whether it's writeable or readonly
 */
obj * str_init(char * c, int ro) {
  obj * o = malloc(sizeof(obj));
  int len = c ? strlen(c) : 1;
  
  o->header     = STRING_T;
  o->readonly   = ro;
  o->overflowed = false;
  o->has_length = true;
  
  o->length = len;
  o->s = malloc(len);
  memset(o->s, '0', len);
  if (len == 1) {
    o->s[0] = '\0';
  } else if (str_load(o->s, c, len) != len) {
    fprintf(stderr, "Found unexpected null character.");
  }
  return o;
}

/* erase the text data held onto by the string struct's internal pointer
 * and return the pointer to the string struct such that the cleanup code
 * may be called as:
 *    obj * ptr = str_init(...);
 *    // ...
 *    free(str_kill(ptr))
 */
obj * str_kill(obj * string) {
  free(string->s);
  return string;
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

/* create a new string by combining two others */
obj * str_concat(obj * left, obj * right) {
  unsigned new_len = left->length + right->length;
  char * buffer = malloc((new_len + 1) * sizeof(char)); // +1 counts temp '\0'
  strcat(buffer, left->s);
  strcat(buffer, right->s);
  obj * o = str_init(buffer, false);
  free(buffer);
  return o;
}

/* create a new string by repeating it the number of times specified
 * by the integer object
 */
obj * str_repeat(obj * string, obj * integer) {
  unsigned new_len = string->length * integer->i;
  char * buffer = malloc((new_len + 1) * sizeof(char)); // +1 counts temp '\0'
  for (unsigned u = 0; u < integer->i; u++) {
    strcat(buffer, string->s);
  }
  obj * out = str_init(buffer, false);
  free(buffer);
  return out;
}

/* get internal C-string value from a string object */
char * str_get(obj * in) {
  return in->header == STRING_T ? in->s : NULL;
}



