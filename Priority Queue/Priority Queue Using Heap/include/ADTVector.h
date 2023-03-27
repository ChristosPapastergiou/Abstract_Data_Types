#pragma once

#include "common_types.h"

typedef struct vector* Vector;

// Creating and returning a vector with all elements null
// If destroy_value != NULL, then the destroy_value(value) is called every time an element is changing or has been removed
Vector vector_create(int size, DestroyFunc destroy_value);

// Returns vector's size
int vector_size(Vector vec);

// Insert element at vector and size + 1
void vector_insert_last(Vector vec, Pointer value);

// Removing the last element and size - 1...undefined result if vector is empty
void vector_remove_last(Vector vec);

// Returns element of pos position...undefined result if pos >= size || pos < 0 
Pointer vector_get_at(Vector vec, int pos);

// Changing the element at pos position to value...undefined result if pos >= size || pos < 0 
void vector_set_at(Vector vec, int pos, Pointer value);

// Find the first element in vector that equals the pointer value
// Compare function must be used. If empty then NULL
Pointer vector_find(Vector vec, Pointer value, CompareFunc compare);

DestroyFunc vector_set_destroy_value(Vector vec, DestroyFunc destroy_value);

// Freeing all the memory and destroying the vector
void vector_destroy(Vector vec);

// Virtual nodes that are before the first element (VECTOR_BOF) and after the last (VECTOR_EOF)
#define VECTOR_BOF (VectorNode)0
#define VECTOR_EOF (VectorNode)0

typedef struct vector_node* VectorNode;

// Return the first and last element of vector. VECTOR_EOF or VECTOR_BOF if vector is empty
VectorNode vector_first(Vector vec);
VectorNode vector_last(Vector vec);

// Return the next or the previous node from VectorNode node
VectorNode vector_next(Vector vec, VectorNode node);
VectorNode vector_previous(Vector vec, VectorNode node);

// Returns node value
Pointer vector_node_value(Vector vec, VectorNode node);

// Find the first element in vector that equals the pointer value
// Compare function must be used. If there is not such a value then it returns VECTOR_EOF
VectorNode vector_find_node(Vector vec, Pointer value, CompareFunc compare);

