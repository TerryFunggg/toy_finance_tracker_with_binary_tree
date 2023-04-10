#ifndef QUEUE_H
#define QUEUE_H
#include "record.h"

void cleanQueue();
void enqueue(record **node);
record** dequeue();
record** peek();
int is_empty();

#endif // QUEUE_H
