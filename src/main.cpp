#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// #include "Zumo32U4Motors.h"
#include "Zumo32U4Interface.h"
#include "settings.h"

int main(void)
{
    sei(); //Enabling global interrupts
    /*
    uint8_t recieved = 0;
    int status = 0;
	for (;;) {
        status = Zumo32U4Serial::UART_ReceiveByte(&recieved); 
        while(status == 0)
            status = Zumo32U4Serial::UART_ReceiveByte(&recieved); 

        Zumo32U4Serial::UART_TransmitByte(recieved);
	}*/

    for(;;) {
        Zumo32U4Interface::processNextCommand();
        _delay_ms(500);
    }
	return -1;
}