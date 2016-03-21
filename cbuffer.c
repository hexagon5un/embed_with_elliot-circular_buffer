#include "cbuffer.h"

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

int32_t BUF_emptySlots(Buffer* b){
    int16_t fullSlots = b->newest_index - b->oldest_index;
    
    if(fullSlots < 0){
        fullSlots = BUFFER_LENGTH + 1 - fullSlots;
    }
    
    return(uint32_t)fullSlots;
}

int32_t BUF_fullSlots(Buffer* b){
    int16_t fullSlots = (int16_t)b->oldest_index - (int16_t)b->newest_index;
    
    if(fullSlots < 0){
        fullSlots = BUFFER_LENGTH + 1 - fullSlots;
    }
    
    return(uint32_t)fullSlots;
}

#if (BUFFER_ELEMENT_WIDTH == 32)
/* 32-bit wide elements */

BufferStatus BUF_write(Buffer* b, uint32_t writeValue){
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

uint32_t BUF_read(Buffer* b){
    uint32_t readValue = 0;
    
    if(b->newest_index != b->oldest_index){
        readValue = b->data[b->oldest_index];
        b->oldest_index++;
        b->oldest_index &= ~BUFFER_LENGTH;
    }
    
    return readValue;
}

#elif (BUFFER_ELEMENT_WIDTH == 16)
/* 16 bit wide elements */

BufferStatus BUF_write(Buffer* b, uint16_t writeValue){
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

uint16_t BUF_read(Buffer* b){
    uint16_t readValue = 0;
    
    if(b->newest_index != b->oldest_index){
        readValue = b->data[b->oldest_index];
        b->oldest_index++;
        b->oldest_index &= ~BUFFER_LENGTH;
    }
    
    return readValue;
}

#else
/* 8 bit wide elements */


BufferStatus BUF_write(Buffer* b, uint8_t writeValue){
    if(b->status != BUFFER_FULL){
        b->data[b->newest_index] = writeValue;
        b->newest_index += 1;
        b->newest_index &= ~BUFFER_LENGTH;
        
        if(b->newest_index == b->oldest_index)
            b->status = BUFFER_FULL;
        else
            b->status = BUFFER_OK;
    }
    
    return b->status;
}

uint8_t BUF_read(Buffer* b){
    uint8_t readValue = 0;
    
    if(b->status != BUFFER_EMPTY){
        readValue = b->data[b->oldest_index];
        b->oldest_index++;
        b->oldest_index &= ~BUFFER_LENGTH;
        
        if(b->newest_index == b->oldest_index)
            b->status = BUFFER_EMPTY;
        else
            b->status = BUFFER_OK;
    }
        
    return readValue;
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

