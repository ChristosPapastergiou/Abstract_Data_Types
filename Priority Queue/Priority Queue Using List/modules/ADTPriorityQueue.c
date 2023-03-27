#include <stdlib.h>
#include <assert.h>

#include "ADTPriorityQueue.h"
#include "ADTList.h"


// PriorityQueue is a pointer to this struct
struct priority_queue{
	List list;
	CompareFunc compare;		// Queue's arrangement
	DestroyFunc destroy_value;
};

PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value){
	// Allocate space for the queue
	PriorityQueue pqueue = malloc(sizeof(*pqueue));

	// Just putting the destory value and it will automatically 
	// will be called whenever it is necessary
	pqueue->list = list_create(destroy_value);
	pqueue->compare = compare;

	return pqueue;
}

int pqueue_size(PriorityQueue pqueue){
	return list_size(pqueue->list);
}

Pointer pqueue_max(PriorityQueue pqueue){
	if(pqueue_size(pqueue) > 0){
		return list_node_value(pqueue->list, list_first(pqueue->list));
	}
		
	return NULL;
}

void pqueue_insert(PriorityQueue pqueue, Pointer value){
	// If list is empty just insert it. If it is not we will use
	// compare function to insert it to the right place
	if(pqueue_size(pqueue) == 0){
		list_insert_next(pqueue->list, LIST_BOF, value);
	}else{
		if(pqueue->compare(value, list_node_value(pqueue->list, list_first(pqueue->list))) > 0){
			list_insert_next(pqueue->list, LIST_BOF, value);
		}else{
			for(ListNode node = list_first(pqueue->list); node != LIST_EOF; node = list_next(pqueue->list, node)){
				if(list_next(pqueue->list, node) == LIST_EOF){
					list_insert_next(pqueue->list, list_last(pqueue->list), value);	
					break;
				}
				if(pqueue->compare(value, list_node_value(pqueue->list, node)) < 0 && pqueue->compare(value, list_node_value(pqueue->list, list_next(pqueue->list, node))) > 0){
					list_insert_next(pqueue->list, node, value);
					break;
				}
			}
		}
	}	
}

void pqueue_remove_max(PriorityQueue pqueue){
	// The first element of the list is the biggest
	list_remove_next(pqueue->list, LIST_BOF);
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value) {
	return list_set_destroy_value(pqueue->list, destroy_value);
}

void pqueue_destroy(PriorityQueue pqueue){
	list_destroy(pqueue->list);
	free(pqueue);
}
