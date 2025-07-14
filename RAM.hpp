#include <cstdint>
#include <iostream>
#include <string.h>
#include <vector>
#include "6502.hpp"

class RAM {
    public:
        RAM();

        BYTE READ(ADDRESS addr);
        void WRITE(ADDRESS addr, BYTE data);

    private:
        BYTE _memory[MEM_CAPACITY];
};

RAM::RAM() {
    memset(_memory, 0, sizeof(BYTE) * MEM_CAPACITY); // zeros out the memory
}