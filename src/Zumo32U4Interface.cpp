#include <stdint.h>
#include <avr/io.h>

#include "Zumo32U4Serial.h"
#include "Zumo32U4Interface.h"

void Zumo32U4Interface::init2(void)
{
    // Add initialization code here (there's nth to initialize right now)
}

int Zumo32U4Interface::processNextCommand(void)
{
    // Get the current byte
    uint8_t currentByte = 0;
    command_t commandStatus = UNSET;
    Zumo32U4Serial::UART_ReceiveByte(&currentByte);

    if(commandStatus == UNSET)
    {
        // Add state machine for reading command byte
    }

    if(commandStatus == CONTROL)
    {
        // Add state machine for reading control byte
    }

    if(commandStatus == SENSOR)
    {
        // Add state machine for reading sensor byte
    }


    return -1;
}

// Add private functions here for modularization as necessary