#include <stdint.h>
#include <stddef.h>

#include "buffer.h"

Buffer::Buffer(uint16_t buff_size)
{
    buffer = new uint8_t[buff_size];
    readPtr = 0;
    writePtr = 0;
    this->buff_size = buff_size;
}

Buffer::~Buffer()
{
    delete buffer;
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