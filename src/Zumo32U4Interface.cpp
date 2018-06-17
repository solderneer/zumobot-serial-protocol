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

int stateMachine(uint8_t* byte)
{
    int state = 0; // should give more verbose state declarations
    bool dir_left, dir_right;
    while(1)
    {
        switch(state)
        {
            case 0:
                if(*byte & 0b10000000)
                    state = 2;
                else 
                    state = 1;
            case 1:
                state = 10; // No idea how to deal with this
            case 2:
                if(*byte & 0b00000010) // Checking left motor direction
                    dir_left = true;
                else
                    dir_left = false;

                if(*byte & 0b00000001) // Checking right motor direction
                    dir_right = true;
                else
                    dir_right = false;
        }
    }
    return -1;
}