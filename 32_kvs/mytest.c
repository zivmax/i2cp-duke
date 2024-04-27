#include "kv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_openFile(const char *fname)
{
    FILE *file = openFile(fname);
    printf("%p\n", (void *) file);

    if (file != NULL)
    {
        fclose(file);
    }

    return;
}

void test_readFile(const char *fname)
{
    FILE *file = openFile(fname);
    char **lines = readFile(file);

    for (size_t i = 0; lines[i] != NULL; i++)
    {
        printf("%s\n", lines[i]);
    }


    if (file != NULL)
    {
        fclose(file);
    }

    for (size_t i = 0; i == 0 || lines[i - 1] != NULL; i++)
    {
        free(lines[i]);
    }

    free(lines);

    return;
}

void test_readkv(const char *fname)
{
    freeKVs(readKVs(fname));
    return;
}

int main(void)
{
    test_readkv("tests.xt");
    return 0;
}
