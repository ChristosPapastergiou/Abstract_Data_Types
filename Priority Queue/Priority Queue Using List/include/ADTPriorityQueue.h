#pragma once

#include "common_types.h"

typedef struct priority_queue* PriorityQueue;

// Creating a queue. If destroy_value != NULL every time an item is removed list destroy it.
PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value);

// Returning the size of the queue
int pqueue_size(PriorityQueue pqueue);

// Returning the greater element of the queue...undefined result if the queue is empty
Pointer pqueue_max(PriorityQueue pqueue);

// Inserting value to the queue
void pqueue_insert(PriorityQueue pqueue, Pointer value);

// Removing the greater value of the queue...undefined result if the queue is empty
void pqueue_remove_max(PriorityQueue pqueue);

// Setting up the destroy value of the queue
DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value);

// Destroying the queue
void pqueue_destroy(PriorityQueue pqueue);