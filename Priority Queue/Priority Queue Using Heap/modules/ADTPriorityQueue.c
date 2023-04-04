#include <stdlib.h>
#include <assert.h>

#include "ADTPriorityQueue.h"
#include "ADTVector.h"

// PriorityQueue is a pointer to this struct
struct priority_queue {
	Vector vector;
	CompareFunc compare;
	DestroyFunc destroy_value;
};

//*** Static functions ***//

static Pointer node_value(PriorityQueue pqueue, int node_id) {
	// node_ids are 1-based, node_id is saved to node_id - 1
	return vector_get_at(pqueue->vector, node_id - 1);
}

// Swapping value of node_id1 and node_id2
static void node_swap(PriorityQueue pqueue, int node_id1, int node_id2) {
	// node_ids are 1-based, node_id is saved to node_id - 1
	Pointer value1 = node_value(pqueue, node_id1);
	Pointer value2 = node_value(pqueue, node_id2);

	vector_set_at(pqueue->vector, node_id1 - 1, value2);
	vector_set_at(pqueue->vector, node_id2 - 1, value1);
}

// Brings back balance to the heap
static void bubble_up(PriorityQueue pqueue, int node_id) {
	// Stop when we reach to the root
	if(node_id == 1){
		return;
	}

	int parent = node_id / 2;		// Parent node. node_ids are 1-based

	// If node is greater than the parent then swap and keep going up
	if(pqueue->compare(node_value(pqueue, parent), node_value(pqueue, node_id)) < 0){
		node_swap(pqueue, parent, node_id);
		bubble_up(pqueue, parent);
	}
}

// Brings back balance to the heap
static void bubble_down(PriorityQueue pqueue, int node_id){
	// Finding the children. Stop when there are no more children
	int left_child = 2 * node_id;
	int right_child = left_child + 1;

	int size = pqueue_size(pqueue);
	if(left_child > size){
		return;
	}

	// Finding the greater child
	int max_child = left_child;
	if(right_child <= size && pqueue->compare(node_value(pqueue, left_child), node_value(pqueue, right_child)) < 0){
		max_child = right_child;
	}

	// If node is less than the child then swap and keep going down
	if(pqueue->compare(node_value(pqueue, node_id), node_value(pqueue, max_child)) < 0){
		node_swap(pqueue, node_id, max_child);
		bubble_down(pqueue, max_child);
	}
}

//*** Priority Queue functions ***//

PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value){
	assert(compare != NULL);

	PriorityQueue pqueue = malloc(sizeof(*pqueue));
	pqueue->compare = compare;
	pqueue->destroy_value = destroy_value;

	// Creating a vector that will save the elements. We dont give a destroy function
	// If we give the destroy function it will be called automatically when we will
	// swap 2 elements and we dont want this to happen
	pqueue->vector = vector_create(0, NULL);

	return pqueue;
}

int pqueue_size(PriorityQueue pqueue){
	return vector_size(pqueue->vector);
}

Pointer pqueue_max(PriorityQueue pqueue){
	return node_value(pqueue, 1);		// root
}

void pqueue_insert(PriorityQueue pqueue, Pointer value){
	// Inserting the value to the end of the heap
	vector_insert_last(pqueue->vector, value);

	// All nodes are ok in the heap except the last on that may be greater than his father node. 
	// We can bring balance to the heap if we call the helper function bubble_up for the last node.
	// Last node's 1-based id is equal with the new size of heap
	bubble_up(pqueue, pqueue_size(pqueue));
}

void pqueue_remove_max(PriorityQueue pqueue){
	int last_node = pqueue_size(pqueue);
	assert(last_node != 0);

	// Destroy the value that is removed
	if(pqueue->destroy_value != NULL){
		pqueue->destroy_value(pqueue_max(pqueue));
	}

	// Swapping the last with the first and we delete it
	node_swap(pqueue, 1, last_node);
	vector_remove_last(pqueue->vector);

 	// All nodes are ok in the heap except the last on that may be smaller than his child node. 
	// We can bring balance to the heap if we call the helper function bubble_down for the last node.
	bubble_down(pqueue, 1);
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value){
	DestroyFunc old = pqueue->destroy_value;
	pqueue->destroy_value = destroy_value;
	return old;
}

void pqueue_destroy(PriorityQueue pqueue){
	// If we give the destroy function it will be automatically called at the
	// vector_destroy function
	vector_set_destroy_value(pqueue->vector, pqueue->destroy_value);
	vector_destroy(pqueue->vector);

	free(pqueue);
}