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
	
		
	const char *code_buffer = calloc(INIT_MEM_SIZE, sizeof(char));
	if ( read(fd_sc, (void *) code_buffer, file_stat.st_size) < 0 ) {
		perror("read");
		close(fd_sc);
		free((void*) code_buffer);
		exit(EXIT_FAILURE);
	}

	

	close(fd_sc);
	free((void *) code_buffer);
	return EXIT_SUCCESS;
}
