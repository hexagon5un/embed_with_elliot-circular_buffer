#include "unity.h"
#include "cbuffer.h"

#define BUFFER_ARRAY_LENGTH 8

uint8_t bufferArray[BUFFER_ARRAY_LENGTH] = {0};
Buffer b;
BufferStatus status;

void setUp(void)
{
    status = BUF_init(&b, bufferArray, BUFFER_ARRAY_LENGTH, 8);
}

void tearDown(void)
{
    
}

void test_init_8(void)
{
	TEST_ASSERT_EQUAL_INT(BUFFER_EMPTY, status);
}

void test_read_empty_8(void){
    uint8_t data = 100;
    data = BUF_read8(&b);
    
	TEST_ASSERT_EQUAL_INT(0, data);
}

void test_write_to_almost_full_8(void){
    int i;
    for(i = 0; i < (BUFFER_ARRAY_LENGTH - 1); i++){
        status = BUF_write8(&b, 1);
    }
    
	TEST_ASSERT_EQUAL_INT(BUFFER_OK, status);
}

void test_write_to_full_8(void){
    int i;
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        status = BUF_write8(&b, 1);
    }
    
	TEST_ASSERT_EQUAL_INT(BUFFER_FULL, status);
}

void test_write_to_full_8_status(void){
    int i;
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        BUF_write8(&b, 1);
    }
    
    status = BUF_status(&b);
    
	TEST_ASSERT_EQUAL_INT(BUFFER_FULL, status);
}

void test_write_to_full_read_to_empty_8(void){
    uint8_t data;
    
    int i;
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        status = BUF_write8(&b, 1);
    }
    
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        data = BUF_read8(&b);
    }
    
    status = BUF_status(&b);
    
	TEST_ASSERT_EQUAL_INT(BUFFER_EMPTY, status);
}

void test_write3_read3_8(void){
    uint8_t dataIn[3] = {1,2,3};
    uint8_t dataOut[BUFFER_ARRAY_LENGTH] = {0};
    
    uint8_t data;
    
    int i;
    for(i = 0; i < 3; i++){
        status = BUF_write8(&b, dataIn[i]);
    }
    
    for(i = 0; i < 3; i++){
        dataOut[i] = BUF_read8(&b);
    }
    
    /* test each element of the array */
    for(i = 0; i < 3; i++){
        TEST_ASSERT_EQUAL_INT(dataIn[i], dataOut[i]);
    }
}

void test_write_overflow_8(void){
    uint8_t dataIn[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint8_t dataOut[BUFFER_ARRAY_LENGTH] = {0};
    
    uint8_t data;
    
    int i;
    for(i = 0; i < 10; i++){
        status = BUF_write8(&b, dataIn[i]);
    }
    
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        dataOut[i] = BUF_read8(&b);
    }
    
    /* test each element of the array */
    for(i = 0; i < BUFFER_ARRAY_LENGTH; i++){
        TEST_ASSERT_EQUAL_INT(i, dataOut[i]);
    }
}