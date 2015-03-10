#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

void printling(FILE* output, Graph H, List path, int through);

int main (int argc, char * argv[]) {
    FILE *output;
    
    /* check command line for correct number of arguments */
    if( argc != 2 ) {
        printf("Usage: %s outfile\n", argv[0]);
        exit(1);
    }
    
    output = fopen(argv[1], "w");
    if(output==NULL){
        printf("Unable to open file for writing\n");
        exit(1);
    }
    int n = 7;
    int through;
    Graph H = newGraph(n);
    List path = newList();
    addEdge(H, 1, 4);
    addEdge(H, 1, 5);
    addEdge(H, 4, 5);
    addEdge(H, 2, 3);
    addEdge(H, 2, 6);
    addEdge(H, 3, 7);
    addEdge(H, 6, 7);
    printGraph(output, H);
    BFS(H, 2);
    through = 7;
    getPath(path, H, through);
    printling(output, H, path, through);
    BFS(H, 3);
    clear1(path);
    through = 6;
    getPath(path, H, through);
    printling(output, H, path, through);
    BFS(H, 1);
    clear1(path);
    through = 7;
    getPath(path, H, through);
    printling(output, H, path, through);
    freeList(&path);
    freeGraph(&H);
    fclose(output);
    return 0;
}

void printling(FILE* output, Graph H, List path, int through){
    fprintf(output,"\n");
    fprintf(output, "The distance from %d to %d is ", getSource(H), through);
    if ( front(path) == NIL ) {
        fprintf(output, "infinity\n");
        fprintf(output, "No %d-%d path exists", getSource(H), through);
    }else {
        fprintf(output, "%d\n", getDist(H, through));
        fprintf(output, "A shortest %d-%d path is: ", getSource(H), through);
        printList(output, path);
    }
    fprintf(output,"\n");
}
