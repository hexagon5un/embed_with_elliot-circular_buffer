#include "unity.h"
#include "cbuffer.h"

#define BUFFER_ARRAY_LENGTH 8

void setUp(void)
{
    
}

void tearDown(void)
{
    
}

void test_init_32(void)
{
    uint32_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 32);
    
	TEST_ASSERT_EQUAL_INT(BUFFER_EMPTY, status);
}

void test_read_empty_32(void){
    uint32_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 32);
    
    uint32_t data = 100;
    data = BUF_read32(&b);
    
	TEST_ASSERT_EQUAL_INT(0, data);
}

void test_write_to_almost_full_32(void){
    uint32_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 32);
    
    int i;
    for(i = 0; i < (BUFFER_ARRAY_LENGTH - 1); i++){
        status = BUF_write32(&b, 1);
    }
    
	TEST_ASSERT_EQUAL_INT(BUFFER_OK, status);
}

void test_write_to_full_32(void){
    uint32_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 32);
    
    int i;
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        status = BUF_write32(&b, 1);
    }
    
	TEST_ASSERT_EQUAL_INT(BUFFER_FULL, status);
}

void test_write_to_full_read_to_empty_32(void){
    uint32_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    uint32_t data;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 32);
    
    int i;
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        status = BUF_write32(&b, 1);
    }
    
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        data = BUF_read32(&b);
    }
    
    status = BUF_status(&b);
    
	TEST_ASSERT_EQUAL_INT(BUFFER_EMPTY, status);
}

void test_write3_read3_32(void){
    uint32_t dataIn[3] = {1,2,3};
    uint32_t dataOut[BUFFER_ARRAY_LENGTH] = {0};
    
    uint32_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    uint32_t data;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 32);
    
    int i;
    for(i = 0; i < 3; i++){
        status = BUF_write32(&b, dataIn[i]);
    }
    
    for(i = 0; i < 3; i++){
        dataOut[i] = BUF_read32(&b);
    }
    
    /* test each element of the array */
    for(i = 0; i < 3; i++){
        TEST_ASSERT_EQUAL_INT(dataIn[i], dataOut[i]);
    }
}

void test_write_overflow_32(void){
    uint32_t dataIn[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint32_t dataOut[BUFFER_ARRAY_LENGTH] = {0};
    
    uint32_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
    Buffer b;
    BufferStatus status;
    uint32_t data;
    
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 32);
    
    int i;
    for(i = 0; i < 10; i++){
        status = BUF_write32(&b, dataIn[i]);
    }
    
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        dataOut[i] = BUF_read32(&b);
    }
    
    /* test each element of the array */
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        TEST_ASSERT_EQUAL_INT(i, dataOut[i]);
    }
}

