#include "stack.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

void sinit(stack *s) {
	s->length = 0;
	s->alloc_length = INIT_ALLOC;
	s->elements = (char **) malloc(sizeof(char*) * INIT_ALLOC);
	if (s->elements == NULL) {
		perror("sinit");
		exit(EXIT_FAILURE);
	}
}

void sdelete(stack *s) {
	free(s->elements);	
}

void push(stack *s, char *c) {
	if (s->length == s->alloc_length) {
		s->alloc_length *= 2;
		s->elements = reallocf(s->elements, s->alloc_length * sizeof(char));
		if (s->elements == NULL) {
			perror("realloc stack");
			exit(EXIT_FAILURE);
		}
	}

	s->elements[s->length] = c;
	s->length += 1;
}


char *pop(stack *s) {
	assert(s->length > 0);
	s->length--;
	return s->elements[s->length];
}

char *top(stack *s) {
	if (s->length <= 0) return NULL;
	return s->elements[s->length - 1];
}
