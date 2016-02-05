#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

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

void dumpBuffer(void){

	for (uint8_t i=0; i<BUFFER_SIZE; i++){
		if (buffer.oldest_index == buffer.newest_index && buffer.newest_index == i){
			transmitByte('=');
		} else  if (buffer.oldest_index == i){
			transmitByte('[');
		} else if (buffer.newest_index == i){
			transmitByte(']');
		} else {
			transmitByte('.');
		}
	}
	printString("\n");

	for (uint8_t i=0; i<BUFFER_SIZE; i++){
			transmitByte(buffer.data[i]);
	}
	printString("\n");
}


int main(void) {

	initUSART();
	_delay_ms(200);

	uint8_t i;
	uint8_t tempCharStorage;

	while (1) {

		dumpBuffer();
		printString("  Demo: adding characters to buffer\n");
		uint8_t coolString[] = "Howdy";
		i = 0;
		while(i < sizeof(coolString) - 1){
			bufferWrite(coolString[i]);
			++i;
			dumpBuffer();
		}

		printString("  Demo: reading out the first three characters\n");
		for (i = 0; i<3 ; i++){	
			bufferRead(&tempCharStorage);
			transmitByte(tempCharStorage);	
			printString("\n");
			dumpBuffer();
		}

		printString("  Demo: adding more characters to buffer\n");
		uint8_t anotherString[] = "Hello";	
		i = 0;
		while(i < sizeof(anotherString) - 1){
			bufferWrite(anotherString[i]);
			++i;
			dumpBuffer();
		}

		// And read it back out using return code
		printString("  Demo: reading everything back out\n");
		while (bufferRead(&tempCharStorage) == BUFFER_OK){
			transmitByte(tempCharStorage);	
		}
		printString("\n");
		
		dumpBuffer();
		printString("  Demo: empty! (newest = oldest)\n");

		// Fill up buffer, using return code
		i = 0;
		while(bufferWrite('A'+i) == BUFFER_OK){
			++i;
			dumpBuffer();
		}

		printString("  Note: never fills up whole buffer\n");
		printString("  it's full when first index equals last\n");

		return 0;

	}                                                  /* End event loop */
	return 0;                              /* This line is never reached */
}
