CC=gcc
INCF=src/include
CFLAGS=-Wall -Werror -DC99 -ICTester -g -std=c99 -I $(INCF)


OBJ=buffer.o stack.o producer.o reverse.o sha256.o
SRC= src/buffer.c src/stack.c src/producer.c src/reverse.c src/sha256.c


all: $(OBJ) cracker

cracker : src/main.c $(OBJ)
	$(CC) $(CFLAGS) src/main.c -o cracker $(OBJ)
#%.o : %.c
$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)


#clean:
#	rm *.o *.a cracker
