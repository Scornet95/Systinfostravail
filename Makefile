CC=gcc
AR=ar
CFLAGS=-Wall -Werror -DC99 -ICTester -g -std=c99

LIB_FILES=src/lib/reverse.c src/lib/sha256.c
OBJ=stack.o producer.o buffer.o stack.o
SRC=src/producer.c src/stack.c src/stack.c src/buffer.c

LIB=reverse.o sha256.o

all: cracker $(OBJ) $(LIB)

cracker: src/main.c $(OBJ) $(LIB)
	$(CC) $(CFLAGS) src/main.c $(LIB) $(OBJ) -lpthread -o cracker

$(LIB): $(LIB_FILES)
	$(CC) $(CFLAGS) -c $(LIB_FILES)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm *.o *.a cracker
