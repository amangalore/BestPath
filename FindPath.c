#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Graph.h"
#define MAX_LEN 165

int main(int argc, char* argv[]){
	char word[MAX_LEN];
	if (argc != 3){
		printf("<FindPath> <input> <output>");
		exit(1);
	}

int begin = 0;
FILE* in = fopen(argv[1], "r");
FILE* out = fopen(argv[2], "w");
if (in == NULL){
	printf(" can't open file\n");
	return 1;
}
else if (out == NULL){
	printf("can't open file");
	return 1;
}
    fgets(word, MAX_LEN, in);
int vert = 0;
sscanf(word, "%d", &vert);
Graph G = newGraph(vert);
while (fgets(word, MAX_LEN, in) != NULL) {
	int firstvertex = 0;
	int secondvertex = 0;
	sscanf(word, "%d %d", &firstvertex, &secondvertex);
	if(firstvertex == 0 && secondvertex == 0){
		break;
	}
	addEdge(G, firstvertex, secondvertex);
}
printGraph(out, G);
List L;
while(fgets(word, MAX_LEN, in) != NULL){
	int firstvertex = 0;
	int secondvertex = 0;
	begin++;
	sscanf(word, "%d %d", &firstvertex, &secondvertex);
	if (firstvertex == 0 && secondvertex == 0){
		break;
	}
	if(begin != 1){
		fprintf(out, "\n");
	}
	BFS(G, firstvertex);
	int distance = getDist(G, secondvertex);
	fprintf(out, "The distance from %d to %d is ", firstvertex, secondvertex);
	if(distance == -255){
		fprintf(out, "infinity\n");
	}
	else{
		fprintf(out, "%d\n", distance);
	}
	L = newList();
	getPath(L, G, secondvertex);
	if(front(L) == -254){
		fprintf(out, "no %d-%d path exists", firstvertex, secondvertex);
	}
	else{
		fprintf(out, "A shortest %d-%d path is: ", firstvertex, secondvertex);
		printList(out, L);
	}
    fprintf(out, "\n");

    
	freeList(&L);
    }
	
    fprintf(out, "\n");
	freeGraph(&G);
	fclose(in);
	fclose(out);
	return(0);
}