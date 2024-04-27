#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n);


int main(void)
{
    int array1[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
    if (maxSeq(array1, 10) != 4)
    {

        return EXIT_FAILURE;
    }

    int *array2 = NULL;
    if (maxSeq(array2, 0) != 0)
    {
        return EXIT_FAILURE;
    }

    int array3[] = {1, 1, 1, 1};
    if (maxSeq(array3, 4) != 1)
    {
        return EXIT_FAILURE;
    }

    int array4[] = {1};
    if (maxSeq(array4, 1) != 1)
    {
        return EXIT_FAILURE;
    }

    int array5[] = {-1, -2, -3, -4, 1, 2, 0};
    if (maxSeq(array5, 7) != 3)
    {
        return EXIT_FAILURE;
    }

    int array6[] = {1, 1, 1, 1, 0, 0};
    if (maxSeq(array6, 6) != 1)
    {
        return EXIT_FAILURE;
    }
    int array7[] = {1, 2, 1, 4, 5, 6};
    if (maxSeq(array7, 6) != 4)
    {
        return EXIT_FAILURE;
    }

    int array8[] = {1, 2, 3, 2, 5, 6};
    if (maxSeq(array8, 6) != 3)
    {
        return EXIT_FAILURE;
    }

    int array9[] = {4, 3, 2, 1};
    if (maxSeq(array9, 4) != 1)
    {
        return EXIT_FAILURE;
    }

    int array10[] = {1, 2, 3, 4};
    if (maxSeq(array10, 4) != 4)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
