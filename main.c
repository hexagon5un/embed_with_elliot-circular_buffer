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



int main(void) {
	enum BufferStatus status;
	uint8_t input_byte;

	initUSART();
	initUSART_interrupts();
	_delay_ms(200);

	while (1) {

		status = bufferRead(&rx_buffer, &input_byte);
		if (status == BUFFER_OK){
			bufferWrite(&tx_buffer, input_byte);
			enable_transmission();
		}

	}                                                  /* End event loop */
	return 0;                              /* This line is never reached */
}

