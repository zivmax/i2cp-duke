#include "counts.h"

counts_t *createCounts(void)
{
    counts_t temp = {.array = NULL, .length = 0, .unknown = 0};
    counts_t *c = malloc(sizeof(*c));
    memcpy(c, &temp, sizeof(*c));

    return c;
}


int search(counts_t *c, const char *name)
{
    for (size_t i = 0; i < c->length; i++)
    {
        if (strcmp(c->array[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}


void addCount(counts_t *c, const char *name)
{
    if (c == NULL)
    {
        return;
    }

    if (name == NULL)
    {
        c->unknown++;
    }

    else
    {
        int idx = search(c, name);
        if (idx == -1)
        {
            c->array = realloc(c->array, (c->length + 1) * sizeof(*c->array));
            c->array[c->length].name = malloc((strlen(name) + 1) * sizeof(*name));
            strcpy(c->array[c->length].name, name);
            c->array[c->length].number = 1;
            c->length++;
        }
        else
        {
            c->array[idx].number++;
        }
    }
}

void printCounts(counts_t *c, FILE *outFile)
{
    if (c == NULL)
    {
        return;
    }

    for (size_t i = 0; i < c->length; i++)
    {
        fprintf(outFile, "%s: %zu\n", c->array[i].name, c->array[i].number);
    }

    if (c->unknown != 0)
    {
        fprintf(outFile, "<unknown> : %zu\n", c->unknown);
    }
}

void freeCounts(counts_t *c)
{
    if (c == NULL)
    {
        return;
    }

    for (size_t i = 0; i < c->length; i++)
    {
        free(c->array[i].name);
    }
    free(c->array);
    free(c);
}
