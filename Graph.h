//
//  Graph.h
//  Graph
//
//  Created by Aman Mangalore on 2/23/15.
//  Copyright (c) 2015 Aman Mangalore. All rights reserved.
//


#if !defined(_GRAPH_H_INCLUDE_)
#define _GRAPH_H_INCLUDE_
#define INF -1
#define NIL 0
#define WHITE 0
#define GREY 1
#define BLACK 2

#include "List.h"

typedef struct GraphObj* Graph;
Graph newGraph(int n);
void freeGraph(Graph* pG);
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void printGraph(FILE* out, Graph G);
#endif
