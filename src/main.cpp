#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// #include "Zumo32U4Motors.h"
// #include "Zumo32U4Serial.h"
#include "settings.h"

int main(void)
{
    /*
    sei(); // Enabling global interrupts
	for (;;) {
        Zumo32U4Serial::UART_TransmitByte('c');
		_delay_ms(1000);
	}*/

    UCSR1B = (1 << RXEN1) | (1 << TXEN1);   // Turn on the transmission and reception circuitry
    UCSR1C = (1 << UCSZ10) | (1 << UCSZ11); // Use 8-bit character sizes

    UBRR1H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
    UBRR1L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

    UCSR1B |= (1 << RXCIE1); // Enable the USART Recieve Complete interrupt (USART_RXC)
    sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed

    for (;;) // Loop forever
    {
         // Do nothing - echoing is handled by the ISR instead of in the main loop
    }   

	return -1;
}

ISR(USART1_RX_vect)
{
   char ReceivedByte;
   ReceivedByte = UDR1; // Fetch the received byte value into the variable "ByteReceived"
   UDR1 = ReceivedByte; // Echo back the received byte back to the computer
}