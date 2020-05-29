CC=cc
FLAGS=-Ofast -Wall -Werror -Wshadow
BIN=bfi


all:
	${CC} main.c ${FLAGS} -o ${BIN}	

clean:
	rm ${BIN}
