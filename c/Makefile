CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDLIBS = -lreadline
DEPS = question.h
OBJ = vocatrainer.o question.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDLIBS) 

vocatrainer: $(OBJ)
	gcc $(CFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(OBJ) vocatrainer
