#include <stdlib.h>
#include <assert.h>

#include "ADTVector.h"

#define VECTOR_MIN_CAPACITY 10	// Lets take 10 as a minimum capacity to start the vector

struct vector_node{
	Pointer value;				// Node's value
};

// Vector points to this struct
struct vector{
	int size;					// Number of elements
	int capacity;				// The capacity we have...Must be capacity >= size
	VectorNode array;
	DestroyFunc destroy_value;	// Function for the destruction of an element
};

Vector vector_create(int size, DestroyFunc destroy_value){
	Vector vec = malloc(sizeof(*vec));	// Allocate memory for the vector

	vec->size = size;
	vec->destroy_value = destroy_value;

	// To skip many resizes we allocate in the begining min vector capacity
	vec->capacity = size < VECTOR_MIN_CAPACITY ? VECTOR_MIN_CAPACITY : size;
	vec->array = calloc(vec->capacity, sizeof(*vec->array));

	return vec;
}

int vector_size(Vector vec){	
	return vec->size;
}

Pointer vector_get_at(Vector vec, int pos){
	assert(pos >= 0 && pos < vec->size);

	return vec->array[pos].value;
}

void vector_set_at(Vector vec, int pos, Pointer value){
	assert(pos >= 0 && pos < vec->size);

	// If there is a destroy function we are calling it for the old element
	if(value != vec->array[pos].value && vec->destroy_value != NULL){
		vec->destroy_value(vec->array[pos].value);
	}

	vec->array[pos].value = value;
}

void vector_insert_last(Vector vec, Pointer value){
	// Increase the vector if needed...every time *2
	if(vec->capacity == vec->size){
		vec->capacity *= 2;
		vec->array = realloc(vec->array, vec->capacity * sizeof(*vec->array));
	}

	vec->array[vec->size].value = value;
	vec->size++;
}

void vector_remove_last(Vector vec){
	assert(vec->size != 0);

	// If there is a destroy function we are calling it for the element that will be removed
	if(vec->destroy_value != NULL){
		vec->destroy_value(vec->array[vec->size - 1].value);
	}

	vec->size--;

	// Decrease the size of the array if needed for less space
	// Because of the complexity it is important to decrease the space in half and only 
	// if capacity is 4 times biger than size (75% of the array is empty)
	if(vec->capacity > vec->size * 4 && vec->capacity > 2*VECTOR_MIN_CAPACITY){
		vec->capacity /= 2;
		vec->array = realloc(vec->array, vec->capacity * sizeof(*vec->array));
	}
}

Pointer vector_find(Vector vec, Pointer value, CompareFunc compare){
	for(int i = 0; i < vec->size; i++){
		if(compare(vec->array[i].value, value) == 0){
			return vec->array[i].value;		// Has been found
		}
	}

	return NULL;				// There is not such an element
}


DestroyFunc vector_set_destroy_value(Vector vec, DestroyFunc destroy_value){
	DestroyFunc old = vec->destroy_value;
	vec->destroy_value = destroy_value;

	return old;
}

void vector_destroy(Vector vec){
	// If there is a destroy function we are calling it for all the elements
	if(vec->destroy_value != NULL){
		for (int i = 0; i < vec->size; i++){
			vec->destroy_value(vec->array[i].value);
		}
	}

	// Need to free the array and the struct
	free(vec->array);
	free(vec);
}

VectorNode vector_first(Vector vec){
	if(vec->size == 0){
		return VECTOR_BOF;
	}else{
		return &vec->array[0];
	}
}

VectorNode vector_last(Vector vec){
	if(vec->size == 0){
		return VECTOR_EOF;
	}else{
		return &vec->array[vec->size-1];
	}
}

VectorNode vector_next(Vector vec, VectorNode node){
	if(node == &vec->array[vec->size-1]){
		return VECTOR_EOF;
	}else{
		return node + 1;
	}
}

VectorNode vector_previous(Vector vec, VectorNode node){
	if(node == &vec->array[0]){
		return VECTOR_EOF;
	}else{
		return node - 1;
	}
}

Pointer vector_node_value(Vector vec, VectorNode node){
	return node->value;
}

VectorNode vector_find_node(Vector vec, Pointer value, CompareFunc compare){
	for(int i = 0; i < vec->size; i++){
		if(compare(vec->array[i].value, value) == 0){
			return &vec->array[i];		// Has been found
		}
	}

	return VECTOR_EOF;				// There is not such an element
}