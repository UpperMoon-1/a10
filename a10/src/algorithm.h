/**
 * -------------------------------------
 * @file  algorithm.h
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-23
 *
 * -------------------------------------
 */
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "edgelist.h"
#include "graph.h"

EDGELIST* mst_prim(GRAPH *g, int start);
EDGELIST* spt_dijkstra(GRAPH *g, int start);
EDGELIST* sp_dijkstra(GRAPH *g, int start, int end);

#endif
