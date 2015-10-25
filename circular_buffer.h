#include <util/atomic.h>
#include <avr/io.h>
#define BUFFER_SIZE  16

  /* Use: 
   *
   * enum BufferStatus status;
   * struct Buffer buffer {{},0,0};
   * status = bufferWrite(&buffer, 'A');
   * if (status == BUFFER_FULL){
   *     handle_it();
   * }
   *
   * uint8_t buffer_byte;
   * status = bufferRead(&buffer, &buffer_byte); 
   * if (status == BUFFER_OK){
   * 	do_something(buffer_byte);
   * }
   *
   * */

enum BufferStatus {BUFFER_OK, BUFFER_EMPTY, BUFFER_FULL};

struct Buffer {
	uint8_t data[BUFFER_SIZE];
	uint8_t newest_index;
	uint8_t oldest_index;
};
// A weakness of this implementation is that all buffers are the same length, 
// being defined by BUFFER_SIZE above.  Meh.

// Read and write to circular buffer
// Takes Buffer struct as first argument,
//  and either data or pointer to some memory as second.
// Returns the result codes enumerated in BufferStatus

enum BufferStatus bufferWrite(volatile struct Buffer *buffer, uint8_t byte);
enum BufferStatus bufferRead(volatile struct Buffer *buffer, uint8_t *byte);
enum BufferStatus bufferPeek(volatile struct Buffer *buffer, uint8_t *byte);


