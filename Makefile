

CC=gcc
EXEC=programme
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)


all: $(EXEC)

programme: $(OBJ)
	$(CC) -o $@ $^




gcc src/* -o prog -I include -lmingw32