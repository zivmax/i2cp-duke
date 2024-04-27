#include "cards.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


void assert_card_valid(card_t c)
{
    // Assert the value is between 2 and VALUE_ACE
    assert(2 <= c.value && c.value <= VALUE_ACE);

    // Assert the suit is between 0 and NUM_SUITS
    assert(0 <= c.suit && c.suit < NUM_SUITS);
}

const char *ranking_to_string(hand_ranking_t r)
{
    switch (r)
    {
        case STRAIGHT_FLUSH:
            return "STRAIGHT_FLUSH";
            break;

        case FOUR_OF_A_KIND:
            return "FOUR_OF_A_KIND";
            break;

        case FULL_HOUSE:
            return "FULL_HOUSE";
            break;

        case FLUSH:
            return "FLUSH";
            break;

        case STRAIGHT:
            return "STRAIGHT";
            break;

        case THREE_OF_A_KIND:
            return "THREE_OF_A_KIND";
            break;

        case TWO_PAIR:
            return "TWO_PAIR";
            break;

        case PAIR:
            return "PAIR";
            break;

        case NOTHING:
            return "NOTHING";
            break;

        default:
            printf("Some thing wrong in `const char *ranking_to_string(hand_ranking_t r)`.\n");
            abort();
            break;
    }

    // Should never reach here
    return "";
}

char value_letter(card_t c)
{
    switch (c.value)
    {
        case -1:
            return '?';
            break;

        case 2:
            return '2';
            break;

        case 3:
            return '3';
            break;

        case 4:
            return '4';
            break;

        case 5:
            return '5';
            break;

        case 6:
            return '6';
            break;

        case 7:
            return '7';
            break;

        case 8:
            return '8';
            break;

        case 9:
            return '9';
            break;

        case 10:
            return '0';
            break;

        case VALUE_JACK:
            return 'J';
            break;

        case VALUE_QUEEN:
            return 'Q';
            break;

        case VALUE_KING:
            return 'K';
            break;

        case VALUE_ACE:
            return 'A';
            break;

        default:
            printf("Some thing wrong in `char value_letter(card_t c)`.\n");
            abort();
            break;
    }

    // Should never reach here
    return '\0';
}


char suit_letter(card_t c)
{
    switch (c.suit)
    {
        case SPADES:
            return 's';
            break;

        case DIAMONDS:
            return 'd';
            break;

        case HEARTS:
            return 'h';
            break;

        case CLUBS:
            return 'c';
            break;

        default:
            printf("Some thing wrong in `char suit_letter(card_t c)`.\n");
            abort();
            break;
    }

    // Should never reach here
    return '\0';
}

void print_card(card_t c)
{
    char value_char = '\0';
    switch (c.value)
    {
        case 2:
            value_char = '2';
            break;

        case 3:
            value_char = '3';
            break;

        case 4:
            value_char = '4';
            break;

        case 5:
            value_char = '5';
            break;

        case 6:
            value_char = '6';
            break;

        case 7:
            value_char = '7';
            break;

        case 8:
            value_char = '8';
            break;

        case 9:
            value_char = '9';
            break;

        case 10:
            value_char = '0';
            break;

        case VALUE_JACK:
            value_char = 'J';
            break;

        case VALUE_QUEEN:
            value_char = 'Q';
            break;

        case VALUE_KING:
            value_char = 'K';
            break;

        case VALUE_ACE:
            value_char = 'A';
            break;

        default:
            printf("Some thing wrong in `void print_card(card_t c)`.\n");
            abort();
            break;
    }

    char suit_char = '\0';
    switch (c.suit)
    {
        case SPADES:
            suit_char = 's';
            break;

        case DIAMONDS:
            suit_char = 'd';
            break;

        case HEARTS:
            suit_char = 'h';
            break;

        case CLUBS:
            suit_char = 'c';
            break;

        default:
            printf("Some thing wrong in `void print_card(card_t c)`.\n");
            abort();
            break;
    }

    printf("%c%c", value_char, suit_char);
}

card_t card_from_letters(char value_let, char suit_let)
{

    int value = 0;
    if ('2' <= value_let && value_let <= '9')
    {
        value = value_let - '0';
    }
    else if (value_let == '0')
    {
        value = 10;
    }
    else
    {
        switch (value_let)
        {
            case 'J':
                value = VALUE_JACK;
                break;
            case 'Q':
                value = VALUE_QUEEN;
                break;
            case 'K':
                value = VALUE_KING;
                break;
            case 'A':
                value = VALUE_ACE;
                break;
            default:
                break;
        }
    }


    int suit = 0;
    switch (suit_let)
    {
        case 's':
            suit = SPADES;
            break;
        case 'h':
            suit = HEARTS;
            break;
        case 'd':
            suit = DIAMONDS;
            break;
        case 'c':
            suit = CLUBS;
            break;
        default:
            break;
    }

    card_t temp = {.value = value, .suit = suit};

    return temp;
}

card_t card_from_num(unsigned c)
{
    assert(0 <= c && c < 52);
    unsigned value = (c % 13) + 2;
    unsigned suit = (int) c / 13;
    card_t temp = {.value = value, .suit = suit};

    return temp;
}
