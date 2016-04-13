#include "cbuffer.h"

#define CIRCULAR_BUFFER_LENGTH          8
#define CIRCULAR_BUFFER_ELEMENT_WIDTH   8

int main(void){
    /* Create an array for the circular buffer to utilize, then
        create the structure for the cbuffer.  Be sure that the
        array width matched your data type! */
    uint8_t cBufferArray[CIRCULAR_BUFFER_LENGTH];
    Buffer b;
    
    /* Initialize the buffer */
    BUF_init(&b, cBufferArray, CIRCULAR_BUFFER_LENGTH, CIRCULAR_BUFFER_ELEMENT_WIDTH);
    
    /* Read the buffer status whenever desired (BUFFER_EMPTY, BUFFER_OK, BUFFER_FULL) */
    BufferStatus status = BUF_status(&b);
    
    /* Write to the buffer. Remember not to overflow or new values will not be written!
        If your element width is 16, use BUF_write16, etc. */
    BUF_write8(1);
    BUF_write8(2);
    BUF_write8(3);
    
    /* Read all data from the buffer into a local array */
    uint8_t dataOut[CIRCULAR_BUFFER_LENGTH];
    uint8_t i = 0;
    while(BUF_status(&b) != BUFFER_EMPTY){
        /* again, remember to use the proper width! */
        dataOut[i] = BUF_read8(&b);
        i++;
    }
    
    /* now the length of the data that was read is stored in i */
    dataOutLength = i;  
    
    return 0;
}