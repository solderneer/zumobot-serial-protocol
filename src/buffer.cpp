#include <stdint.h>
#include <stddef.h>

#include "buffer.h"

Buffer::Buffer(uint8_t* buffer, uint16_t buff_size)
{
    readPtr = 0;
    writePtr = 0;
    this->buffer = buffer;
    this->buff_size = buff_size;
}

Buffer::~Buffer()
{
    // Don't need to do anything here
}

void Buffer::bufferReset(void)
{
    readPtr = 0;
    writePtr = 0;
}

void Buffer::bufferPut(uint8_t byte)
{
    buffer[writePtr] = byte;
    writePtr = (writePtr + 1) % buff_size;

    if(writePtr == readPtr)
    {
        readPtr = (readPtr + 1) % buff_size;
    }
}

int Buffer::bufferGet(uint8_t *byte)
{
    if(byte && !(bufferEmpty()))
    {
        *byte = buffer[readPtr];
        readPtr = (readPtr + 1) % buff_size;
        return SUCCESS;
    }

    return FAIL;
}

bool Buffer::bufferEmpty(void)
{
    return (readPtr == writePtr);
}

bool Buffer::bufferFull(void)
{
     return ((writePtr + 1) % buff_size) == readPtr;
}