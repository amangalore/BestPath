//
//  main.c
//  Graph
//
//  Created by Aman Mangalore on 2/23/15.
//  Copyright (c) 2015 Aman Mangalore. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define black 19999991
#define white 10000001
#define grey -6666669

//structure Graph
struct GraphObj {
    List* arr;
    int* color;
    int* distance;
    int* parent;
    int O;
    int sz;
    int src;
};

//Constructor
Graph newGraph(int n) {
    Graph G = malloc(sizeof(struct GraphObj));
    G->arr = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->distance = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->O = n;
    G->sz = 0;
    G->src = NIL;
    int a;
    for (a = 1; a <= n; ++a){
        G->arr[a] = newList();
        G->color[a] = white;
        G->parent[a] = NIL;
        G->distance[a] = INF;
    }
    return (G);
    
}

//Deconstructor
void freeGraph(Graph* pG) {
    Graph freed = *pG;
    int i;
    for(i = 0; i < (freed->O) + 1; i++){
        freeList(&(freed->arr[i]));
    }
    free(freed->arr);
    free(freed->color);
    free(freed->parent);
    free(freed->distance);
    free(*pG);
    *pG = NULL;
}

//gets the order of Graph G
int getOrder(Graph G){
    if (G == NULL){
        printf("Graph is NULL");
        exit(1);
    }
    return G->O;
}

//gets the size of Graph G
int getSize(Graph G){
    if (G == NULL){
        printf("Graph is NULL");
        exit(1);
    }
    return G->sz;
}

//gets the source of Graph G
int getSource(Graph G){
    if (G == NULL){
        printf("Graph is NULL");
        exit(1);
    }
    return G->src;
}

//return the parent of vertex u in the BFS tree
int getParent(Graph G, int u){
    if (G == NULL){
        printf("Graph is NULL");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Error: index is out of array");
        return 0;
    }
    return G->parent[u];
}

//return the distance from the most recent BFS source to vertex u
int getDist(Graph G, int u){
    if (G == NULL){
        printf("Graph is NULL");
        exit(1);
    }
    if(getSource(G) == NIL){
        return INF;
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Error: index is out of array");
        return 0;
    }
    return G->distance[u];
}

//appends to List L the shortest path from the source to vertex u
void getPath(List L, Graph G, int u){
    if (L == NULL){
        printf("List is NULL");
        exit(1);
    }
    if (G == NULL){
        printf("Graph is NULL");
        exit(1);
    }
    if (u > getOrder(G) || u < 1){
        printf("Error: index is out of array");
        return;
    }
    if (getSource(G) == NIL){
        printf("Error: Source is NIL");
    }
    
    int s = G->src;
    if (u == s){
        prepend(L, s);
        return;
    } else if (G->parent[u] == NIL) {
        append(L, NIL);
    } else {
    prepend(L,u);
    getPath(L, G, G->parent[u]);
    }   
}

//removes all edges from Graph G
void makeNULL(Graph G){
    int i;
    for(i = 0; i < G->O + 1; i++){
        clear1(G->arr[i]);
    }
}

//inserts a new edge joining vertex u to vertex v
void addEdge(Graph G, int u, int v){
    if (G == NULL){
        printf("Graph is NULL");
        exit(1);
    }
    if (u > getOrder(G) || u < 1){
        printf("Error: index is out of array");
        return;
    }
    if (v > getOrder(G) || v < 1){
        printf("Error: index is out of array");
        return;
    }
    append(G->arr[u], v);
    append(G->arr[v], u);
    G->sz++;
}

//inserts a new directed edge from vertex u to vertex v
void addArc(Graph G, int u, int v){
    if (G == NULL){
        printf("Graph is NULL");
        exit(1);
    }
    if (u > getOrder(G) || u < 1){
        printf("Error: index is out of array");
        exit(1);
    }
    if (v > getOrder(G) || v < 1){
        printf("Error: index is out of array");
        exit(1);
    }
    append(G->arr[u], v);
    G->sz++;
}

//runs BFS algorithm and sets up color, distance, parent, and source fields of G
void BFS(Graph G, int s){
    int u;
    for (u = 0; u < G->O + 1; u++){
        if(u != s){
            G->color[u] = white;
            G->distance[u] = INF;
            G->parent[u] = NIL;
        }
    }
    G->src = s;
    G->color[s] = grey;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    prepend(Q, s);
    while(length(Q) > 0){
        int u = back(Q);
        deleteBack(Q);
        List adj = G->arr[u];
        for(moveTo(adj, 0);getIndex(adj) >= 0 ; moveNext(adj)){
            int vertex = getElement(adj);
            if(G->color[vertex] == white){
                G->color[vertex] = grey;
                G->distance[vertex] = G->distance[u] + 1;
                G->parent[vertex] = u;
                prepend(Q, vertex);
            }
        }
        G->color[u] = black;
    }
    freeList(&Q);
}

//prints the adjacency list of graph G
void printGraph(FILE* out, Graph G){
    if (G == NULL){
        printf("Graph is null");
        exit(1);
    }
    int a;

    for (a = 1; a <= getOrder(G); ++a){
        fprintf(out, "%d: ", a);
        printList(out, G->arr[a]);
        fprintf(out, "\n");
    }
}


