#include <stdlib.h>
#include <assert.h>

#include "ADTList.h"
#include "ADTQueue.h"

// Making a queue struct with a list inside 
struct queue{
	List list;
};

Queue queue_create(DestroyFunc destroy_value){
	Queue queue = malloc(sizeof(*queue));		// Allocation of queue
	queue->list = list_create(destroy_value);	// Making the queue using the list
	
	return queue;
}

int queue_size(Queue queue){
	return list_size(queue->list);	// Just return list's size
}

Pointer queue_front(Queue queue){
	return list_node_value(queue->list, list_first(queue->list));	// Return the first value of the list
}

Pointer queue_back(Queue queue){
	return list_node_value(queue->list, list_last(queue->list));	// Return the last value of the list
}

void queue_insert_back(Queue queue, Pointer value){
	list_insert_next(queue->list, list_last(queue->list), value);	// Insert value at the end of the list
}

void queue_remove_front(Queue queue){
	list_remove_next(queue->list, NULL);	// Removing a value from the start of the list
}

DestroyFunc queue_set_destroy_value(Queue queue, DestroyFunc destroy_value){
	return list_set_destroy_value(queue->list, destroy_value);
}

void queue_destroy(Queue queue){
	list_destroy(queue->list);	// Destroying the list
	free(queue);				// Freeing queue's allocated memory
}
