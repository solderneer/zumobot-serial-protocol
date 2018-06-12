#include <stdio.h>
#include <stdint.h>
#include <iostream>

#include "buffer.h"

/* Unit Tests for buffer */
int main(void)
{
    Buffer buf1(10);
    uint8_t num1 = 0;
    uint8_t num2 = 0;
    uint8_t num3 = 0;

    buf1.bufferReset();
    buf1.bufferPut(10);
    buf1.bufferPut(20);
    buf1.bufferPut(30);

    buf1.bufferGet(&num1);
    buf1.bufferGet(&num2);
    buf1.bufferGet(&num3);

    std::cout << "First number:" << num1 << '\n';
    std::cout << "Second number:" << num2 << '\n';
    std::cout << "Third number:" << num3 << '\n';
}
