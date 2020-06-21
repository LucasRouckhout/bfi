CC=cc
FLAGS=-Ofast -Wall -Wshadow
BIN=bfi


all:
	${CC} main.c stack.c ${FLAGS} -o ${BIN}	

clean:
	rm ${BIN}
