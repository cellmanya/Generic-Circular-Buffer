#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "circularbuffer.h"

#define DEFAULT_CAPACITY	6


int main(){

	//Test1 Int Array
	int * buffer_d = (int*)malloc(DEFAULT_CAPACITY * sizeof(int));
	if( buffer_d == NULL ) { printf("NULL is assigned to buffer_d!");	return EXIT_FAILURE; }
	int data_d = 5;
	cbuf_ptr handle_container_d = CircularBufferInit(buffer_d, DEFAULT_CAPACITY, sizeof(int));


	//Test2 Float Array
	float * buffer_f = (float*)malloc(DEFAULT_CAPACITY * sizeof(float));
	if( buffer_f == NULL ) { printf("NULL is assigned to buffer_f!");	return EXIT_FAILURE; }
	float data_f = 34.456f;
	cbuf_ptr handle_container_f = CircularBufferInit(buffer_f, DEFAULT_CAPACITY, sizeof(float));


	for(int i = 0; i < 5; i++){

		if( CircularBufferInsertValue(handle_container_d, &data_d) == EXIT_FAILURE ) puts("The buffer_d is full!");
		if( CircularBufferInsertValue(handle_container_f, &data_f) == EXIT_FAILURE ) puts("The buffer_f is full!");

	}

	for(int i = 0; i < 5; i++){

		if( CircularBufferGetValue(handle_container_d, &data_d) == EXIT_FAILURE ) puts("The buffer_d is empty!");
		if( CircularBufferGetValue(handle_container_f, &data_f) == EXIT_FAILURE ) puts("The buffer_f is empty!");


	}

	for(int i = 0; i < 4; i++){

		if( CircularBufferInsertValue(handle_container_d, &data_d) == EXIT_FAILURE ) puts("The buffer_d is full!");
		if( CircularBufferInsertValue(handle_container_f, &data_f) == EXIT_FAILURE ) puts("The buffer_f is full!");

	}


	printf("The size of the buffer_d : %zu\n", CircularBufferSize(handle_container_d));
	printf("The capacity of the buffer_d : %zu\n", CircularBufferCapacity(handle_container_d));
	printf("The value is gotten from the buffer_d : %d\n\n", data_d);

	printf("The size of the buffer_f : %zu\n", CircularBufferSize(handle_container_f));
	printf("The capacity of the buffer_f : %zu\n", CircularBufferCapacity(handle_container_f));
	printf("The value is gotten from the buffer_f : %f\n\n", data_f);


	CircularBufferFree(handle_container_d);
	CircularBufferFree(handle_container_f);


	return 0;
}
