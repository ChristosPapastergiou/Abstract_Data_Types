#include <stdlib.h>
#include <assert.h>

#include "ADTQueue.h"
#include "ADTStack.h"

struct queue {
	Stack first_stack;      // We will use two stacks to be more efficient
    Stack second_stack;
	Pointer front;          // Pointer for the first value of the queue (last of stack)
    Pointer back;           // Pointer for the last value of the queue (first of stack)
};

Queue queue_create(DestroyFunc destroy_value){
	Queue queue = malloc(sizeof(*queue));               // Allocation for the queue
	queue->first_stack = stack_create(destroy_value);   // Making the first stack
    queue->second_stack = stack_create(destroy_value);  // Making the second stack

	return queue;
}

int queue_size(Queue queue){
	return stack_size(queue->first_stack) + stack_size(queue->second_stack);    // Queue size is the size of the two stacks
}

Pointer queue_front(Queue queue){
    // Two stacks means that the first value of the queue is the last value of 
    // the first stack if its not empty or the first value of the second 
    // stack if first one is empty
	if(stack_size(queue->second_stack) > 0){
        return stack_top(queue->second_stack);
	}else if(stack_size(queue->first_stack) > 0){
        return queue->front;
    }
	
	return NULL;    // Null if the queue is empty
}

Pointer queue_back(Queue queue){
    // Two stacks means that the last value of the queue is the first value of 
    // the first stack if its not empty or the last value of the second 
    // stack if first one is empty
	if(stack_size(queue->first_stack) > 0){
		return stack_top(queue->first_stack);
	}else if(stack_size(queue->second_stack) > 0){
        return queue->back;
    }

	return NULL;    // Null if the queue is empty
}

void queue_insert_back(Queue queue, Pointer value){
	stack_insert_top(queue->first_stack, value);
	
	if(stack_size(queue->first_stack) == 1){    // The pointer to the first value of queue
		queue->front = value;
	}
}

void queue_remove_front(Queue queue){
    // If second stack is empty we will take the elements of the first stack
    // and we will put them in the second stack and delete them from the first
    if(stack_size(queue->second_stack) > 0){
        stack_remove_top(queue->second_stack);
    }else if(stack_size(queue->second_stack) == 0){
        while(stack_size(queue->first_stack) > 0){
            Pointer val = stack_top(queue->first_stack);
            stack_insert_top(queue->second_stack, val);

            if(stack_size(queue->second_stack) == 1){
                queue->back = val;
            }
            
            stack_remove_top(queue->first_stack);
        }
        stack_remove_top(queue->second_stack);
    }
}

DestroyFunc queue_set_destroy_value(Queue queue, DestroyFunc destroy_value){
	return stack_set_destroy_value(queue->first_stack, destroy_value);
}

void queue_destroy(Queue queue){
	stack_destroy(queue->first_stack);  // Destroying the first stack
    stack_destroy(queue->second_stack); // Destroying the second stack
	
	free(queue);    // Freeing the memory allocated for the queue
}
