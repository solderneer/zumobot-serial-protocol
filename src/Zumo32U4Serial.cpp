#include <avr/io.h>
#include <avr/interrupt.h>

#include "settings.h"
#include "Zumo32U4Serial.h"

uint8_t Zumo32U4Serial::UART_Buffer_Raw[USART_BUFFER_SIZE];
circular_buf Zumo32U4Serial::UART_Buffer = {Zumo32U4Serial::UART_Buffer_Raw, 0, 0, USART_BUFFER_SIZE};

void Zumo32U4Serial::init2(void)
{
    cli();  //Critical section of code: initializes UART interrupts
    UCSR1B = (1 << RXEN1) | (1 << TXEN1);   // Turn on the transmission and reception circuitry
    UCSR1C = (1 << UCSZ10) | (1 << UCSZ11); // Use 8-bit character sizes

    UBRR1H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
    UBRR1L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

    UCSR1B |= (1 << RXCIE1); // Enable the USART Recieve Complete interrupt (USART_RXC)
    bufferReset(&UART_Buffer);

    sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
}

void Zumo32U4Serial::UART_TransmitByte(uint8_t byte)
{
    // Blocking Transmit
    init();
    while(!(UCSR1A & (1 << UDRE1)));
    UDR1 = byte;
}

void Zumo32U4Serial::UART_TransmitBytes(uint8_t *bytes, uint16_t cnt)
{
    // Blocking Transmit
    uint16_t i;

    init();

    for(i = 0; i < cnt; i++) 
    {
        while(!(UCSR1A & (1 << UDRE1)));
        UDR1 = *(bytes + i);
    }
}

int Zumo32U4Serial::UART_ReceiveByte(uint8_t* byte)
{
    // Non-blocking Receive
    int status = 0;
    init();
    status = bufferGet(&UART_Buffer, byte);
    return status;
}

void Zumo32U4Serial::UART_ReceiveBytes(uint8_t *bytes, uint16_t cnt)
{
    // Non-blocking Receive
    uint16_t i;

    init();

    for(i = 0; i < cnt; i++)
    {
        bufferGet(&UART_Buffer, (bytes + i));
    }
}

ISR(USART1_RX_vect)
{
    bufferPut(&Zumo32U4Serial::UART_Buffer, UDR1);
}

/********Circular Buffer implementation to buffer UART bus*******/
int bufferReset(circular_buf* buf)
{
    int r = -1;

    if(buf)
    {
        buf->readPtr = 0;
        buf->writePtr = 0;
        r = 0;
    }

    return r;
}

int bufferPut(circular_buf* buf, uint8_t byte)
{
    int r = -1;

    if(buf)
    {
        buf->buffer[buf->writePtr] = byte;
        buf->writePtr = (buf->writePtr + 1) % buf->buffSize;
        
        if(buf->writePtr == buf->readPtr)
        {
            buf->readPtr = (buf->readPtr + 1) % buf->buffSize;
        }

        r = 0;
    }

    return r;
}

int bufferGet(circular_buf* buf, uint8_t* byte)
{
    int r = -1;

    if(buf && byte && !(bufferEmpty(*buf)))
    {
        *byte = buf->buffer[buf->readPtr];
        r = 0;
    }

    return r;
}

bool bufferEmpty(circular_buf buf)
{
    return (buf.readPtr == buf.writePtr);
}

bool bufferFull(circular_buf buf)
{
    return ((buf.writePtr + 1) % buf.buffSize) == buf.readPtr;
}