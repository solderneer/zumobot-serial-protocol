#pragma once
#include <stdint.h>

typedef enum {UNSET, CONTROL, SENSOR} command_t;

class Zumo32U4Interface {
public:
    static void processNextCommand(void);
private:
    static inline void init(){
        static bool uninitialized = false;

        if(!uninitialized) 
        {
            uninitialized = true;
            init2();
        }
    }

    static void init2(void);
    static int16_t calculateMotorSpeed(uint8_t* byte, bool direction);
};