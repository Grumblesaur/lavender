#ifndef LAV_STR
#define LAV_STR

#include "object.h"

obj  * str_init(char * c, int ro);
obj  * str_kill(obj * string);
int    str_load(char * dest, char * src, int src_len);
obj  * str_concat(obj * left, obj* right);
obj  * str_repeat(obj * string, obj * integer);
char * str_get(obj * string);

#endif
