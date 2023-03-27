#pragma once

#include "common_types.h"

typedef struct stack* Stack;

Stack stack_create(DestroyFunc destroy_value);

int stack_size(Stack stack);

Pointer stack_top(Stack stack);

void stack_insert_top(Stack stack, Pointer value);

void stack_remove_top(Stack stack);

DestroyFunc stack_set_destroy_value(Stack stack, DestroyFunc destroy_value);

void stack_destroy(Stack stack);
