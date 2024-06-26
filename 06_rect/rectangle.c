#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


// I've provided "min" and "max" functions in
// case they are useful to you
int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

// Declare your rectangle structure here!

typedef struct
{
    int x;
    int y;
    int width;
    int height;
} rectangle;


rectangle canonicalize(rectangle r)
{
    // WRITE THIS FUNCTION
    r.x = (r.width < 0) ? r.x + r.width : r.x;
    r.width = abs(r.width);
    r.y = (r.height < 0) ? r.y + r.height : r.y;
    r.height = abs(r.height);
    return r;
}

bool no_intersected(rectangle r1, rectangle r2)
{
    rectangle right_rec = (r1.x >= r2.x) ? r1 : r2;
    rectangle left_rec = (r1.x < r2.x) ? r1 : r2;
    rectangle upper_rec = (r1.y >= r2.y) ? r1 : r2;
    rectangle lower_rec = (r1.y < r2.y) ? r1 : r2;

    if (right_rec.x > left_rec.x + left_rec.width)
    {
        return true;
    }
    else if (upper_rec.y > lower_rec.y + lower_rec.height)
    {
        return true;
    }
    else
    {
        return false;
    }

    // This should never happen
    return false;
}

rectangle intersection(rectangle r1, rectangle r2)
{
    r1 = canonicalize(r1);
    r2 = canonicalize(r2);
    // WRITE THIS FUNCTION
    rectangle itsec;
    if (no_intersected(r1, r2))
    {
        itsec.x = 0;
        itsec.y = 0;
        itsec.width = 0;
        itsec.height = 0;
    }
    else
    {
        itsec.x = max(r1.x, r2.x);
        itsec.y = max(r1.y, r2.y);
        itsec.width = min(r1.x + r1.width, r2.x + r2.width) - itsec.x;
        itsec.height = min(r1.y + r1.height, r2.y + r2.height) - itsec.y;
    }

    return itsec;
}

// You should not need to modify any code below this line
void printRectangle(rectangle r)
{
    r = canonicalize(r);
    if (r.width == 0 && r.height == 0)
    {
        printf("<empty>\n");
    }
    else
    {
        printf("(%d,%d) to (%d,%d)\n", r.x, r.y,
               r.x + r.width, r.y + r.height);
    }
}

int main(void)
{
    rectangle r1;
    rectangle r2;
    rectangle r3;
    rectangle r4;

    r1.x = 2;
    r1.y = 3;
    r1.width = 5;
    r1.height = 6;
    printf("r1 is ");
    printRectangle(r1);

    r2.x = 4;
    r2.y = 5;
    r2.width = -5;
    r2.height = -7;
    printf("r2 is ");
    printRectangle(r2);

    r3.x = -2;
    r3.y = 7;
    r3.width = 7;
    r3.height = -10;
    printf("r3 is ");
    printRectangle(r3);

    r4.x = 0;
    r4.y = 7;
    r4.width = -4;
    r4.height = 2;
    printf("r4 is ");
    printRectangle(r4);

    // test everything with r1
    rectangle i = intersection(r1, r1);
    printf("intersection(r1,r1): ");
    printRectangle(i);

    i = intersection(r1, r2);
    printf("intersection(r1,r2): ");
    printRectangle(i);

    i = intersection(r1, r3);
    printf("intersection(r1,r3): ");
    printRectangle(i);

    i = intersection(r1, r4);
    printf("intersection(r1,r4): ");
    printRectangle(i);

    // test everything with r2
    i = intersection(r2, r1);
    printf("intersection(r2,r1): ");
    printRectangle(i);

    i = intersection(r2, r2);
    printf("intersection(r2,r2): ");
    printRectangle(i);

    i = intersection(r2, r3);
    printf("intersection(r2,r3): ");
    printRectangle(i);

    i = intersection(r2, r4);
    printf("intersection(r2,r4): ");
    printRectangle(i);

    // test everything with r3
    i = intersection(r3, r1);
    printf("intersection(r3,r1): ");
    printRectangle(i);

    i = intersection(r3, r2);
    printf("intersection(r3,r2): ");
    printRectangle(i);

    i = intersection(r3, r3);
    printf("intersection(r3,r3): ");
    printRectangle(i);

    i = intersection(r3, r4);
    printf("intersection(r3,r4): ");
    printRectangle(i);

    // test everything with r4
    i = intersection(r4, r1);
    printf("intersection(r4,r1): ");
    printRectangle(i);

    i = intersection(r4, r2);
    printf("intersection(r4,r2): ");
    printRectangle(i);

    i = intersection(r4, r3);
    printf("intersection(r4,r3): ");
    printRectangle(i);

    i = intersection(r4, r4);
    printf("intersection(r4,r4): ");
    printRectangle(i);


    return EXIT_SUCCESS;
}
