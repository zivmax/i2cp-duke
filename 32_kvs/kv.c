#include "kv.h"


FILE *openFile(const char *fname)
{
    FILE *file = fopen(fname, "r");
    if (file == NULL)
    {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }
    return file;
}


char *strip_newline(char *line)
{
    char *newline = strchr(line, '\n');
    if (newline != NULL)
    {
        *newline = '\0';
    }

    return line;
}


char **readFile(FILE *file)
{
    char **lines = NULL;

    size_t bytes = 0;
    size_t line_num = 0;
    size_t chars_num = 0;
    while (!feof(file))
    {
        char *line = NULL;
        if ((chars_num = getline(&line, &bytes, file)) == EOF)
        {
            free(line);
        }
        else
        {
            line_num++;
            lines = realloc(lines, (line_num + 1) * sizeof(*lines));
            // chars_num + 1 for '\0'.
            lines[line_num - 1] = calloc((chars_num + 1), sizeof(**lines));
            strcpy(lines[line_num - 1], strip_newline(line));
            free(line);
            lines[line_num] = NULL;
        }
    }

    return lines;
}

void freeLines(char **lines)
{
    for (size_t i = 0; i == 0 || lines[i - 1] != NULL; i++)
    {
        free(lines[i]);
    }

    free(lines);
    return;
}

/**
 * open the file, read the lines of text, split them into
key/value pairs, add the resulting pairs to an array (hint: realloc it to make it larger
each time), close the file, and return the kvarray_t * that has your array.
*/
kvarray_t *readKVs(const char *fname)
{
    kvarray_t tempArr = {.pairs = NULL, .length = 0};

    FILE *file = openFile(fname);
    char **lines = readFile(file);
    fclose(file);

    if (lines == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; lines[i] != NULL; i++)
    {

        char *key = calloc(strlen(lines[i]), sizeof(*key));
        char *value = calloc(strlen(lines[i]), sizeof(*value));

        if (strchr(lines[i], '=') != NULL)
        {
            sscanf(lines[i], "%[^=]", key);
            sscanf(lines[i], "%*[^=]=%s", value);
        }
        else
        {
            free(key);
            free(value);
            freeLines(lines);
            return NULL;
        }

        if (key == NULL || value == NULL)
        {
            fprintf(stderr, "Invalid line: %s\n", lines[i]);
        }

        kvpair_t tempPair = {.key = key, .value = value};
        tempArr.length++;
        tempArr.pairs = realloc(tempArr.pairs, (tempArr.length) * sizeof(*tempArr.pairs));

        // Remember to free &tempArr.pairs[tempArr.length - 1]
        memcpy(&tempArr.pairs[tempArr.length - 1], &tempPair, sizeof(*tempArr.pairs));
    }

    kvarray_t *kvArr = calloc(1, sizeof(*kvArr));
    memcpy(kvArr, &tempArr, sizeof(*kvArr));


    freeLines(lines);

    return kvArr;
}

void freeKVs(kvarray_t *pairs)
{
    if (pairs == NULL)
    {
        return;
    }

    for (size_t i = 0; i < pairs->length; i++)
    {
        free(pairs->pairs[i].key);
        free(pairs->pairs[i].value);
    }

    free(pairs->pairs);
    free(pairs);
    return;
}

void printKVs(kvarray_t *pairs)
{
    if (pairs == NULL)
    {
        return;
    }

    for (size_t i = 0; i < pairs->length; i++)
    {
        printf("key = '%s' value = '%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
    }

    return;
}

char *lookupValue(kvarray_t *pairs, const char *key)
{
    if (pairs == NULL || key == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < pairs->length; i++)
    {
        if (strcmp(pairs->pairs[i].key, key) == 0)
        {
            return pairs->pairs[i].value;
        }
    }

    return NULL;
}
