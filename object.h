#ifndef LAV_OBJ
#define LAV_OBJ

enum type {
  STRING,
  REAL,
  NATURAL,
  INTEGER,
  VECTOR
}

typedef struct obj {
  unsigned int  header;
  unsigned char readonly    : 1;
  unsigned char initialized : 1;
  unsigned char overflowed  : 1;
  unsigned char has_length  : 1;
  unsigned char             : 4;
  unsigned int  length;
  union {
    char *        s;
    double        r;
    unsigned long n;
    long          i;
    struct obj *  v;
} obj;


#endif
