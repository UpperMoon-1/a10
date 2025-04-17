/**
 * -------------------------------------
 * @file  edgelist.c
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-23
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "edgelist.h"

EDGELIST* new_edgelist() {
	EDGELIST *tp = malloc(sizeof(EDGELIST));
	tp->size = 0;
	tp->start = NULL;
	tp->end = NULL;
	return tp;
}

void insert_edge_end(EDGELIST *g, int from, int to, int weight) {
	// your code
	EDGENODE *node = malloc(sizeof(EDGENODE));
	node->from = from;
	node->to = to;
	node->weight = weight;
	node->next = NULL;
	g->size++;
	if (g->start == NULL) {
		g->start = node;
		g->end = node;
	} else {
		g->end->next = node;
		g->end = node;
	}

	return;
}

void insert_edge_start(EDGELIST *g, int from, int to, int weight) {
	// your code
	EDGENODE *node = malloc(sizeof(EDGENODE));
	node->from = from;
	node->to = to;
	node->weight = weight;
	node->next = NULL;
	g->size++;
	if (g->start == NULL) {
		g->start = node;
		g->end = node;
	} else {
		node->next = g->start;
		g->start = node;
	}
	return;
}

void delete_edge(EDGELIST *g, int from, int to) {
	// your code
	EDGENODE *current = g->start;
	EDGENODE *prev = NULL;
	while (current != NULL) {
		if (current->from == from && current->to == to) { //now delete current
			if (g->size == 1) { //only 1 node and delete it
				g->size--;
				g->start = NULL;
				g->end = NULL;
				free(current);
			} else if (prev == NULL) { //delete first node
				g->start = g->start->next;
				g->size--;
				free(current);
			} else if (current->next == NULL) { //delete last node
				g->end = prev;
				g->end->next = NULL;
				g->size--;
				free(current);
			} else {
				prev->next = current->next;
				g->size--;
				free(current);
			}
			return;
		}
		prev = current;
		current = current->next;
	}
	return;
}

int weight_edgelist(EDGELIST *g) {
	// your code
	int count = 0;
	EDGENODE *current = g->start;
	while (current != NULL) {
		count += current->weight;
		current = current->next;
	}

	return count;
}

void clean_edgelist(EDGELIST **gp) {
	EDGELIST *g = *gp;
	EDGENODE *temp, *p = g->start;
	while (p) {
		temp = p;
		p = p->next;
		free(temp);
	}
	free(g);
	*gp = NULL;
}

void display_edgelist(EDGELIST *g) {
	if (g == NULL)
		return;
	printf("size %d ", g->size);
	printf("(from to weight) ");
	EDGENODE *p = g->start;
	while (p) {
		printf("(%d %d %d) ", p->from, p->to, p->weight);
		p = p->next;
	}
}
