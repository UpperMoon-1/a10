/**
 * -------------------------------------
 * @file  graph_ptest.c
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
#include "graph.h"

int order = 5;

typedef struct vertex {
	int nid;
	char name[10];
} VERTEX;

typedef struct edge {
	int from;
	int to;
	int weight;
} EDGE;

VERTEX node_tests[] = { { 0, "A" }, { 1, "B" }, { 2, "C" }, { 3, "D" },
		{ 4, "E" } };

EDGE edge_tests[] = { { 0, 1, 7 }, { 0, 2, 3 }, { 1, 2, 4 }, { 1, 3, 9 }, { 1,
		4, 11 }, { 2, 3, 10 } };

GRAPH *graph = NULL;

void test_new_graph() {
	printf("------------------\n");
	printf("Test: new_graph\n\n");
	graph = new_graph(order);

	int n = sizeof node_tests / sizeof *node_tests;
	for (int i = 0; i < n; i++) {
		if (node_tests[i].nid < order)
			strcpy(graph->nodes[node_tests[i].nid]->name, node_tests[i].name);
	}

	printf("display_graph(): ");
	display_graph(graph);
	printf("\n");
}

void test_insert_edge_graph() {
	printf("------------------\n");
	printf("Test: insert_edge_graph\n\n");
	int n = sizeof edge_tests / sizeof *edge_tests;
	for (int i = 0; i < n; i++) {
		insert_edge_graph(graph, edge_tests[i].from, edge_tests[i].to,
				edge_tests[i].weight);
		printf("%s(%d %d %d): ", "insert_edge_graph", edge_tests[i].from,
				edge_tests[i].to, edge_tests[i].weight);
		display_graph(graph);
		printf("\n");
	}

}

void test_get_edge_weight() {
	printf("------------------\n");
	printf("Test: get_edge_weigh\n\n");
	int n = sizeof edge_tests / sizeof *edge_tests;
	for (int i = 0; i < n; i++) {
		printf("%s(%d %d): %d\n", "get_edge_weight", edge_tests[i].from,
				edge_tests[i].to,
				get_edge_weight(graph, edge_tests[i].from, edge_tests[i].to));
	}
	printf("\n");
}

void test_traverse_bforder() {
	printf("------------------\n");
	printf("Test: test_traverse_bforder\n\n");
	for (int i = 0; i < graph->order; i++) {
		printf("%s(%d): ", "traverse_bforder", i);
		traverse_bforder(graph, i);
		printf("\n");
	}
	printf("\n");
}

void test_traverse_dforder() {
	printf("------------------\n");
	printf("Test: test_traverse_dforder\n\n");
	for (int i = 0; i < graph->order; i++) {
		printf("%s(%d): ", "traverse_dforder", i);
		traverse_dforder(graph, i);
		printf("\n");
	}
	printf("\n");
}

void test_delete_edge_graph() {
	printf("------------------\n");
	printf("Test: test_delete_edge_graph\n\n");
	int n = sizeof edge_tests / sizeof *edge_tests;
	for (int i = 0; i < n; i++) {
		delete_edge_graph(graph, edge_tests[i].from, edge_tests[i].to);
		printf("%s(%d %d): ", "delete_edge_graph", edge_tests[i].from,
				edge_tests[i].to);
		display_graph(graph);
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char *args[]) {
	test_new_graph();
	test_insert_edge_graph();
	test_get_edge_weight();
	test_traverse_bforder();
	test_traverse_dforder();
	test_delete_edge_graph();
	clean_graph(&graph);
	return 0;
}

