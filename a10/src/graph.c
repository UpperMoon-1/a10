/**
 * -------------------------------------
 * @file  graph.c
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
#include <string.h>
#include "queue_stack.h"
#include "graph.h"

GRAPH* new_graph(int order) {
	GRAPH *gp = malloc(sizeof(GRAPH));
	gp->nodes = malloc(order * sizeof(GNODE*));

	int i;
	for (i = 0; i < order; i++) {
		gp->nodes[i] = malloc(sizeof(GNODE));
		gp->nodes[i]->nid = i;
		strcpy(gp->nodes[i]->name, "null");
		gp->nodes[i]->neighbor = NULL;
	}

	gp->order = order;
	gp->size = 0;

	return gp;
}

void insert_edge_graph(GRAPH *g, int from, int to, int weight) { //done
	// your code

	ADJNODE *node = malloc(sizeof(ADJNODE));

	g->size++;
	node->nid = to;
	node->weight = weight;
	node->next = NULL;

	ADJNODE *current = g->nodes[from]->neighbor;
	//node->next = g->nodes[from]->neighbor;
	//g->nodes[from]->neighbor = node;
	if (current == NULL) {
		g->nodes[from]->neighbor = node;
	} else {
		while (current->next != NULL) {
			current = current->next;
		}

		current->next = node;
	}

	return;
}

void delete_edge_graph(GRAPH *g, int from, int to) { //done
	// your code
	ADJNODE *current = g->nodes[from]->neighbor;
	ADJNODE *previous = NULL;
	if (current != NULL) {
		while (current != NULL && current->nid != to) {
			previous = current;
			current = current->next;
		}
		if (current != NULL) {	//then delete current
			g->size--;
			if (previous == NULL) {	//first node
				g->nodes[from]->neighbor = current->next;
			} else { //middle node
				previous->next = current->next;
			}
		}
	}

	return;
}

int get_edge_weight(GRAPH *g, int from, int to) { //done
	// your code
	int count = 0;
	ADJNODE *current = g->nodes[from]->neighbor;
	while (current != NULL && current->nid != to) {
		current = current->next;
	}
	if (current != NULL) {
		count = current->weight;
	} else {
		return INFINITY;
	}
	return count;
}

void traverse_bforder(GRAPH *g, int nid) {	//done
	// your code
	if (g == NULL) {
		return;
	}
	int n = g->order;
	int visited[n];
	int i;
	for (i = 0; i < n; i++) {
		visited[i] = 0;
	}
	ADJNODE *cur = NULL;
	QUEUE q = { 0 };
	GNODE *temp;
	GNODE *enquetemp = { 0 };
	enqueue(&q, g->nodes[nid]);
	visited[nid] = 1;
	while (q.front != NULL) {
		temp = (GNODE*) dequeue(&q);
		visited[temp->nid] = 1;
		printf("(%d %s)", temp->nid, temp->name);
		cur = temp->neighbor;
		while (cur != NULL) {
			if (visited[cur->nid] == 0) {
				enquetemp = g->nodes[cur->nid];
				enqueue(&q, enquetemp);
				visited[enquetemp->nid] = 1;

			}
			cur = cur->next;
		}

	}
	clean_queue(&q);

	return;
}

// Use auxiliary stack data structure for the algorithm
void traverse_dforder(GRAPH *g, int nid) {
	// your code
	if (g == NULL) {
		return;
	}
	int visited[g->order];
	int i;
	for (i = 0; i < g->order; i++) {
		visited[i] = 0;
	}

	STACK s = { 0 };
	push(&s, g->nodes[nid]);
	visited[nid] = 1;
	GNODE *temp;
	GNODE *stemp;
	ADJNODE *atemp;

	while (s.top != NULL) {
		temp = (GNODE*) pop(&s);
		visited[temp->nid] = 1;
		printf("(%d %s)", temp->nid, temp->name);
		atemp = temp->neighbor;
		while (atemp != NULL) {
			if (visited[atemp->nid] == 0) {
				stemp = g->nodes[atemp->nid];
				push(&s, stemp);
				visited[stemp->nid] = 1;
			}
			atemp = atemp->next;
		}
	}
	clean_stack(&s);
	return;
}

void clean_graph(GRAPH **gp) {
	int i;
	GRAPH *g = *gp;
	ADJNODE *temp, *ptr;
	for (i = 0; i < g->order; i++) {
		ptr = g->nodes[i]->neighbor;
		while (ptr != NULL) {
			temp = ptr;
			ptr = ptr->next;
			free(temp);
		}
		free(g->nodes[i]);
	}
	free(g->nodes);
	free(g);
	*gp = NULL;
}

void display_graph(GRAPH *g) {
	if (g) {
		printf("order %d ", g->order);
		printf("size %d ", g->size);
		printf("(from to weight) ");
		int i;
		ADJNODE *ptr;
		for (i = 0; i < g->order; i++) {
			//printf("\n%d:", g->nodes[i]->nid);
			ptr = g->nodes[i]->neighbor;
			while (ptr != NULL) {
				printf("(%d %d %d) ", i, ptr->nid, ptr->weight);
				ptr = ptr->next;
			}
		}
	}
}
