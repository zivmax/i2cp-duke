#include "counts.h"
#include "kv.h"
#include "outname.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t *countFile(const char *filename, kvarray_t *kvPairs)
{
    counts_t *counts = createCounts();
    if (counts == NULL)
    {
        return NULL;
    }

    FILE *file = openFile(filename);
    char **lines = readFile(file);
    if (fclose(file) != 0)
    {
        fprintf(stderr, "Cannot close file %s\n", filename);
        return NULL;
    }
    
    for (int i = 0; lines[i] != NULL; i++)
    {
        char *value = lookupValue(kvPairs, lines[i]);
        addCount(counts, value);
    }
    
    freeLines(lines);
    return counts;
}

int main(int argc, char **argv)
{
    // WRITE ME (plus add appropriate error checking!)
    if (argc < 3)
    {
        fprintf(stderr, "Not enough arguments\n");
        return EXIT_FAILURE;
    }

    // read the key/value pairs from the file named by argv[1] (call the result kv)
    kvarray_t *kvs = readKVs(argv[1]);

    // count from 2 to argc (call the number you count i)
    for (int i = 2; i < argc; i++)
    {
        // count the values that appear in the file named by argv[i], using kv as the key/value pair
        //    (call this result c)
        counts_t *c = countFile(argv[i], kvs);
        if (c == NULL)
        {
            fprintf(stderr, "Cannot count file %s\n", argv[i]);
            return EXIT_FAILURE;
        }

        // compute the output file name from argv[i] (call this outName)
        char *outName = computeOutputFileName(argv[i]);

        // open the file named by outName (call that f)
        FILE *f = fopen(outName, "w");
        if (f == NULL)
        {
            fprintf(stderr, "Cannot create file %s\n", outName);
            return EXIT_FAILURE;
        }

        // print the counts from c into the FILE f
        printCounts(c, f);

        // close f
        fclose(f);

        // free the memory for outName and c
        free(outName);
        freeCounts(c);
    }


    // free the memory for kv
    freeKVs(kvs);
    return EXIT_SUCCESS;
}
