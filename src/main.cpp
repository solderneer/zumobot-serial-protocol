#include <avr/io.h>
#include <util/delay.h>

#include "Zumo32U4Motors.h"
#include "Zumo32U4Serial.h"

int main(void)
{
	for (;;) {
        Zumo32U4Serial::UART_TransmitByte('c');
		_delay_ms(1000);
	}

	return -1;
}