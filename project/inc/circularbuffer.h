#ifndef _INC_CIRCULAR_BUFFER
#define _INC_CIRCULAR_BUFFER

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

// Function macro definitions
#define _CIRC_BUF_GET_CAPACITY(circular_buf)	( (circular_buf)->capacity )
#define _CIRC_BUF_FREE(circular_buf)					( free(circular_buf) )

typedef enum{

	CIRCULAR_BUF_EMPTY,
	CIRCULAR_BUF_FULL,
	CIRCULAR_BUF_NORMAL

}circular_buf_state;

struct circular_buf{

	void* buffer;
	int head;
	int tail;
	size_t capacity;
	circular_buf_state state;

};

typedef struct circular_buf cbuf_t;
typedef cbuf_t* cbuf_ptr;


/// Pass in a storage buffer and size
/// Returns a circular buffer handle
cbuf_ptr CircularBufferInit(void* buffer, size_t size);

/* Reset the circular buffer to empty */
void CircularBufferReset(cbuf_ptr circular_buf);


/// Free a circular buffer structure.
/// Does not free data buffer; owner is responsible for that
void CircularBufferFree(cbuf_ptr circular_buf);


/* Updates the current state of the circular_buf structure elements */
void CircularBufferSetStates(cbuf_ptr circular_buf);


/* Inserts the given data into the buffer and rejects new data if the buffer is full
   Returns 0 on success, 1 if buffer is full */
int CircularBufferInsertValue(cbuf_ptr circular_buf, void* data, size_t typesize);


/* Assigns the most recent data into the user data
   Returns 0 on success, 1 if buffer is empty */
int CircularBufferGetValue(cbuf_ptr circular_buf, void* data, size_t typesize);


/* Returns the maximum capacity of the buffer */
size_t CircularBufferCapacity(cbuf_ptr circular_buf);


/* Returns the current number of elements in the buffer */
size_t CircularBufferSize(cbuf_ptr circular_buf);


#endif
