CC = gcc
CFLAGS = -Wall -std=c99
DEPS = question.h
OBJ = vocatrainer.o question.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

vocatrainer: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	$(RM) -f vocatrainer *.o
