#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_KEY 26
void count_letters(FILE *fp, int counts[MAX_KEY]);
int find_e(int counts[MAX_KEY]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return (EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file\n");
        return (EXIT_FAILURE);
    }

    int counts[MAX_KEY] = {0};
    count_letters(fp, counts);

    int e = find_e(counts);
    int k = (e - 4 + 26) % 26;
    if (k < 0 || k > 25)
    {
        fprintf(stderr, "Failed to find the key\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", k);


    if (fclose(fp) != 0)
    {
        perror("Failed to close the input file!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void count_letters(FILE *fp, int counts[MAX_KEY])
{
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        if (isalpha(c))
        {
            c = tolower(c);
            counts[c - 'a']++;
        }
    }
}

int find_e(int counts[MAX_KEY])
{
    // We first caculate the sum of all characters
    long long sum = 0;
    for (int i = 0; i < MAX_KEY; i++)
    {
        sum += counts[i];
    }

    // Then we calculate frequency of each characters
    double freq[MAX_KEY] = {0};
    for (int i = 0; i < MAX_KEY; i++)
    {
        freq[i] = (double) counts[i] / sum;
    }

    // Finally we find the e whose frequncy largest

    int max = 0;
    for (int i = 0; i < MAX_KEY; i++)
    {
        if (freq[i] > freq[max])
        {
            max = i;
        }
    }


    return max;
}
