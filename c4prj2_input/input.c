#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
 * This function reads the input from f.  Recall that the input
   file has one hand per line (and that we represent a hand
   with a deck_t).  You should allocate a deck_t for each hand
   and place it into an array of pointers to deck_ts, which is your
   answer.
   This function needs to tell its caller how many hands it read.
   We could return a struct, but we are going to do this a
   different way: it will fill in *n_hands with the number
   of hands.  This is a bit different, but you have seen it
   before: this is how getline "returns" the string it
   read and the size of the space allocated to that string.

   As you read the input, if you encounter future cards
   (?0, ?1, ...), you should use add_empty_card to
   create a placeholder in the hand, and then add_future_card
   to make sure you will update it correctly when you draw
   later.  Also remember that you wrote add_card_to
   earlier in this course, as well as card_from_letters
   in Course 2.  These will both be handy here!

*/

deck_t **read_input(FILE *f, size_t *n_hands, future_cards_t *fc)
{
    if (f == NULL)
    {
        return NULL;
    }

    char **lines = readFile(f);

    deck_t **hands = NULL;
    *n_hands = 0;
    char *token = calloc(10, sizeof(*token));
    for (size_t i = 0; lines[i] != NULL; i++)
    {
        (*n_hands)++;
        hands = realloc(hands, (*n_hands) * sizeof(*hands));
        hands[*n_hands - 1] = malloc(sizeof(**hands));
        hands[*n_hands - 1]->cards = NULL;
        hands[*n_hands - 1]->n_cards = 0;

        size_t header = 0;
        while (1)
        {
            if (lines[i][header + 1] == '\0')
            {
                break;
            }

            sscanf(&lines[i][header], "%s", token);

            if (token[0] == '?')
            {
                card_t *tempcard = add_empty_card(hands[*n_hands - 1]);
                add_future_card(fc, atoi(&(token[1])), tempcard);
            }
            else
            {
                add_card_to(hands[*n_hands - 1], card_from_letters(token[0], token[1]));
            }


            while (lines[i][header] != ' ')
            {
                header++;
                if (lines[i][header + 1] == '\0')
                {
                    break;
                }
            }

            while (lines[i][header] == ' ')
            {
                header++;
            }
        }
    }

    free(token);
    freeLines(lines);
    return hands;
}
