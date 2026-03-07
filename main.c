#include <stdio.h>
#include "graph.h"

void graphPrint(Graph* graph) {
    unsigned size = graphSize(graph);
    
    for (unsigned vertex = 0; vertex < size; vertex++) {
	    bool err = false;
	    VertexList neighbours = graphGetNeighbours(graph, vertex, &err);
	    if (err) {
		    fprintf(stderr, ":c\n");
		    break;
	    }
	    printf("%d:", vertex);
	    for (unsigned i = 0; i < neighbours.count; i++) {
		    if (neighbours.vertices[i]) {
			    printf(" %d", i); 
		    }
	    }
	    printf("\n");
    }
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, "correct usage: %s <filename>\n", argv[0]);
		return 1;
	}
	char* fileName = argv[1];
	printf("before read\n");
	Graph* graph = graphRead(fileName);
	printf("after read\n");
	printf("%d\n", graphSize(graph));
	graphPrint(graph);
	// graphFree(&graph);
	return 0;
}
