OBJS=cards.o  deck.o  eval.o future.o  input.o
CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu99 -Werror=pedantic

test: cards.o  deck.o  eval.o future.o  input.o test.c
	gcc -o $@ $(CFLAGS) $(OBJS) $@.c

future.o: future.c deck.o future.h
	gcc -c $(CFLAGS) $<

input.o: input.c deck.o input.h
	gcc -c $(CFLAGS) $<

eval.o: eval.c deck.o eval.h
	gcc -c $(CFLAGS) $<

deck.o: deck.c deck.h
	gcc -c $(CFLAGS) $<

cards.o: cards.c cards.h
	gcc -c $(CFLAGS) $<

clean:
	rm test *.o *~