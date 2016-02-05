#include "cbuffer.h"

#if (BUFFER_ELEMENT_WIDTH == 32)
/* 32-bit wide elements */

#elif (BUFFER_ELEMENT_WIDTH == 16)
/* 16 bit wide elements */

#else
/* 8 bit wide elements */


BufferStatus BUF_init(Buffer* b){
    BufferStatus status = BUFFER_EMPTY;
    
    /* erase the buffer */
    uint16_t i;
    for(i = 0; i < BUFFER_LENGTH; i++){
        b->data[i] = 0;
    }
    
    b->newest_index = 0;
    b->oldest_index = 0;
    
    return status;
}

BufferStatus BUF_status(Buffer* b){
    BufferStatus status;
    
    if(b->newest_index == b->oldest_index){
        status = BUFFER_EMPTY;
    }else if(((b->newest_index + 1) & ~BUFFER_LENGTH) == b->oldest_index){
        status = BUFFER_FULL;
    }else{
        status = BUFFER_OK;
    }
    
    return status;
}

BufferStatus BUF_write(Buffer* b, uint8_t writeValue){
    BufferStatus status;
    
    uint16_t new_index = (b->newest_index + 1) & ~BUFFER_LENGTH;
    if(new_index == b->oldest_index){
        status = BUFFER_FULL;
    }else{
        b->data[new_index] = writeValue;
        b->newest_index = new_index;
        status = BUFFER_OK;
    }
    
    return status;
}

BufferStatus BUF_read(Buffer* b, uint8_t* readValue){
    BufferStatus status;
    
    if(b->newest_index == b->oldest_index){
        status = BUFFER_EMPTY;
        *readValue = 0;
    }else{
        *readValue = b->data[b->oldest_index];
        b->oldest_index++;
        b->oldest_index &= ~BUFFER_LENGTH;
    }
    
    return status;
}

#endif

/* check to ensure that the buffer length is of an appropriate length */
#if (   (BUFFER_LENGTH != 1)        \
         && (BUFFER_LENGTH != 2)  \
         && (BUFFER_LENGTH != 4)   \
         && (BUFFER_LENGTH != 8)   \
         && (BUFFER_LENGTH != 16)  \
         && (BUFFER_LENGTH != 32)  \
         && (BUFFER_LENGTH != 64)  \
         && (BUFFER_LENGTH != 128) \
         && (BUFFER_LENGTH != 256) \
         && (BUFFER_LENGTH != 512) \
         && (BUFFER_LENGTH != 1024))
#error "BUFFER_LENGTH is not a power of 2"
#endif

