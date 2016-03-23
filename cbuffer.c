#include "cbuffer.h"

BufferStatus BUF_status(Buffer* b){
    BufferStatus status;
    
    if(b->newest_index == b->oldest_index){
        status = BUFFER_EMPTY;
    }else if(((b->newest_index + 1) & ~b->length) == b->oldest_index){
        status = BUFFER_FULL;
    }else{
        status = BUFFER_OK;
    }
    
    return status;
}

int32_t BUF_emptySlots(Buffer* b){
    int16_t emptySlots = 0;
    
    if(b->status == BUFFER_EMPTY){
        emptySlots = b->length;
    }else if(b->status == BUFFER_FULL){
        emptySlots = 0;
    }else{
        /* count the empty slots */
        int16_t index = b->newest_index;
        
        while(index != b->oldest_index){
            /* index = (index + 1) % b->length */
            index++;
            index &= ~b->length;
            emptySlots++;
        }
    }
    
    return(uint32_t)emptySlots;
}

int32_t BUF_fullSlots(Buffer* b){
    int16_t fullSlots = 0;
    
    if(b->status == BUFFER_EMPTY){
        fullSlots = 0;
    }else if(b->status == BUFFER_FULL){
        fullSlots = b->length;
    }else{
        /* count the empty slots */
        int16_t index = b->oldest_index;
        
        while(index != b->newest_index){
            /* index = (index + 1) % b->length */
            index++;
            index &= ~b->length;
            fullSlots++;
        }
        
        
    }
    
    return(uint32_t)fullSlots;
}

#if (BUFFER_ELEMENT_WIDTH == 32)
/* 32-bit wide elements */

BufferStatus BUF_write(Buffer* b, uint32_t writeValue){
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

uint32_t BUF_read(Buffer* b){
    uint32_t readValue = 0;
    
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

#elif (BUFFER_ELEMENT_WIDTH == 16)
/* 16 bit wide elements */

BufferStatus BUF_write(Buffer* b, uint16_t writeValue){
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

uint16_t BUF_read(Buffer* b){
    uint16_t readValue = 0;
    
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

#else
/* 8 bit wide elements */

BufferStatus BUF_init8(Buffer* b, uint8_t* arr, uint16_t length){
    b->dataPtr = arr;
    b->length = length;
    
    /* erase the buffer */
    uint16_t i;
    for(i = 0; i < length; i++){
        b->dataPtr[i] = 0;
    }
    
    b->newest_index = 0;
    b->oldest_index = 0;
    b->status = BUFFER_EMPTY;
    
    /* ensure that the buffer length is a power of 2
     * so that it conforms to this library */
    uint16_t possibleLength = 1;
    uint8_t valueOk = 0;
    while(possibleLength <= 16384){
        if(possibleLength == b->length){
            valueOk = 1;
            break;
        }
        possibleLength = possibleLength << 1;
    }
    
    if(valueOk == 0)
        while(1);       // programmer's trap to catch errant length values
    
    return b->status;
}


BufferStatus BUF_write(Buffer* b, uint8_t writeValue){
    if(b->status != BUFFER_FULL){
        b->dataPtr[b->newest_index] = writeValue;
        b->newest_index += 1;
        b->newest_index &= ~b->length;
        
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
        readValue = b->dataPtr[b->oldest_index];
        b->oldest_index++;
        b->oldest_index &= ~b->length;
        
        if(b->newest_index == b->oldest_index)
            b->status = BUFFER_EMPTY;
        else
            b->status = BUFFER_OK;
    }
        
    return readValue;
}

#endif



