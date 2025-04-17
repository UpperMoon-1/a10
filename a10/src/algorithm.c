/**
 * -------------------------------------
 * @file  algorithm.c
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
#include "heap.h"
#include "edgelist.h"
#include "algorithm.h"

EDGELIST* mst_prim(GRAPH *g, int start) { //done
	// your code
	if (g == NULL) {
		return NULL;
	}
	int i;
	int heapindex;
	int n = g->order;
	int T[n];
	int parent[n];
	for (i = 0; i < n; i++)
		T[i] = 0;
	for (i = 0; i < n; i++)
		parent[i] = -1;
	HEAPDATA hn;
	HEAP *h = new_heap(4);
	T[start] = 1;
	ADJNODE *temp = g->nodes[start]->neighbor;
	while (temp) {
		hn.key = temp->weight;
		hn.value = temp->nid;
		heap_insert(h, hn);
		parent[temp->nid] = start;
		temp = temp->next;
	}
	EDGELIST *mst = new_edgelist();
	while (h->size > 0) {
		hn = heap_extract_min(h);
		i = hn.value;
		T[i] = 1;
		insert_edge_end(mst, parent[i], i, hn.key);
		temp = g->nodes[i]->neighbor;
		while (temp) {
			heapindex = heap_search_value(h, temp->nid);
			if (heapindex >= 0) {
				if (T[temp->nid] == 0 && temp->weight < h->hda[heapindex].key) {
					heap_change_key(h, heapindex, temp->weight);
					parent[temp->nid] = i;
				}
			} else {
				if (T[temp->nid] == 0) {
					hn.key = temp->weight;
					hn.value = temp->nid;
					heap_insert(h, hn);
					parent[temp->nid] = i;
				}

			}
			temp = temp->next;
		}
	}
	return mst;

}

EDGELIST* spt_dijkstra(GRAPH *g, int start) {	//done
	// your code
	if (g == NULL) {
		return NULL;
	}
	EDGELIST *spt = new_edgelist();
	int i;
	int heapindex;
	int u;
	int n = g->order;
	int T[n];
	int v;
	int nd;
	int parent[n];
	int label[n];
	HEAPDATA hn;
	for (i = 0; i < n; i++) {
		T[i] = 0;
		label[i] = 9999;
	}
	HEAP *h = new_heap(4);
	ADJNODE *temp = g->nodes[start]->neighbor;
	label[start] = 0;
	T[start] = 1;
	while (temp) {
		hn.key = temp->weight + label[start];
		hn.value = temp->nid;
		heap_insert(h, hn);
		parent[temp->nid] = start;
		temp = temp->next;
	}
	while (h->size > 0) {
		hn = heap_extract_min(h);
		u = hn.value;
		T[u] = 1;
		label[u] = hn.key;
		insert_edge_end(spt, parent[u], u, label[u] - label[parent[u]]);

		temp = g->nodes[u]->neighbor;
		while (temp) {
			v = temp->nid;
			nd = label[u] + temp->weight;
			if (T[v] == 0 && nd < label[v]) {
				label[v] = nd;
				parent[v] = u;
				heapindex = heap_search_value(h, v);
				if (heapindex >= 0) {
					heap_change_key(h, heapindex, nd);
				} else {
					hn.key = nd;
					hn.value = v;
					heap_insert(h, hn);
				}
			}
			temp = temp->next;
		}
	}
	return spt;
}

EDGELIST* sp_dijkstra(GRAPH *g, int start, int end) {
	// your code
	EDGELIST *sp = new_edgelist();
	if (g == NULL) {
		return NULL;
	}
	EDGELIST *spt = new_edgelist();
	int i;
	int heapindex;
	int u;
	int n = g->order;
	int T[n];
	int v;
	int nd;
	int parent[n];
	int label[n];
	HEAPDATA hn;
	for (i = 0; i < n; i++) {
		T[i] = 0;
		label[i] = 9999;
	}
	HEAP *h = new_heap(4);
	ADJNODE *temp = g->nodes[start]->neighbor;
	label[start] = 0;
	T[start] = 1;
	while (temp) {
		hn.key = temp->weight + label[start];
		hn.value = temp->nid;
		heap_insert(h, hn);
		parent[temp->nid] = start;
		temp = temp->next;
	}
	while (h->size > 0) {
		hn = heap_extract_min(h);
		u = hn.value;
		T[u] = 1;
		label[u] = hn.key;
		insert_edge_end(spt, parent[u], u, label[u] - label[parent[u]]);

		temp = g->nodes[u]->neighbor;
		while (temp) {
			v = temp->nid;
			nd = label[u] + temp->weight;
			if (T[v] == 0 && nd < label[v]) {
				label[v] = nd;
				parent[v] = u;
				heapindex = heap_search_value(h, v);
				if (heapindex >= 0) {
					heap_change_key(h, heapindex, nd);
				} else {
					hn.key = nd;
					hn.value = v;
					heap_insert(h, hn);
				}
			}
			temp = temp->next;
		}
	}
	i = end;
	while (1) {
		if (i == start) {
			break;
		}
		insert_edge_start(sp, parent[i], i, label[i] - label[parent[i]]);
		i = parent[i];
	}
	return sp;
}
