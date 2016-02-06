#ifndef _CIRCULAR_BUFFER_H
#define _CIRCULAR_BUFFER_H

#include <stdint.h>

/* The buffer length sets the number of elements
 * in the buffers.  This should always be a power
 * of 2 for this library */
#define BUFFER_LENGTH           8

/* valid values for BUFFER_ELEMENT_WIDTH are
 * 8, 16, and 32.  If you place another value
 * here, you will get a default of '8' */
#define BUFFER_ELEMENT_WIDTH    8

typedef enum bufferstatus {
    BUFFER_OK, 
    BUFFER_EMPTY, 
    BUFFER_FULL
} BufferStatus;

#if (BUFFER_ELEMENT_WIDTH == 32)
typedef struct buffer {
	uint32_t data[BUFFER_LENGTH];
	uint16_t newest_index;      // buffer could be long, use a 16-bit var here
	uint16_t oldest_index;
} Buffer;
#elif (BUFFER_ELEMENT_WIDTH == 16)
typedef struct buffer {
	uint16_t data[BUFFER_LENGTH];
	uint16_t newest_index;      // buffer could be long, use a 16-bit var here
	uint16_t oldest_index;
} Buffer;

#else
typedef struct buffer {
	uint8_t data[BUFFER_LENGTH];
	uint16_t newest_index;      // buffer could be long, use a 16-bit var here
	uint16_t oldest_index;
} Buffer;
#endif

BufferStatus BUF_init(Buffer* b);
BufferStatus BUF_status(Buffer* b);

#if (BUFFER_ELEMENT_WIDTH == 32)
BufferStatus BUF_write(Buffer* b, uint32_t writeValue);
BufferStatus BUF_read(Buffer* b, uint32_t* readValue);

#elif (BUFFER_ELEMENT_WIDTH == 16)
BufferStatus BUF_write(Buffer* b, uint16_t writeValue);
BufferStatus BUF_read(Buffer* b, uint16_t* readValue);

#else
BufferStatus BUF_write(Buffer* b, uint8_t writeValue);
BufferStatus BUF_read(Buffer* b, uint8_t* readValue);

#endif

#endif
