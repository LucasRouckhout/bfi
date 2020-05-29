#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 100

typedef struct {
	char *bottom;
	ssize_t size;
} stack;

void init(stack *s) {
	s->bottom = (char *)malloc(sizeof(char) * INIT_SIZE);
	s->size = 0;
}

char *top(const stack *s) {
	if (s->size == 0) return NULL;
	return (s->bottom + s->size - 1);
}

void push(stack s*) {
	if ()
}

#endif // _STACK_H_
