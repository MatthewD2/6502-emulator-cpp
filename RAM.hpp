#include <cstdint>
#include <iostream>
#include <string.h>
#include <vector>
#include "6502.hpp"



#define MEM_CAPACITY 0x10000

typedef int8_t BYTE;
typedef int16_t HALF_WORD;

class RAM {
    public:
        RAM();

        BYTE ACCESS(HALF_WORD addr, CLOCK clk, BYTE input, SIGNAL R_W_n);

    private:
        BYTE _memory[MEM_CAPACITY];
};

RAM::RAM() {
    memset(_memory, 0, sizeof(BYTE) * MEM_CAPACITY); // zeros out the memory
}
