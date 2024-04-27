#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// This function is used to figure out the ordering
// of the strings in qsort.  You do not need
// to modify it.
int stringOrder(const void *vp1, const void *vp2)
{
    const char *const *p1 = vp1;
    const char *const *p2 = vp2;
    return strcmp(*p1, *p2);
}

// This function will sort and print data (whose length is count).
void sortData(char **data, size_t count)
{
    qsort(data, count, sizeof(char *), stringOrder);

    // print data
    for (size_t i = 0; i < count; i++)
    {
        printf("%s\n", data[i]);
    }
}

int main(int argc, char **argv)
{


    // WRITE YOUR CODE HERE!

    for (size_t i = (argc == 1) ? 0 : 1; i < argc; i++)
    {
        char **lines = NULL;
        size_t lines_num = 0;

        FILE *file = NULL;
        if (argc == 1)
        {
            file = stdin;
        }
        else
        {
            file = fopen(argv[i], "r");
        }

        if (!file)
        {
            for (size_t i = 0; i < lines_num; i++)
            {
                free(lines[i]);
            }

            free(lines);
            fprintf(stderr, "Could not open file.\n");
            return EXIT_FAILURE;
        }


        char *line_buffer = NULL;
        size_t line_len = 0;
        size_t byte_size = 0;

        while ((line_len = getline(&line_buffer, &byte_size, file)) != EOF)
        {
            lines_num++;
            lines = realloc(lines, lines_num * sizeof(*lines));
            lines[lines_num - 1] = malloc((line_len + 1) * sizeof(*lines[lines_num - 1]));
            strcpy(lines[lines_num - 1], line_buffer);

            char *newline_pos = NULL;
            if ((newline_pos = strchr(lines[lines_num - 1], '\n')) != NULL)
            {
                *newline_pos = '\0';
            }
        }

        free(line_buffer);

        if (argc != 1)
        {
            fclose(file);
        }

        sortData(lines, lines_num);

        for (size_t i = 0; i < lines_num; i++)
        {
            free(lines[i]);
        }

        free(lines);
    }


    return EXIT_SUCCESS;
}
