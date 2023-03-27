#include <stdlib.h>
#include <assert.h>

#include "ADTList.h"
#include "ADTStack.h"

Stack stack_create(DestroyFunc destroy_value){
	List list = list_create(destroy_value); // list_create returns a List. We cast the list as a stack
	return (Stack) list;
}

int stack_size(Stack stack){
	List list = (List) stack;    // Stack in reality is a List
	return list_size(list);
}

Pointer stack_top(Stack stack){
	List list = (List) stack;
	return list_node_value(list, list_first(list));
}

void stack_insert_top(Stack stack, Pointer value){
	List list = (List) stack;
	list_insert_next(list, NULL, value);
}

void stack_remove_top(Stack stack){
	List list = (List) stack;
	list_remove_next(list, NULL);
}

DestroyFunc stack_set_destroy_value(Stack stack, DestroyFunc destroy_value){
	List list = (List) stack;
	return list_set_destroy_value(list, destroy_value);
}

void stack_destroy(Stack stack){
	List list = (List) stack;
	list_destroy(list);
}