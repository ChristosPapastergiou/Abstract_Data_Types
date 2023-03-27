#include <stdlib.h>
#include <assert.h>

#include "ADTList.h"

// List is pointer to this struct
struct list{
	int size;					// Saving the size so we can have the best complexity to list_size function
	ListNode last;				// Pointer to the last node (to dummy if list's size is zero)
	ListNode dummy;				// Using dummy node
	DestroyFunc destroy_value;
};

struct list_node{
	ListNode next;		// Pointer to next
	Pointer value;		// Node's value
};

List list_create(DestroyFunc destroy_value){
	// Creating the struct
	List list = malloc(sizeof(*list));
	list->size = 0;
	list->destroy_value = destroy_value;

	// Using dummy node. Its very helpfull
	list->dummy = malloc(sizeof(*list->dummy));
	list->dummy->next = NULL;

	// Zero list size means dummy is the last too
	list->last = list->dummy;

	return list;
}

int list_size(List list){
	return list->size;
}

ListNode list_first(List list){
	// Dummy's next is the first
	return list->dummy->next;
}

ListNode list_last(List list){
	if(list->last == list->dummy){
		return LIST_EOF;
	}else{
		return list->last;
	}
}

ListNode list_next(List list, ListNode node){
	assert(node != NULL);
	return node->next;
}

Pointer list_node_value(List list, ListNode node){
	assert(node != NULL);
	return node->value;
}

void list_insert_next(List list, ListNode node, Pointer value){
	// If node is NULL just insert after dummy node
	if (node == NULL) node = list->dummy;

	// Making a new node
	ListNode new = malloc(sizeof(*new));
	new->value = value;

	// Linking the nodes
	new->next = node->next;
	node->next = new;

	// Increase size and making sure about who is the last node
	list->size++;
	if (list->last == node) list->last = new;
}

void list_remove_next(List list, ListNode node){
	// If node is NULL jest remove after dummy
	if (node == NULL) node = list->dummy;

	ListNode removed = node->next;
	assert(removed != NULL);

	if(list->destroy_value != NULL) list->destroy_value(removed->value);

	// Linking the nodes before free
	node->next = removed->next;

	free(removed);

	// Like insert
	list->size--;
	if(list->last == removed) list->last = node;
}

ListNode list_find_node(List list, Pointer value, CompareFunc compare){
	// Using the compare function to be able to find the node we want
	for (ListNode node = list->dummy->next; node != NULL; node = node->next){
		if(compare(value, node->value) == 0) return node;
	}
	return NULL;	// The item is not in the list
}

Pointer list_find(List list, Pointer value, CompareFunc compare){
	ListNode node = list_find_node(list, value, compare);
	return node == NULL ? NULL : node->value;
}

DestroyFunc list_set_destroy_value(List list, DestroyFunc destroy_value){
	DestroyFunc old = list->destroy_value;
	list->destroy_value = destroy_value;
	return old;
}

void list_destroy(List list){
	// While loop to free all the nodes. Dummy too
	ListNode node = list->dummy;
	while (node != NULL) {
		ListNode next = node->next;

		if(node != list->dummy && list->destroy_value != NULL){
			list->destroy_value(node->value);
		}

		free(node);
		node = next;
	}

	free(list);
}

Pointer list_get_at(List list, int pos){
	if(pos >= 0 && pos <= list->size){
		int i = -1;
		for(ListNode node=list->dummy->next; node!=NULL; node=node->next){
			i++;
			if(i == pos) return node->value;
		}
	}

	return NULL; // The item is not in the set
}

void list_remove(List list, ListNode node){
	// Making a listnode to save the previous node
	ListNode previous;

	for(ListNode new_node=list->dummy; new_node!=NULL; new_node=new_node->next){
		if(node == new_node->next){
			previous = (new_node == list->dummy ? NULL : new_node);
			break;
		}
	}

	list_remove_next(list, previous);
}

void list_append(List list, List to_append){
	// This way the complexity is better than crossing all the list
	// and copying one by one
	if(list->size == 0 && to_append->size != 0){
		list->dummy->next = to_append->dummy->next;
		list->last = to_append->last;
		list->size = list->size + to_append->size;
		free(to_append->dummy); 
		free(to_append);
	}else if(list->size != 0 && to_append->size != 0){
		list->last->next = to_append->dummy->next;
		list->size = list->size + to_append->size;
		free(to_append->dummy);
		free(to_append);
	}else if(to_append->size == 0){
		free(to_append->dummy); 
		free(to_append);
	}
}