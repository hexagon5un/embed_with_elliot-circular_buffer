#include "circular_buffer.h"

enum BufferStatus bufferWrite(volatile struct Buffer *buffer, uint8_t byte){
	/* Modulo arithmetic should work in any case, 
	 * but if your compiler doesn't optimize for powers of two, you might want to */
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		uint8_t next_index = (((buffer->newest_index)+1) % BUFFER_SIZE);

		if (next_index == buffer->oldest_index){
			return BUFFER_FULL;
		}

		buffer->data[buffer->newest_index] = byte;
		buffer->newest_index = next_index;
	}
	return BUFFER_OK;
}

enum BufferStatus bufferRead(volatile struct Buffer *buffer, uint8_t *byte){

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if (buffer->newest_index == buffer->oldest_index){
			return BUFFER_EMPTY;
		}

		*byte = buffer->data[buffer->oldest_index];
		buffer->oldest_index = ((buffer->oldest_index+1) % BUFFER_SIZE);
	}
	return BUFFER_OK;
}

