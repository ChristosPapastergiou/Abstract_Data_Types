#include "acutest.h"
#include "ADTList.h"

void test_create(void){
	List list = list_create(NULL);
	list_set_destroy_value(list, NULL);

	TEST_CHECK(list != NULL);
	TEST_CHECK(list_size(list) == 0);

	list_destroy(list);
}

void test_insert(void){
	List list = list_create(NULL);

	int N = 1000;
	int array[N];					

	for(int i = 0; i < N; i++){
		list_insert_next(list, LIST_BOF, &array[i]);
		TEST_CHECK(list_size(list) == (i + 1));						
		TEST_CHECK(list_node_value(list, list_first(list)) == &array[i]);	
	}

	ListNode node = list_first(list);

	for(int i = N - 1; i >= 0; i--){
		TEST_CHECK(list_node_value(list, node) == &array[i]);
		node = list_next(list, node);
	}

	ListNode first_node = list_first(list);
	list_insert_next(list, first_node, NULL);
	TEST_CHECK(list_node_value(list, list_next(list, first_node)) == NULL);

	list_destroy(list);
}

void test_remove_next(void){
	List list = list_create(free);

	int N = 1000;
	int* array[N];

	for(int i = 0; i < N; i++){
		array[i]  = malloc(sizeof(int));
		*array[i] = i;
		list_insert_next(list, LIST_BOF, array[i]);
	}

	for(int i = N - 1; i >= 0; i--){
		TEST_CHECK(list_node_value(list, list_first(list)) == array[i]);
		list_remove_next(list, LIST_BOF);
		TEST_CHECK(list_size(list) == i);
	}

	for(int i = 0; i < N; i++){
		array[i]  = malloc(sizeof(int));
		*array[i] = i;
		list_insert_next(list, LIST_BOF, array[i]);
	}	

	list_remove_next(list, list_first(list));
	TEST_CHECK(list_size(list) == N - 1);

	list_destroy(list);
}

int compare_ints(Pointer a, Pointer b){
	return *(int*)a - *(int*)b;
}

void test_find(){
	List list = list_create(NULL);
	int N = 1000;
	int array[N];

	for(int i = 0; i < N; i++){
		array[i] = i;
		list_insert_next(list, LIST_BOF, &array[i]);
	}

	for(int i = 0; i < N; i++){
		int* value = list_find(list, &i, compare_ints); 
		TEST_CHECK(value == &array[i]);
	}

	int not_exists = -1;
	TEST_CHECK(list_find(list, &not_exists, compare_ints) == NULL);

	list_destroy(list);
}


void test_find_node(){
	List list = list_create(NULL);

	int N = 1000;
	int array[N];

	for(int i = 0; i < N; i++){
		array[i] = i;
		list_insert_next(list, LIST_BOF, &array[i]);
	}

	ListNode node = list_first(list);

	for(int i = N - 1; i >= 0; i--){
		ListNode found_node = list_find_node(list, &i, compare_ints); 
		TEST_CHECK(found_node == node);
		TEST_CHECK(list_node_value(list, found_node) == &array[i]);

		node = list_next(list, node);
	}

	list_destroy(list);
}

void test_get_at(){
	List list = list_create(NULL);
	int N = 1000;
	int array[N];

	for(int i = 0; i < N; i++){
		array[i] = i;
		list_insert_next(list, LIST_BOF, &array[i]);
	}

	for(int i = 0; i < N; i++){
		int* value = list_get_at(list, i);
		TEST_ASSERT(value == &array[N-1 - i]);
	}

	list_destroy(list);
}

int* create_int(int value){
	int* pointer = malloc(sizeof(int));
	*pointer = value;
	return pointer;
}

List create_test_list(int N, int array[]){
	List list = list_create(array == NULL ? free : NULL);
	ListNode node = LIST_BOF;

	for(int i = 0; i < N; i++){
		int* value = array == NULL ? create_int(i) : &array[i];
		list_insert_next(list, node, value);
		node = node == LIST_BOF ? list_first(list) : list_next(list, node);
	}

	return list;
}

void test_remove(){
	int N = 1000;
	List list = create_test_list(N, NULL);

	ListNode first = list_first(list);
	list_remove(list, list_next(list, first));	
	TEST_ASSERT(list_size(list) == N - 1);
	TEST_ASSERT(*(int*)list_node_value(list, list_next(list, first)) == 2);

	list_remove(list, list_first(list));	
	TEST_ASSERT(list_size(list) == N - 2);
	TEST_ASSERT(*(int*)list_node_value(list, list_first(list)) == 2);

	for(int i = 0; i <= N - 3; i++){
		TEST_ASSERT(*(int*)list_node_value(list, list_last(list)) == N-1 - i);
		list_remove(list, list_last(list));	
		TEST_ASSERT(list_size(list) == N - 3 - i);
		break;
	}

	list_destroy(list);
}

void test_append(){
	int N = 10;
	int array[2*N];

	List list = create_test_list(0, array);
	List to_append = create_test_list(N, array);

	list_append(list, to_append);
	TEST_ASSERT(list_size(list) == N);
	for(int i = 0; i < N; i++){
		TEST_ASSERT(list_get_at(list, i) == &array[i]);
	}

	to_append = create_test_list(0, array);

	list_append(list, to_append);
	TEST_ASSERT(list_size(list) == N);
	for(int i = 0; i < N; i++){
		TEST_ASSERT(list_get_at(list, i) == &array[i]);
	}

	to_append = create_test_list(N, &array[N]);

	list_append(list, to_append);
	TEST_ASSERT(list_size(list) == 2*N);

	for(int i = 0; i < 2*N; i++){
		TEST_ASSERT(list_get_at(list, i) == &array[i]);
	}

	list_destroy(list);
}

TEST_LIST = {
	{ "list_create", test_create },
	{ "list_insert_next", test_insert },
	{ "list_remove_next", test_remove_next },
	{ "list_find", test_find },
	{ "list_find_node", test_find_node },
	{ "list_get_at", test_get_at },
	{ "list_remove", test_remove },
	{ "list_append", test_append },
	{ NULL, NULL }
};