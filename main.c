/*
 * A POSIX compliant brainfuck interpreter.
 *
 * Author: Lucas Rouckhout <lucas.rouckhout@gmail.com>
 * */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define INIT_MEM_SIZE 1000000000
#define handle_error(msg) \
  do {                    \
    perror(msg);          \
    exit(EXIT_FAILURE);   \
  } while (0)

/* Top of the stack of jump locations like '[' and ']'. */
int TOP_OF_STACK = 0;

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Wrong usage expected a source file: bfi <SOURCE_FILE>\n");
		exit(EXIT_FAILURE);
	}
	
	// Open the file containing the source code.
	int source_code_fd;
	if ((source_code_fd = open(argv[1], O_RDONLY)) < 0) {
		handle_error(argv[1]);
	}

	// Retrieve the size of the source code file.
	struct stat stats;
	if (fstat(source_code_fd, &stats) < 0) {
		handle_error(argv[0]); 
	}

	off_t size = stats.st_size;

	// Read the source code file into memory on the heap.
	char *begin_of_program = malloc(sizeof(char) * size);
	ssize_t n_bytes;
	if ((n_bytes = read(source_code_fd, (void *)begin_of_program, size)) < 0) {
		handle_error(argv[1]);
	}

	if (n_bytes < size) {
		close(source_code_fd);
		free(begin_of_program);
		printf("Could not read out the complete source file.");
		return EXIT_FAILURE;
	}

	const char *end_of_program = begin_of_program + n_bytes - 1;
	char *source_code_ptr = begin_of_program;

	// Allocate memory on the heap for the programm to use.
	// TODO: Dynammically increase. Will seg fault if going out of memory.
	char *begin_ptr = (char *) calloc(INIT_MEM_SIZE, sizeof(char));
	char *ptr = begin_ptr;
	char *location_stack[size];

	/* Interpreter loop. */
	while (source_code_ptr != end_of_program) {
		switch (*source_code_ptr) {
			case '+':
				++(*ptr);
				break;
			case '-':
				--(*ptr);
				break;
			case '>':
				++ptr;
				break;
			case '<':
				--ptr;
				break;
			case '.':
				putchar(*ptr);
				break;
			case ',':
				*ptr=getchar();
				break;
			case ']':
				if (*ptr != 0) {
					source_code_ptr = location_stack[TOP_OF_STACK];	
				} else {
					TOP_OF_STACK--;
				}
				break;
			case '[':
				if (*ptr == 0) {
					while (*source_code_ptr != ']') source_code_ptr++;
				} else {
					TOP_OF_STACK++;
					location_stack[TOP_OF_STACK] = source_code_ptr;
				}
				break;
			default:
				break;
		}
		source_code_ptr++;
	}

	close(source_code_fd);
	free(begin_of_program);
	free(begin_ptr);
	return EXIT_SUCCESS;
}
