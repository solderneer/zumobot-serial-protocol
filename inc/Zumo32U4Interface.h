#pragma once

#include <stdint.h>
#include <stddef.h>

// Circular buffer implementation
typedef struct
{
    uint8_t* buffer;
    size_t readPtr;
    size_t writePtr;
    size_t buffSize;
} circular_buf;

// Public functions for buffer
int bufferReset(circular_buf* buf);
int bufferPut(circular_buf* buf, uint8_t byte);
int bufferGet(circular_buf* buf, uint8_t* byte);
bool bufferFull(circular_buf buf);
bool bufferEmpty(circular_buf buf);

class Zumo32U4Interface 
{
    public:
        static void UART_Transmit(uint8_t byte);
        static void UART_Receive(uint8_t* byte);
    private:
        static inline void init()
        {
            static bool initialized = false;
            
            if(!initialized)
            {
                initialized = true;
                init2();
            }
        }
        static void init2();
        static circular_buf UART_Buffer;
};
