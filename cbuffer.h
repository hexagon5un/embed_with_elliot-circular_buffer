#ifndef _CIRCULAR_BUFFER_H
#define _CIRCULAR_BUFFER_H

#include <stdint.h>

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
	uint16_t length;
	uint16_t newest_index;
	uint16_t oldest_index;
    BufferStatus status;
    uint32_t dataPtr*;
} Buffer;
#elif (BUFFER_ELEMENT_WIDTH == 16)
typedef struct buffer {
	uint16_t length;
	uint16_t newest_index;
	uint16_t oldest_index;
    BufferStatus status;
    uint16_t dataPtr*;
} Buffer;

#else
typedef struct buffer {
	uint16_t length;
	uint16_t newest_index;
	uint16_t oldest_index;
    BufferStatus status;
    uint8_t* dataPtr;
} Buffer;
#endif

BufferStatus BUF_status(Buffer* b);
int32_t BUF_emptySlots(Buffer* b);
int32_t BUF_fullSlots(Buffer* b);

#if (BUFFER_ELEMENT_WIDTH == 32)
BufferStatus BUF_init32(Buffer* b, uint8_t* arr, uint16_t length);
BufferStatus BUF_write(Buffer* b, uint32_t writeValue);
uint32_t BUF_read(Buffer* b);

#elif (BUFFER_ELEMENT_WIDTH == 16)
BufferStatus BUF_init16(Buffer* b, uint8_t* arr, uint16_t length);
BufferStatus BUF_write(Buffer* b, uint16_t writeValue);
uint16_t BUF_read(Buffer* b);

#else
BufferStatus BUF_init8(Buffer* b, uint8_t* arr, uint16_t length);
BufferStatus BUF_write(Buffer* b, uint8_t writeValue);
uint8_t BUF_read(Buffer* b);

#endif

#endif
