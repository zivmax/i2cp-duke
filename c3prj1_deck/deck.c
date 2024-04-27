#include "deck.h"
#include <assert.h>
#include <stdio.h>

void print_hand(deck_t *hand)
{
    for (size_t i = 0; i < hand->n_cards; i++)
    {
        print_card(*(hand->cards[i]));
        printf(" ");
    }
}

int deck_contains(deck_t *d, card_t c)
{
    for (size_t i = 0; i < d->n_cards; i++)
    {
        if (d->cards[i]->value == c.value && d->cards[i]->suit == c.suit)
        {
            return 1;
        }
    }
    return 0;
}

void shuffle(deck_t *d)
{
    card_t *temp;
    size_t index;
    for (size_t i = 0; i < d->n_cards; i++)
    {
        index = random() % d->n_cards;
        temp = d->cards[i];
        d->cards[i] = d->cards[index];
        d->cards[index] = temp;
    }
}

void assert_full_deck(deck_t *d)
{
    assert(d->n_cards == 52);
    for (size_t i = 0; i < d->n_cards; i++)
    {
        assert(deck_contains(d, *(d->cards[i])));
    }
}
