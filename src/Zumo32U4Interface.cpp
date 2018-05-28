#include <avr/io.h>
#include <Zumo32U4Interface.h>
#include <util/setbaud.h>
#include <settings.h>

void Zumo32U4Interface::init2()
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= (1 << U2X0);
#endif

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

}