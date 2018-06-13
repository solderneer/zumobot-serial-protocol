#include <avr/io.h>
#include <avr/interrupt.h>

#include "settings.h"
#include "buffer.h"
#include "Zumo32U4Serial.h"

uint8_t Zumo32U4Serial::UART_Buffer_Raw[UART_BUFFER_SIZE];
Buffer Zumo32U4Serial::UART_Buffer(Zumo32U4Serial::UART_Buffer_Raw, UART_BUFFER_SIZE);

void Zumo32U4Serial::init2(void)
{
    cli();  //Critical section of code: initializes UART interrupts
    UCSR1B = (1 << RXEN1) | (1 << TXEN1);   // Turn on the transmission and reception circuitry
    UCSR1C = (1 << UCSZ10) | (1 << UCSZ11); // Use 8-bit character sizes

    UBRR1H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
    UBRR1L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

    UCSR1B |= (1 << RXCIE1); // Enable the USART Recieve Complete interrupt (USART_RXC)
    UART_Buffer.bufferReset();

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
    status = UART_Buffer.bufferGet(byte);
    return status;
}

void Zumo32U4Serial::UART_ReceiveBytes(uint8_t *bytes, uint16_t cnt)
{
    // Non-blocking Receive
    uint16_t i;

    init();

    for(i = 0; i < cnt; i++)
    {
        UART_Buffer.bufferGet((bytes + i));
    }
}

void Zumo32U4Serial::UART_ISR(uint8_t byte)
{
    UART_Buffer.bufferPut(byte);
}

ISR(USART1_RX_vect)
{
    Zumo32U4Serial::UART_ISR(UDR1);
}