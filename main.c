#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "USART.h"
#include "circular_buffer.h"

volatile struct Buffer rx_buffer = {{}, 0, 0};
volatile struct Buffer tx_buffer = {{}, 0, 0};

static inline void initUSART_interrupts(void){
	UCSR0B |= (1<<RXCIE0);
	sei();
}
static inline void enable_transmission(void){
	UCSR0B |= (1<<UDRIE0);
}
static inline void disable_transmission(void){
	UCSR0B &= ~(1<<UDRIE0);
}

ISR(USART_RX_vect){
	bufferWrite(&rx_buffer, UDR0);
}

ISR(USART_UDRE_vect){
	uint8_t tempy;
	enum BufferStatus status_tx = bufferRead(&tx_buffer, &tempy);
	if (status_tx == BUFFER_EMPTY){
		disable_transmission();
	} else {
		UDR0 = tempy;  /* write it out to the hardware serial */
	}
}

/* If something in RX buffer, copy it into TX */
static inline void echoReceived(volatile struct Buffer *rx_buffer_p, 
								volatile struct Buffer *tx_buffer_p);


int main(void) {

	initUSART();
	initUSART_interrupts();
	_delay_ms(200);

	// Fill hello string into tx buffer
	uint8_t helloString[] = "Hello World! This is too long!";
	for(uint8_t i=0; i < sizeof(helloString); i++){
		bufferWrite(&tx_buffer, helloString[i]);
	}
	// And then transmit it
	enable_transmission();

	while (1) {

		echoReceived(&rx_buffer, &tx_buffer);
		/*  The delay simulates doing something more important.
		 *  Try typing as fast as you can here.  
		 *  You'll see it being returned every 1/2 second 
		 *   as the buffer gets processed. 
		 *  If you type fast enough, you can overflow the rx_buffer. */
		_delay_ms(500);

	}                                                  /* End event loop */
	return 0;                              /* This line is never reached */
}


/* If something in RX buffer, copy it into TX */
static inline void echoReceived(volatile struct Buffer *rx_buffer_p, 
		volatile struct Buffer *tx_buffer_p){
	uint8_t one_character;
	while(1) {
		/*  read in the received data, if any */
		enum BufferStatus status_rx = bufferRead(rx_buffer_p, &one_character);
		/* jump out when the buffer is empty */
		if (status_rx == BUFFER_EMPTY){  
			break;
		}
		/*  otherwise write received byte to the tx buffer
		 *  and re-enable the transmission interrupt routine */
		bufferWrite(tx_buffer_p, one_character);
		enable_transmission();
	} 
}

