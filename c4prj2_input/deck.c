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

/**
 *    Add the particular card to the given deck (which will
   involve reallocing the array of cards in that deck).
*/
void add_card_to(deck_t *deck, card_t c)
{
    card_t *new_card = calloc(1, sizeof(*new_card));
    new_card->value = c.value;
    new_card->suit = c.suit;
    deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*deck->cards));
    deck->cards[deck->n_cards] = new_card;
    deck->n_cards++;
}

/**
 *    Add a card whose value and suit are both 0, and return a pointer
   to it in the deck.
   This will add an invalid card to use as a placeholder
   for an unknown card.
*/

card_t *add_empty_card(deck_t *deck)
{
    card_t *new_card = calloc(1, sizeof(*new_card));
    new_card->value = 0;
    new_card->suit = 0;
    deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*deck->cards));
    deck->cards[deck->n_cards] = new_card;
    deck->n_cards++;
    return new_card;
}

/**
 *    Create a deck that is full EXCEPT for all the cards
   that appear in excluded_cards.  For example,
   if excluded_cards has Kh and Qs, you would create
   a deck with 50 cards---all of them except Kh and Qs.
   You will need to use malloc to allocate this deck.
   (You will want this for the next function).
   Don't forget you wrote card_t card_from_num(unsigned c)
   in Course 2 and int deck_contains(deck_t * d, card_t c)
   in Course 3!  They might be useful here.
*/
deck_t *make_deck_exclude(deck_t *excluded_cards)
{
    deck_t *deck = calloc(1, sizeof(*deck));
    deck->cards = NULL;
    deck->n_cards = 0;
    for (size_t i = 0; i < 52; i++)
    {
        card_t card = card_from_num(i);
        if (!deck_contains(excluded_cards, card))
        {
            add_card_to(deck, card);
        }
    }
    return deck;
}


/**
 *    This function takes an array of hands (remember
   that we use deck_t to represent a hand).  It then builds
   the deck of cards that remain after those cards have
   been removed from a full deck.  For example, if we have
   two hands:
      Kh Qs ?0 ?1 ?2 ?3 ?4
      As Ac ?0 ?1 ?2 ?3 ?4
   then this function should build a deck with 48
   cards (all but As Ac Kh Qs).  You can just build
   one deck with all the cards from all the hands
   (remember you just wrote add_card_to),
   and then pass it to make_deck_exclude.
*/
deck_t *build_remaining_deck(deck_t **hands, size_t n_hands)
{
    deck_t *deck = calloc(1, sizeof(*deck));
    deck->cards = NULL;
    deck->n_cards = 0;

    deck_t tempdeck = {.cards = NULL, .n_cards = 0};


    for (size_t i = 0; i < n_hands; i++)
    {
        for (size_t j = 0; j < hands[i]->n_cards; j++)
        {
            add_card_to(&tempdeck, *(hands[i]->cards[j]));
        }
    }

    return make_deck_exclude(&tempdeck);
}

void free_deck(deck_t *deck)
{
    for (size_t i = 0; i < deck->n_cards; i++)
    {
        free(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
}
