#include <avr/io.h>
#include <util/delay.h>

#include "Zumo32U4Motors.h"

int main(void)
{
	for (;;) {
        Zumo32U4Motors::setSpeeds(100, 100);
		_delay_ms(1000);
        Zumo32U4Motors::setSpeeds(-100, -100);
        _delay_ms(1000);
	}

	return -1;
}