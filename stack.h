/*
 * A simple stack implementation for elements of type char.
 * */
#ifndef _STACK_H_
#define _STACK_H_

#include <sys/_types/_size_t.h>
#define INIT_ALLOC 20

typedef struct {
	char *elements;
	size_t length;
	size_t alloc_length;
} stack;

void sinit(stack *);

void sdelete(stack *);

void push(stack *, char);

char pop(stack *);

#endif // _STACK_H_
