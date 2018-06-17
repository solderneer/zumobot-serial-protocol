#include <stdint.h>
#include <avr/io.h>

#include "Zumo32U4Serial.h"
#include "Zumo32U4Motors.h"
#include "Zumo32U4Interface.h"

void Zumo32U4Interface::init2(void)
{
    // Add initialization code here (there's nth to initialize right now)
}

void Zumo32U4Interface::processNextCommand(void)
{
    // Get the current byte
    uint8_t byte, state = 0;
    command_t command = UNSET;
    bool dir_left, dir_right = false;
    int16_t rmotor_speed,lmotor_speed = 0;

    Zumo32U4Serial::UART_ReceiveByte(&byte);
    while(state != 6)
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
                break;
            case 3: // Getting next byte for left motor
                if(Zumo32U4Serial::UART_ReceiveByte(&byte) == -1)
                    break;
                lmotor_speed = calculateMotorSpeed(&byte, dir_left);
                state = 4;
                break;
            case 4: // Getting next byte for right motor
                if(Zumo32U4Serial::UART_ReceiveByte(&byte) == -1)
                    break;
                rmotor_speed = calculateMotorSpeed(&byte, dir_right);
                state = 5;
                break;
            case 5: // Setting motor directions
                Zumo32U4Motors::setSpeeds(lmotor_speed, rmotor_speed);
                state = 6;
                break;
        }
    }
}

// Add private functions here for modularization as necessary

int16_t Zumo32U4Interface::calculateMotorSpeed(uint8_t* byte, bool direction)
{
    // Use this helper function to convert 8 bit unsigned motor speed to signed motor speed
    // between -400 and 400
    return -400;
}