#pragma once

#include <stdint.h>
#include <stddef.h>

#include "settings.h"
#include "buffer.h"

#define UART_BUFFER_SIZE 50
#define BAUD_PRESCALE (((F_CPU / (UART_BAUDRATE * 16UL))) - 1)

class Zumo32U4Serial 
{
    public:
        static void UART_TransmitByte(uint8_t byte);
        static void UART_TransmitBytes(uint8_t* bytes, uint16_t cnt);
        static int UART_ReceiveByte(uint8_t* byte); 
        static void UART_ReceiveBytes(uint8_t* bytes, uint16_t cnt);
        static void UART_ISR(uint8_t byte);
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
        static void init2(void);
        static uint8_t UART_Buffer_Raw[UART_BUFFER_SIZE];
        static Buffer UART_Buffer;
};