#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "record.h"

#define MAX_SIZE 100

record** queue[MAX_SIZE];
int front = -1, rear = -1;

void cleanQueue() {
    front = rear = -1;
}

void enqueue(record **node) {
    if(rear == MAX_SIZE - 1) {
        printf("Queue size is full.\n");
        return;
    }

    if(front == -1) front = 0;
    rear++;
    queue[rear] = node;
}

record** dequeue() {
    record** tmp = NULL;

    if(is_empty()) {
        printf("Queue size is full.\n");
        return NULL;
    }

    tmp = queue[front];
    front++;

    if(front >= rear && rear == MAX_SIZE - 1) {
        cleanQueue();
    }
    return tmp;
}


record** peek() {
    record** tmp = NULL;

    if(is_empty()) {
        printf("Queue size is full.\n");
        return NULL;
    }
    tmp = queue[front];
    return tmp;
}

int is_empty() {
    return (front == -1 || front > rear) ? 1 : 0;
}
