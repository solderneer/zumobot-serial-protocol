#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// #include "Zumo32U4Motors.h"
#include "Zumo32U4Serial.h"
#include "settings.h"

int main(void)
{
    char* hello_world = "Hello World!\n";
    sei(); //Enabling global interrupts
    Zumo32U4Serial::UART_TransmitBytes((uint8_t*)hello_world, 13);
	for (;;) {

	}
	return -1;
}