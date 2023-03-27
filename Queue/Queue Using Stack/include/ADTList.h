#pragma once

#include "common_types.h"

// Virtual nodes before the first *LIST_BOF* and after the last *LIST_EOF*
#define LIST_BOF (ListNode)0
#define LIST_EOF (ListNode)0

typedef struct list* List;
typedef struct list_node* ListNode;

// Creating a list. If destroy_value != NULL the every time an item is removed list destroy it.
List list_create(DestroyFunc destroy_value);

// Return list's size
int list_size(List list);

// Adding a new node after *ListNode node* with value *Pointer value*
void list_insert_next(List list, ListNode node, Pointer value);

// Removing a node after *ListNode node*
void list_remove_next(List list, ListNode node);

// Returning the first value equal to *Pointer value* using *CompareFunc compare* 
Pointer list_find(List list, Pointer value, CompareFunc compare);

// Changing the destroy_value
DestroyFunc list_set_destroy_value(List list, DestroyFunc destroy_value);

// Freeing all the memory and destroying the list
void list_destroy(List list);

// Returning the first and last node or LIST_BOF / LIST_EOF if list is empty
ListNode list_first(List list);
ListNode list_last(List list);

// Returning the node after *Listnode node* or LIST_EOF if it is the last
ListNode list_next(List list, ListNode node);

// Returning the value of *Listnode node*
Pointer list_node_value(List list, ListNode node);

// Finding and returning the first node whos value is equal to *Pointer value*...LIST_EOF if the item is not in the list
ListNode list_find_node(List list, Pointer value, CompareFunc compare);

// Returning the item in *pos* (pos >= 0 ή pos <>=> size)
Pointer list_get_at(List list, int pos);

// Removing *ListNode node*
void list_remove(List list, ListNode node);

// Copying *List to_append* to *List list* and destroying to_append
void list_append(List list, List to_append);