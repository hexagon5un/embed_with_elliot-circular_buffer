#include "main.h" 

#define BUFFER_SIZE  16

enum BufferStatus {BUFFER_OK, BUFFER_EMPTY, BUFFER_FULL};

struct Buffer {
	uint8_t data[BUFFER_SIZE];
	uint8_t newest_index;
	uint8_t oldest_index;
};
struct Buffer buffer = {{}, 0, 0};

enum BufferStatus bufferWrite(uint8_t byte){
	uint8_t next_index = (buffer.newest_index+1) % BUFFER_SIZE;

	if (next_index == buffer.oldest_index){
		return BUFFER_FULL;
	}
	buffer.data[buffer.newest_index] = byte;
	buffer.newest_index = next_index;
	return BUFFER_OK;
}

enum BufferStatus bufferRead(uint8_t *byte){
	if (buffer.newest_index == buffer.oldest_index){
		return BUFFER_EMPTY;
	}
	*byte = buffer.data[buffer.oldest_index];
	buffer.oldest_index = (buffer.oldest_index+1) % BUFFER_SIZE;
	return BUFFER_OK;
}

int main(void) {

	initUSART();
	_delay_ms(200);
	printString("Buffer Tester!\n");

	// String is too long.  Watch how it deals with overflow.
	uint8_t localString[27] = "abcdefghijklmnopqrstuvwxyz";
	uint8_t i;
	uint8_t tempCharStorage;
	enum BufferStatus bufferStatus;

	while (1) {

		// Fill up (over-fill) buffer
		for (i=0; i<sizeof(localString); i++){
			bufferStatus = bufferWrite(localString[i]);
			// Watch how the status changes from 0 (OK) to 2 (FULL)
			printString("Byte number: ");
			printByte(i);
			printString(" ");
			printByte(bufferStatus);
			printString("\n");
		}
		// Here's a demo of testing when buffer is empty
		//  to print out the whole thing.
		// And notice that the buffer fills up with 15 characters 
		while (1) {
			bufferStatus = bufferRead(&tempCharStorage);
			if (bufferStatus == BUFFER_EMPTY){
				break;
			} else {
				transmitByte(tempCharStorage);	
			}
		}
		break;
	}                                                  /* End event loop */
	return 0;                              /* This line is never reached */
}
