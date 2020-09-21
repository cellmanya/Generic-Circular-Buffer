#include "circularbuffer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

_Bool HeadChangedEvent = false;

void CircularBufferReset(cbuf_ptr circular_buf){

	circular_buf->head = 0;
	circular_buf->tail = 0;
	circular_buf->state = CIRCULAR_BUF_EMPTY;

}

cbuf_ptr CircularBufferInit(void* buffer, size_t capacity){

	cbuf_ptr cbuf = (cbuf_ptr)malloc(sizeof(cbuf_t));
	if( cbuf == NULL ){ printf("NULL was assigned to cbuf!"); exit(EXIT_FAILURE); }

	cbuf->buffer = buffer;
	cbuf->capacity = capacity;
	CircularBufferReset(cbuf);

	return cbuf;
}



void CircularBufferFree(cbuf_ptr circular_buf){

	free(circular_buf);

}

void CircularBufferSetStates(cbuf_ptr circular_buf){

	if( (circular_buf->head == circular_buf->tail) && !(HeadChangedEvent) ){

		circular_buf->state = CIRCULAR_BUF_FULL; // buffer is full
	}
	else if( (circular_buf->head == circular_buf->capacity) && (0 == circular_buf->tail) ){

		circular_buf->state = CIRCULAR_BUF_FULL; // again buffer is full
	}
	else if( (circular_buf->head == circular_buf->tail) && !(HeadChangedEvent) ){

		circular_buf->state = CIRCULAR_BUF_EMPTY;
	}
	else{

		circular_buf->state = CIRCULAR_BUF_NORMAL;
	}

}


int CircularBufferInsertValue(cbuf_ptr circular_buf, void* data, size_t typesize){

	void* dest;
	HeadChangedEvent = true;

	CircularBufferSetStates(circular_buf); // updating the state

	if( circular_buf->state == CIRCULAR_BUF_FULL ){

		return EXIT_FAILURE;
	}

	else{

		dest = (circular_buf->buffer + circular_buf->head * typesize);

		memcpy(dest, data, typesize);

		circular_buf->head++;

		CircularBufferSetStates(circular_buf);

		if( circular_buf->head == circular_buf->capacity ){ circular_buf->head = 0; }

		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE; // Exception Occurred!
}


int CircularBufferGetValue(cbuf_ptr circular_buf, void* data, size_t typesize){


	void* source;

	if( circular_buf->state == CIRCULAR_BUF_EMPTY ){

		return EXIT_FAILURE;
	}

	else{

		source = (circular_buf->buffer + circular_buf->tail * typesize);

		memcpy(data, source, typesize);

		circular_buf->tail = (circular_buf->tail + 1) % (circular_buf->capacity);

		CircularBufferSetStates(circular_buf);

		return EXIT_SUCCESS;
	}

}

size_t CircularBufferCapacity(cbuf_ptr circular_buf){

	return circular_buf->capacity;
}

size_t CircularBufferSize(cbuf_ptr circular_buf){

	size_t size = circular_buf->capacity;


	if( circular_buf->state == CIRCULAR_BUF_EMPTY){

		size = 0;
	}

	else if( circular_buf->state == CIRCULAR_BUF_NORMAL ){

		if( circular_buf->head >= circular_buf->tail )
		{

			size = circular_buf->head - circular_buf->tail;
		}

		else
		{
			size = (circular_buf->capacity + circular_buf->head) - (circular_buf->tail);

		}

	}

	return size;
}
