CC=gcc
AR=ar
CFLAGS=-Wall -Werror -DC99 -ICTester -g -std=c99

LIB_FILES=src/lib/reverse.c src/lib/sha256.c
SRC=src/consumer.c src/producer.c src/buffer.c

LIB=lib.a

all: cracker $(OBJ) $(LIB)

cracker: src/main.c $(OBJ) $(LIB)
	$(CC) $(CFLAGS) src/main.c $(LIB) $(OBJ) -lpthreads -o cracker 

$(LIB): $(LIB_FILES)
	$(CC) $(CFLAGS) -c $(LIB_FILES)
	$(AR) r $(LIB) reverse.o sha256.o

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm *.o *.a cracker
