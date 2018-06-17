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
    uint8_t byte = 0;

    bool dir_left = false; 
    bool dir_right = false;
    int16_t rmotor_speed = 0;
    int16_t lmotor_speed = 0;

    state_t state = START;

    Zumo32U4Serial::UART_ReceiveByte(&byte);
    while(state != END)
    {
        switch(state)
        {
            case START:
                if(byte & 0b10000000)
                    state = CONTROL_1;
                else
                    state = SENSOR_1;
                break;
            case SENSOR_1:
                state = END;
                break;
            case CONTROL_1:
                if(byte & 0b00000010) // Checking left motor direction
                    dir_left = true;
                if(byte & 0b00000001) // Checking right motor direction
                    dir_right = true;
                state = CONTROL_2;
                break;
            case CONTROL_2: // Getting next byte for left motor
                if(Zumo32U4Serial::UART_ReceiveByte(&byte) == -1)
                    break;
                lmotor_speed = calculateMotorSpeed(&byte, dir_left);
                state = CONTROL_3;
                break;
            case CONTROL_3: // Getting next byte for right motor
                if(Zumo32U4Serial::UART_ReceiveByte(&byte) == -1)
                    break;
                rmotor_speed = calculateMotorSpeed(&byte, dir_right);
                state = CONTROL_4;
                break;
            case CONTROL_4: // Setting motor directions
                Zumo32U4Motors::setSpeeds(lmotor_speed, rmotor_speed);
                state = END;
                break;
            default:
                state = END; // To prevent unknown state crashing the system
        }
    }
}

// Add private functions here for modularization as necessary

int16_t Zumo32U4Interface::calculateMotorSpeed(uint8_t* byte, bool direction)
{
    // Use this helper function to convert 8 bit unsigned motor speed to signed motor speed
    // between -400 and 400
    uint16_t temp = (uint16_t)(*byte << 1);
    if(direction) // If direction is true, apply 2s complement
    {
        temp ^= 0xFFFF; // flip all bits using XOR
        temp += 1;
    }
    return (int16_t)(temp);
}