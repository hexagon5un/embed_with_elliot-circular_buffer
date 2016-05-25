#include "xc.h"
#include "cbuffer.h"
#include <stdio.h>

#define ARR_LEN 8
#define ARR_WIDTH 8

Buffer b;
uint8_t dataArr[ARR_LEN];

void showStatus(void);

int main(void) {
    uint8_t i;
    BUF_init(&b, dataArr, ARR_LEN, ARR_WIDTH);
    showStatus();
    
    uint8_t values0[4] = {10,9,8,7};
    uint8_t values1[4] = {0,0,0,0};
    
    /* write 4 values to the buffer */
    printf("filling 4 element array\n");
    for(i = 0; i < 4; i++){
        BUF_write8(&b, values0[i]);
        showStatus();
    }
    
    /* read 4 values from the buffer values */
    printf("reading 4 element array\n");
    for(i=0; i < 4; i++){
        values1[i] = BUF_read8(&b);
        showStatus();
    }
    
    /* test for array equality */
    for(i=0; i < 4; i++){
        if(values0[i] != values1[i])
            while(1);
    }
    
    printf("4 element array comparison passed\n");
    
    uint8_t values2[] = {125,124,123,122,121,120,119,118};
    uint8_t values3[8] = {0};
    
    /* write 8 values to the buffer */
    printf("filling 8 element array\n");
    for(i = 0; i < 8; i++){
        BUF_write8(&b, values2[i]);
        showStatus();
    }
    
    /* attempt to write another 4 values */
    printf("attempting extra writes,  8 element array\n");
    for(i = 0; i < 4; i++){
        BUF_write8(&b, 100);
        showStatus();
    }
    
    /* read 8 values from the buffer values */
    printf("reading 8 element array\n");
    for(i=0; i < 8; i++){
        values3[i] = BUF_read8(&b);
        showStatus();
    }
    
    /* test for array equality */
    printf("comparing 8 element arrays\n");
    for(i=0; i < 8; i++){
        if(values2[i] != values3[i])
            while(1);
    }
    
    printf("8 element array comparison passed\n");

    return 0;
}

void showStatus(void){
    printf("\tEmpty Slots: %d\tFull Slots: %d\n",
            (int)BUF_emptySlots(&b),
            (int)BUF_fullSlots(&b));
    
    return;
}
