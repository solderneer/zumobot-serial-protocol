#include <avr/io.h>
#include <Zumo32U4Interface.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>
#include <settings.h>

void Zumo32U4Interface::init2(void)
{
    // Setting up UART registers
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= (1 << U2X0);
#endif

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

    // Setting up circular buffer
    uint8_t UART_Buffer_Raw[UART_BUFFER_SIZE];
    Zumo32U4Interface::UART_Buffer.buffer = UART_Buffer_Raw;
    Zumo32U4Interface::UART_Buffer.buffSize = UART_BUFFER_SIZE;

    bufferReset(&Zumo32U4Interface::UART_Buffer);
}

void Zumo32U4Interface::UART_Transmit(uint8_t byte)
{

}

void Zumo32U4Interface::UART_Receive(uint8_t* byte)
{
    bufferGet(&Zumo32U4Interface::UART_Buffer, byte);
}

ISR(USART_RX_vect)
{
    // TODO: Populate the ISRi
    sei();
    bufferPut(&Zumo32U4Interface::UART_Buffer, UDR0);
    reti();
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