#ifndef __KV_H__
#define __KV_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _kvpair_t
{
    char *key;
    char *value;
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t
{
    kvpair_t *pairs;
    unsigned long length;
};
typedef struct _kvarray_t kvarray_t;


char **readFile(FILE *file);

char *strip_newline(char *line);

FILE *openFile(const char *fname);

kvarray_t *readKVs(const char *fname);

void freeKVs(kvarray_t *pairs);

void printKVs(kvarray_t *pairs);

char *lookupValue(kvarray_t *pairs, const char *key);


#endif
