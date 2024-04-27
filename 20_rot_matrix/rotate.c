#include <stdlib.h>
#include <string.h>


void rotate(char matrix[10][10])
{
    char temp[10][10];
    for (size_t i = 0, k = 9; i < 10; i++, k--)
    {
        for (size_t j = 0, l = 0; j < 10; j++, l++)
        {
            temp[l][k] = matrix[i][j];
        }
    }

    // copy back to the matrix
    memcpy(matrix, temp, sizeof(temp));


    return;
}
