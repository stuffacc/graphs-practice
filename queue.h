#pragma once
#include <stdbool.h>

typedef struct Queue Queue;

Queue* createQueue(void);
void freeQueue(Queue** queue);

bool enqueue(Queue* queue, int value);
int dequeue(Queue* queue);

bool isEmptyQueue(Queue* queue);