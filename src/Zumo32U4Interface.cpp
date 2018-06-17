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
    uint8_t byte, state = 0;
    command_t command = UNSET;
    bool dir_left, dir_right = false;

    Zumo32U4Serial::UART_ReceiveByte(&byte);
    while(1)
    {
        switch(state)
        {
            case 0:
                if(byte & 0b10000000)
                    state = 2;
                else
                    state = 1;
                break;
            case 1:
                command = SENSOR;
                state = 10;
                break;
            case 2:
                command = CONTROL;
                if(byte & 0b00000010) // Checking left motor direction
                    dir_left = true;
                if(byte & 0b00000001) // Checking right motor direction
                    dir_right = true;
                state = 3;
        }
    }
    return -1;
}

// Add private functions here for modularization as necessary