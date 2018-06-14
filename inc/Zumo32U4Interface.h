#pragma once

class Zumo32U4Interface {
public:
    static void pollState(void);
    static void getCommand(void);
    static void pushCommand(void);
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
};