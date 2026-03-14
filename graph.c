#include <stdlib.h>
#include <string.h>
#include "graph.h"

typedef struct Graph {
    VertexList* vertices;
    unsigned size;
} Graph;

static VertexList* reallocList(VertexList* list, unsigned size);
static bool reallocNeighbours(VertexList* list, unsigned count);
static void listFree(Graph* graph);

Graph* graphCreate(void)
{
    return calloc(1, sizeof(Graph));
}

Graph* graphRead(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        return NULL;

    Graph* graph = graphCreate();
    if (graph == NULL)
        return NULL;
    if (fscanf(file, "%u", &graph->size) != 1) {
        graphFree(&graph);
        return NULL;
    }

    VertexList* newVertices = reallocList(graph->vertices, graph->size);
    if (newVertices == NULL) {
        graphFree(&graph);
        return NULL;
    }
    memset(newVertices, 0, graph->size * sizeof(VertexList));
    graph->vertices = newVertices;

    for (unsigned idx = 0; idx < graph->size; idx++) {
        VertexList* list = &graph->vertices[idx];
        if (!reallocNeighbours(list, graph->size)) {
            graphFree(&graph);
            return NULL;
        }

        for (unsigned j = 0; j < graph->size; j++) {
            fscanf(file, "%u", &list->vertices[j]);
        }
    }

    return graph;
}

static VertexList* reallocList(VertexList* list, unsigned size)
{
    return realloc(list, size * sizeof(list[0]));
}

static bool reallocNeighbours(VertexList* list, unsigned count)
{
    unsigned* vertices = realloc(list->vertices, sizeof(list->vertices[0]) * count);
    if (vertices == NULL) {
        return false;
    }

    list->vertices = vertices;
    list->count = count;
    return true;
}

static void listFree(Graph* graph)
{
    if (graph == NULL || graph->vertices == NULL)
        return;

    for (unsigned i = 0; i < graph->size; i++)
        free(graph->vertices[i].vertices);
    free(graph->vertices);
    graph->vertices = NULL;
    graph->size = 0;
}

unsigned graphSize(Graph* graph)
{
	return graph->size;
}

void graphFree(Graph** graph)
{
	listFree(*graph);
	free(*graph);
	*graph = NULL;
}

VertexList graphGetNeighbours(Graph *graph, unsigned int vertex, bool *err) {
	if (vertex >= graph->size) {
		VertexList list = { NULL, 0 };
		*err = true;
		return list;
	}
	*err = false;
	return graph->vertices[vertex];
}
