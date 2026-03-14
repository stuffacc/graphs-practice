#include "queue.h"
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;


typedef struct Queue {
    Node* head;
    Node* tail;
} Queue;



Queue* createQueue(void) {
    return calloc(1, sizeof(Queue));
}

void freeQueue(Queue** queue) {
    while (!isEmptyQueue(*queue)) {
        dequeue(*queue);
    }

    free(*queue);
    *queue = NULL;
}

bool enqueue(Queue* queue, int value) {
    Node* node = malloc(sizeof(Node));

    if (node == NULL) {
        return false;
    }

    node->value = value;
    node->next = NULL;

    if (isEmptyQueue(queue)) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }

    return true;
}

int dequeue(Queue* queue) {
    if (isEmptyQueue(queue)) {
        return -1;
    }

    Node* head = queue->head;
    int value = head->value;
    queue->head = head->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(head);   
    return value;
}


bool isEmptyQueue(Queue* queue) {
    return (queue->head == NULL) && (queue->tail == NULL);
}