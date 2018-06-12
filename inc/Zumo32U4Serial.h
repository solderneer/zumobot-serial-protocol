#pragma once

#include <stdint.h>
#include <stddef.h>
#include <settings.h>

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

class Zumo32U4Serial 
{
    public:
        static uint8_t UART_Buffer_Raw[USART_BUFFER_SIZE];
        static circular_buf UART_Buffer;
        static void UART_TransmitByte(uint8_t byte);
        static void UART_TransmitBytes(uint8_t* bytes, uint16_t cnt);
        static void UART_ReceiveByte(uint8_t* byte); 
        static void UART_ReceiveBytes(uint8_t* bytes, uint16_t cnt);
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
};