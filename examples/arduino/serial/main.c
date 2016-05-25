#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "cbuffer.h"

Buffer buffer;

void dumpBuffer(void){
        uint8_t i;
	for (i=0; i<BUFFER_LENGTH; i++){
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

	for (i=0; i<BUFFER_LENGTH; i++){
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
			BUF_write(&buffer, coolString[i]);
			++i;
			dumpBuffer();
		}

		printString("  Demo: reading out the first three characters\n");
		for (i = 0; i<3 ; i++){	
			BUF_read(&buffer, &tempCharStorage);
			transmitByte(tempCharStorage);	
			printString("\n");
			dumpBuffer();
		}

		printString("  Demo: adding more characters to buffer\n");
		uint8_t anotherString[] = "Hello";	
		i = 0;
		while(i < sizeof(anotherString) - 1){
			BUF_write(&buffer, anotherString[i]);
			++i;
			dumpBuffer();
		}

		// And read it back out using return code
		printString("  Demo: reading everything back out\n");
		while (BUF_read(&buffer, &tempCharStorage) == BUFFER_OK){
			transmitByte(tempCharStorage);	
		}
		printString("\n");
		
		dumpBuffer();
		printString("  Demo: empty! (newest = oldest)\n");

		// Fill up buffer, using return code
		i = 0;
		while(BUF_write(&buffer, 'A'+i) == BUFFER_OK){
			++i;
			dumpBuffer();
		}

		printString("  Note: never fills up whole buffer\n");
		printString("  it's full when first index equals last\n");

		return 0;

	}                                                  /* End event loop */
	return 0;                              /* This line is never reached */
}
