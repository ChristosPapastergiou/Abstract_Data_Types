#include "acutest.h"
#include "ADTPriorityQueue.h"

void shuffle(int* array[], int size){
	for(int i = 0; i < size; i++){
		int new_pos = i + rand() / (RAND_MAX / (size - i) + 1);
		int* temp = array[new_pos];
		array[new_pos] = array[i];
		array[i] = temp;
	}
}

int* create_int(int value){
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

int compare_ints(Pointer a, Pointer b){
	return *(int*)a - *(int*)b;
}

void test_create(void){
	PriorityQueue pqueue = pqueue_create(compare_ints, NULL);
	pqueue_set_destroy_value(pqueue, NULL);

	TEST_ASSERT(pqueue != NULL);
	TEST_ASSERT(pqueue_size(pqueue) == 0);

	pqueue_destroy(pqueue);
}	

void test_insert(void){
	PriorityQueue pqueue = pqueue_create(compare_ints, NULL);
	int N = 1000;
	int* array = malloc(N * sizeof(*array));

	for(int i = 0; i < N; i++){
		array[i] = i;
		pqueue_insert(pqueue, &array[i]);
		TEST_ASSERT(pqueue_size(pqueue) == i+1);
		TEST_ASSERT(pqueue_max(pqueue) == &array[i]);
	}

	pqueue_destroy(pqueue);
	free(array);
}

void test_remove(void){
	PriorityQueue pqueue = pqueue_create(compare_ints, free);

	int N = 10;
	int** array = malloc(N * sizeof(*array));
	for(int i = 0; i < N; i++){
		array[i] = create_int(i);
	}
	shuffle(array, N);

	for(int i = 0; i < N; i++){
		pqueue_insert(pqueue, array[i]);
	}
	
	for(int i = N-1; i >= 0; i--){
		int* value = pqueue_max(pqueue);
		TEST_ASSERT(*value == i);
		TEST_ASSERT(pqueue_max(pqueue) == value);
		pqueue_remove_max(pqueue);
		TEST_ASSERT(pqueue_size(pqueue) == i);
	}

	pqueue_destroy(pqueue);

	pqueue = pqueue_create(compare_ints, NULL);
	pqueue_insert(pqueue, &N);
	TEST_ASSERT(pqueue_max(pqueue) == &N);
	pqueue_remove_max(pqueue);
	pqueue_destroy(pqueue);
	free(array);
}

TEST_LIST = {
	{ "pqueue_create", test_create },
	{ "pqueue_insert", test_insert },
	{ "pqueue_remove_max", test_remove },
	{ NULL, NULL }
};
