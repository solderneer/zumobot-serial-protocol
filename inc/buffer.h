#pragma once

#include <stdint.h>
#include <stddef.h>

typedef enum {FAIL, SUCCESS} status_t;

class Buffer {
public:
    Buffer(uint8_t* buffer, uint16_t buff_size);
    ~Buffer();

    void bufferReset(void);
    void bufferPut(uint8_t byte);
    int bufferGet(uint8_t* byte);
    bool bufferEmpty(void);
    bool bufferFull(void);
private:
    uint8_t* buffer;
    size_t readPtr;
    size_t writePtr;
    size_t buff_size;
};