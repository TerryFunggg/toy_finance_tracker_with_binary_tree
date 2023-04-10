#ifndef RECORD_H
#define RECORD_H
#include <time.h>

typedef struct Record record;

struct Record {
    record *left, *right;
    int id;
    int amount;
    char desc[100];
    time_t timestamp;
};
#endif // RECORD_H
