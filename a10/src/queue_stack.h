/**
 * -------------------------------------
 * @file  queue_stack.h
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-23
 *
 * -------------------------------------
 */
#ifndef QUEUE_STACK_H
#define QUEUE_STACK_H

typedef struct node {
	void *data;
	struct node *next;
} NODE;

typedef struct queue {
	NODE *front, *rear;
} QUEUE;

void enqueue(QUEUE *qp, void *data);
void* dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);

typedef struct stack {
	NODE *top;
} STACK;

void push(STACK *sp, void *data);
void* pop(STACK *sp);
void clean_stack(STACK *sp);

#endif
