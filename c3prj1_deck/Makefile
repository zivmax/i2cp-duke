GIVEN_OBJS=deck-c4.o  eval-c4.o  future.o  input.o  main.o
MY_OBJS=../c2prj1_cards/cards.o deck.o eval.o
CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu99

test-deck: deck.o test-deck.o deck-c4.o ../c2prj1_cards/cards.o
	gcc -o test-deck -ggdb3 deck.o test-deck.o deck-c4.o ../c2prj1_cards/cards.o
clean:
	rm test poker cards.o my-test-main.o *~
