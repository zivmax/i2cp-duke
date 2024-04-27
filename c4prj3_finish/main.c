#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    // Check command line arguments/report errors
    if (argc < 2 || argc > 3)
    {
        fprintf(stderr, "Usage: %s inputfile.txt {num_trials}\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Determine the number of trials
    int num_trials = (argc == 3) ? atoi(argv[2]) : 10000;

    // Open the input file and read the hands in it
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", argv[1]);
        return EXIT_FAILURE;
    }

    size_t n_hands = 0;
    future_cards_t *fc = malloc(sizeof(*fc));
    fc->decks = NULL;
    fc->n_decks = 0;
    deck_t **hands = read_input(file, &n_hands, fc);
    fclose(file);

    // Create a deck with the remaining cards
    deck_t *remaining_deck = build_remaining_deck(hands, n_hands);

    /* Create an array to count how many times each hand
     wins, with one more element for if there was a tie
     (so if there are 2 hands, you should have 3 elements).
     and initialize all its values to 0. */
    size_t *win_counts = calloc(n_hands, sizeof(*win_counts));

    size_t ties = 0;
    // Do each Monte Carlo trial (repeat num_trials times)
    for (int i = 0; i < num_trials; i++)
    {
        // Shuffle the remaining deck
        shuffle(remaining_deck);

        // Assign the cards from the shuffled deck to the hands
        future_cards_from_deck(remaining_deck, fc);

        // Determine the winning hand
        unsigned winning_hand = 0;
        unsigned tie_or_not = 0;
        for (size_t j = 1; j < n_hands; j++)
        {
            short res = compare_hands(hands[j], hands[winning_hand]);
            switch (res)
            {
                case 1:
                    winning_hand = j;
                    break;

                case 0:
                    tie_or_not++;
                    break;
                case -1:
                    break;
                default:
                    break;
            }
        }

        // Increment the count for the winning hand

        if (tie_or_not == n_hands - 1)
        {
            ties++;
        }
        else
        {
            win_counts[winning_hand]++;
        }
    }


    // Print the results
    for (size_t i = 0; i < n_hands; i++)
    {
        printf("Hand %zu won %lu / %u times (%.2f%%)\n",
               i, win_counts[i], num_trials, 100.0 * win_counts[i] / num_trials);
    }
    printf("And there were %lu ties\n", ties);


    // Free things
    for (size_t i = 0; i < n_hands; i++)
    {
        free_deck(hands[i]);
    }
    for (size_t i = 0; i < fc->n_decks; i++)
    {
        free(fc->decks[i].cards);
    }
    free(fc->decks);
    free(fc);
    free(hands);
    free_deck(remaining_deck);
    free(win_counts);

    return EXIT_SUCCESS;
}
