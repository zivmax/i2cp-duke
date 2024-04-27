#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "The argument are exactly one\n");
        exit(EXIT_FAILURE);
    }


    FILE *fp = fopen(argv[1], "r");

    if (!fp)
    {
        fprintf(stderr, "The file '%s' open error\n", *argv);
        exit(EXIT_FAILURE);
    }


    char buffer[11] = {0};
    char matrix[10][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

    for (size_t i = 0; i < 10; i++)
    {
        if (fgets(buffer, 11, fp) != NULL && strchr(buffer, '\n') == NULL && fgetc(fp) == '\n')
        {
            strncpy(matrix[i], buffer, 10);
        }
        else
        {
            fprintf(stderr, "Input corrupted\n");
            exit(EXIT_FAILURE);
        }
    }

    if (fgetc(fp) != EOF)
    {
        fprintf(stderr, "Input corrupted\n");
        exit(EXIT_FAILURE);
    }


    char temp[10][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

    for (size_t i = 0, k = 9; i < 10; i++, k--)
    {
        for (size_t j = 0, l = 0; j < 10; j++, l++)
        {
            temp[l][k] = matrix[i][j];
        }
    }

    memcpy(matrix, temp, sizeof(temp));

    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
