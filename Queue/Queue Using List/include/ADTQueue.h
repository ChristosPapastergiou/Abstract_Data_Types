#pragma once

#include "common_types.h"

typedef struct queue* Queue;

// Creating a queue. If destroy_value != NULL every time an item is removed list destroy it.
Queue queue_create(DestroyFunc destroy_value);

// Return queue's size
int queue_size(Queue queue);

// Return the front item of the queue...undefined result if the queue is empty
Pointer queue_front(Queue queue);

// Return the back item of the queue...undefined result if the queue is empty
Pointer queue_back(Queue queue);

// Adding value to the back of the queue
void queue_insert_back(Queue queue, Pointer value);

// Removing an the front item of the queue...undefined result if the queue is empty
void queue_remove_front(Queue queue);

// Setting up the destroy value of the queue
DestroyFunc queue_set_destroy_value(Queue queue, DestroyFunc destroy_value);

// Destroying the queue
void queue_destroy(Queue queue);
