#include "unity.h"
#include "cbuffer.h"

#define BUFFER_ARRAY_LENGTH 8

void setUp(void)
{
    
}

void tearDown(void)
{
    
}

void test_init_16(void)
{
    uint16_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 16);
    
	TEST_ASSERT_EQUAL_INT(BUFFER_EMPTY, status);
}

void test_read_empty_16(void){
    uint16_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 16);
    
    uint16_t data = 100;
    data = BUF_read16(&b);
    
	TEST_ASSERT_EQUAL_INT(0, data);
}

void test_write_to_almost_full_16(void){
    uint16_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 16);
    
    int i;
    for(i = 0; i < (BUFFER_ARRAY_LENGTH - 1); i++){
        status = BUF_write16(&b, 1);
    }
    
	TEST_ASSERT_EQUAL_INT(BUFFER_OK, status);
}

void test_write_to_full_16(void){
    uint16_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 16);
    
    int i;
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        status = BUF_write16(&b, 1);
    }
    
	TEST_ASSERT_EQUAL_INT(BUFFER_FULL, status);
}

void test_write_to_full_read_to_empty_16(void){
    uint16_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    uint16_t data;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 16);
    
    int i;
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        status = BUF_write16(&b, 1);
    }
    
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        data = BUF_read16(&b);
    }
    
    status = BUF_status(&b);
    
	TEST_ASSERT_EQUAL_INT(BUFFER_EMPTY, status);
}

void test_write3_read3_16(void){
    uint16_t dataIn[3] = {1,2,3};
    uint16_t dataOut[BUFFER_ARRAY_LENGTH] = {0};
    
    uint16_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    uint16_t data;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 16);
    
    int i;
    for(i = 0; i < 3; i++){
        status = BUF_write16(&b, dataIn[i]);
    }
    
    for(i = 0; i < 3; i++){
        dataOut[i] = BUF_read16(&b);
    }
    
    /* test each element of the array */
    for(i = 0; i < 3; i++){
        TEST_ASSERT_EQUAL_INT(dataIn[i], dataOut[i]);
    }
}

void test_write_overflow_16(void){
    uint16_t dataIn[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint16_t dataOut[BUFFER_ARRAY_LENGTH] = {0};
    
    uint16_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    uint16_t data;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 16);
    
    int i;
    for(i = 0; i < 10; i++){
        status = BUF_write16(&b, dataIn[i]);
    }
    
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        dataOut[i] = BUF_read16(&b);
    }
    
    /* test each element of the array */
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        TEST_ASSERT_EQUAL_INT(i, dataOut[i]);
    }
}