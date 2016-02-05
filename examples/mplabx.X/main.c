/*
 * File:   main.c
 * Author: Jason
 *
 * Created on February 5, 2016, 10:20 AM
 */


#include "xc.h"
#include "cbuffer.h"



int main(void) {
    Buffer b;
    BUF_init(&b);
    uint8_t a;
    
    /* write to the buffer too many times */
    uint8_t i;
    for(i = 0; i < 16; i++){
        BUF_write(&b, i);
    }
    
    /* read one value */
    BUF_read(&b, &a);
    
    /* write one value */
    a++;
    BUF_write(&b, a);
    
    /* read 3 values into a */
    BUF_read(&b, &a);
    BUF_read(&b, &a);
    BUF_read(&b, &a);
    
    
    
    return 0;
}


