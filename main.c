/*
 * A POSIX compliant brainfuck interpreter.
 *
 * Author: Lucas Rouckhout <lucas.rouckhout@gmail.com>
 *
 * */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define INIT_MEM_SIZE 1048576 // 1 MiB
#define STACK_SIZE 1000

typedef struct {
	const char	*bottom;
	char		*top;
} stack;

stack *init_stack();
void free_stack(stack *);

void int_loop(char *, char*, stack *);

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Wrong usage expected a source file: bfi <SOURCE_FILE>\n");
		exit(EXIT_FAILURE);
	}
	
	int fd_sc;
	if ( (fd_sc = open(argv[1], O_RDONLY)) < 0 ) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}

	struct stat file_stat;
	if ( fstat(fd_sc, &file_stat) < 0 ) {
		perror("size");
		close(fd_sc);
		exit(EXIT_FAILURE);
	}
	
	const char *code_buffer = calloc(file_stat.st_size, sizeof(char));
	if ( read(fd_sc, (void *) code_buffer, file_stat.st_size) < 0 ) {
		perror("read");
		close(fd_sc);
		free((void*) code_buffer);
		exit(EXIT_FAILURE);
	}

	const char *mem_buffer = calloc(INIT_MEM_SIZE, sizeof(char));
	char *mem_ptr		=	(char *) mem_buffer;
	char *code_ptr		=	(char *) code_buffer;
	stack *code_stack	=	init_stack();
	
	int_loop(mem_ptr, code_ptr, code_stack);
	
	close(fd_sc);
	free_stack(code_stack);	
	free((void *) mem_buffer);
	free((void *) code_buffer);
	return EXIT_SUCCESS;
}

stack *init_stack() {
	stack *st = malloc(sizeof(stack));	
	st->bottom = calloc(STACK_SIZE, sizeof(char));
	st->top = (char *) st->bottom;
	return st;
}

void free_stack(stack *st) {
	free((void *) st->bottom);
	free(st);
}

void int_loop(char *mem_ptr, char *code_ptr, stack *code_stack) {
    switch (*code_ptr) {
        case '+':
            *
            break;
            
        default:
            break;
    }
}
