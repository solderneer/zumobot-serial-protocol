#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// #include "Zumo32U4Motors.h"
#include "Zumo32U4Serial.h"
#include "settings.h"

int main(void)
{
    sei(); //Enabling global interrupts
    uint8_t recieved = 0;
    int status = 0;

	for (;;) {
        status = Zumo32U4Serial::UART_ReceiveByte(&recieved); 
        while(status == 0)
            status = Zumo32U4Serial::UART_ReceiveByte(&recieved); 

        Zumo32U4Serial::UART_TransmitByte(recieved);
	}
	return -1;
}