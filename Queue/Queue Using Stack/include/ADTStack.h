#pragma once

#include "common_types.h"

typedef struct stack* Stack;

// Creating a Stack. If destroy_value != NULL every time an item is removed list destroy it.
Stack stack_create(DestroyFunc destroy_value);

// Return stack's size
int stack_size(Stack stack);

// Return the top item of the stack...undefined result if the queue is empty
Pointer stack_top(Stack stack);

// Inserting value to the top of the stack
void stack_insert_top(Stack stack, Pointer value);

// Removes the top value of the stack...undefined result if the queue is empty
void stack_remove_top(Stack stack);

// Setting up the destroy value of the stack
DestroyFunc stack_set_destroy_value(Stack stack, DestroyFunc destroy_value);

// Destroying the stack
void stack_destroy(Stack stack);
