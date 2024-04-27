#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);


void run_check(unsigned x, unsigned y, unsigned expected_ans)
{
    if (power(x, y) != expected_ans)
    {
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    run_check(0, 0, 1);
    run_check(0, 1, 0);
    run_check(1, 0, 1);
    run_check(1, 1, 1);
    run_check(2, 0, 1);
    
    run_check(2, 1, 2);
    run_check(2, 3, 8);
    run_check(2, 4, 16);

    run_check(-1, 1, -1);
    run_check(-1, 2, 1);
    run_check(-1, 3, -1);
    run_check(-1, 0, 1);
    run_check(-2, 0, 1);
    run_check(-2, 1, -2);

    return EXIT_SUCCESS;
}
