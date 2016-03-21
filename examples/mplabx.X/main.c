#include "xc.h"
#include "cbuffer.h"
#include <stdio.h>

Buffer b;

void showStatus(void);

int main(void) {
    uint8_t i;
    BUF_init(&b);
    
    uint8_t values0[4] = {10,9,8,7};
    uint8_t values1[4] = {0,0,0,0};
    
    /* write 4 values to the buffer */
    for(i = 0; i < 4; i++){
        BUF_write(&b, values0[i]);
    }
    
    /* read 4 values from the buffer values */
    for(i=0; i < 4; i++){
        values1[i] = BUF_read(&b);
    }
    
    /* test for array equality */
    for(i=0; i < 4; i++){
        if(values0[i] != values1[i])
            while(1);
    }
    
    uint8_t values2[] = {125,124,123,122,121,120,119,118};
    uint8_t values3[8] = {0};
    
    /* write 8 values to the buffer */
    for(i = 0; i < 8; i++){
        BUF_write(&b, values2[i]);
    }
    
    /* read 8 values from the buffer values */
    for(i=0; i < 8; i++){
        values3[i] = BUF_read(&b);
    }
    
    /* test for array equality */
    for(i=0; i < 8; i++){
        if(values2[i] != values3[i])
            while(1);
    }
    
    
    
    return 0;
}

void showStatus(void){
    printf("\tEmpty Slots: %d\tFull Slots: %d\n",
            (int)BUF_emptySlots(&b),
            (int)BUF_fullSlots(&b));
    
    return;
}
