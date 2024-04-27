CFLAG = -fsanitize=signed-integer-overflow -g -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer -ggdb3 -O0 -std=c17 -Wall -Werror -Wextra -Wshadow -Wpedantic

test:
	gcc $(CFLAG) -o test test.c
