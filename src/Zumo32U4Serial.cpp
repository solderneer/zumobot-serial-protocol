#include <avr/io.h>
#include <Zumo32U4Serial.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>
#include <settings.h>

uint8_t Zumo32U4Serial::UART_Buffer_Raw[UART_BUFFER_SIZE];
circular_buf Zumo32U4Serial::UART_Buffer = {Zumo32U4Serial::UART_Buffer_Raw, 0, 0, UART_BUFFER_SIZE};

void Zumo32U4Serial::init2(void)
{
    // Setting up UART registers
    UBRR1H = UBRRH_VALUE;
    UBRR1L = UBRRL_VALUE;

#if USE_2X
    UCSR1C |= (1 << U2X1);
#else
    UCSR1C &= (1 << U2X1);
#endif

    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);

    bufferReset(&UART_Buffer);
}

void Zumo32U4Serial::UART_TransmitByte(uint8_t byte)
{
    // Blocking Transmit
    init();
    while(!(UCSR1A & (1 << UDRE1)))
    {
        UDR1 = byte;
    }
}

void Zumo32U4Serial::UART_TransmitBytes(uint8_t *bytes, uint16_t cnt)
{
    // Blocking Transmit
    uint16_t i;

    init();

    for(i = 0; i < cnt; i++) 
    {
        while(!(UCSR1A & (1 << UDRE1)))
        {
            UDR1 = *(bytes + i);
        }
    }
}

void Zumo32U4Serial::UART_ReceiveByte(uint8_t* byte)
{
    // Non-blocking Receive
    init();
    bufferGet(&UART_Buffer, byte);
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
    // TODO: Populate the ISR
    sei();
    bufferPut(&Zumo32U4Serial::UART_Buffer, UDR1);
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