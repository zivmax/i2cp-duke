#include "cards.h"
#include "deck.h"
#include "future.h"
#include "input.h"

int main(void)
{
    size_t x = 21;
    future_cards_t *y = malloc(sizeof(*y));
    y->decks = NULL;
    y->n_decks = 0;
    FILE *f = fopen("inputfile.txt", "r");
    deck_t **hand = read_input(f, &x, y);

    for (size_t i = 0; i < x; i++)
    {
        for (size_t j = 0; j < hand[i]->n_cards; j++)
        {
            free(hand[i]->cards[j]);
        }
        free(hand[i]->cards);
        free(hand[i]);
    }
    free(hand);


    // free
    for (size_t i = 0; i < y->n_decks; i++)
    {
        for (size_t j = 0; j < y->decks[i].n_cards; j++)
        {
            free(y->decks[i].cards[j]);
        }

        free(y->decks[i].cards);
    }


    free(y->decks);

    free(y);


    return EXIT_SUCCESS;
}