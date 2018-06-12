#pragma once

#include <stdint.h>
#include <stddef.h>

class Buffer {
public:
    Buffer(uint16_t buff_size);
    int bufferReset(void);
    int bufferPut(uint8_t byte);
    int bufferGet(uint8_t* byte);
    bool bufferEmpty(void);
    bool bufferFull(void);
private:
    uint8_t* buffer;
    size_t readPtr;
    size_t writePtr;
};