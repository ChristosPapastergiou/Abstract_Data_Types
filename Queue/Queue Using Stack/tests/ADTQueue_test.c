#include "acutest.h"

#include "ADTQueue.h"

void test_create(void){
	Queue queue = queue_create(NULL);
	queue_set_destroy_value(queue, NULL);

	TEST_ASSERT(queue != NULL);
	TEST_ASSERT(queue_size(queue) == 0);

	queue_destroy(queue);
}

void test_insert(void){
	Queue queue = queue_create(NULL);
	int N = 1000;
	int* array = malloc(N * sizeof(*array));
	
	for(int i = 0; i < 1000; i++){
		queue_insert_back(queue, &array[i]);
		TEST_ASSERT(queue_size(queue) == i+1);
		TEST_ASSERT(queue_front(queue) == &array[0]);
		TEST_ASSERT(queue_back(queue) == &array[i]);
	}

	queue_destroy(queue);
	free(array);
}

void test_remove(void){
	Queue queue = queue_create(NULL);
	int N = 1000;
	int* array = malloc(N * sizeof(*array));

	for(int i = 0; i < 1000; i++){
		queue_insert_back(queue, &array[i]);
	}

	for(int i = 0; i < 1000; i++){
		TEST_ASSERT(queue_front(queue) == &array[i]);
		queue_remove_front(queue);
		TEST_ASSERT(queue_size(queue) == 999-i);
	}

	queue_destroy(queue);
	free(array);
}

TEST_LIST = {
	{ "queue_create", test_create },
	{ "queue_insert_back", test_insert },
	{ "queue_remove_front", test_remove },
	{ NULL, NULL }
};