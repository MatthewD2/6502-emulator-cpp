#pragma once

#include <cstdint>
#include <iostream>
#include <string.h>
#include <vector>

#include "types.h"
#include "macros.h"

class RAM {
    public:
        RAM();

        BYTE READ(ADDRESS addr);
        void WRITE(ADDRESS addr, BYTE data);

    private:
        BYTE _memory[MEM_CAPACITY];
};

RAM::RAM() {
    memset(_memory, 0, sizeof(BYTE) * MEM_CAPACITY);
}