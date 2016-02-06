#include "cbuffer.h"

/* declare two buffers */
Buffer b1;
Buffer b2;

void setup() {
  // properly initialize the buffer
  BUF_init(&b1);
  BUF_init(&b2);
}

void loop() {
  /* write 3 bytes to the buffer b1 */
  int8_t i = 0;
  BUF_write(&b1, i++);
  BUF_write(&b1, i++);
  BUF_write(&b1, i++);
  
  /* read 3 bytes from the buffer b1 */
  uint8_t b;
  BUF_read(&b1, &b);
  BUF_read(&b1, &b);  // this overwrites the previous value
  BUF_read(&b1, &b);  // this overwrites the previous value
  
  /* check the buffer status of buffer b1 */
  BUF_status(&b1);
  
  /* you can do the same with buffer b2 or any number of buffers */
  BUF_write(&b2, i++);
  BUF_write(&b2, i++);
  BUF_write(&b2, i++);
  
  /* read 3 bytes from the buffer b1 */
  BUF_read(&b2, &b);
  BUF_read(&b2, &b);  // this overwrites the previous value
  BUF_read(&b2, &b);  // this overwrites the previous value
  
  /* check the buffer status of buffer b1 */
  BUF_status(&b2);
  
}
