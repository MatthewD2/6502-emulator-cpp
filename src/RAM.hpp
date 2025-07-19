#pragma once

#include <cstdint>
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>

#include "types.h"
#include "macros.h"

using namespace std;

class RAM {
    public:
        RAM();

        BYTE READ(ADDRESS addr);

        void WRITE(ADDRESS addr, BYTE data);

        /* load's a binary file into memory to be executed
            by the 6502. 
            Returns 1 on error, 0 on success. */

        int LOAD_ROM(const string& filename);

    private:
        BYTE _memory[MEM_CAPACITY];
};

RAM::RAM() {

    memset(_memory, 0, sizeof(BYTE) * MEM_CAPACITY);

}

BYTE RAM::READ(ADDRESS addr) {
    
    return _memory[addr];

}

void RAM::WRITE(ADDRESS addr, BYTE data) {

    _memory[addr] = data;

}

int RAM::LOAD_ROM(const string& filename) {

    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        
        cerr << "Failed to open binary" << endl;

        return 1;

    }

    memset(_memory, ILLEGAL_OP, sizeof(BYTE) * MEM_CAPACITY);

    int byte;
    
    ADDRESS address = 0;
    
    while ((byte = file.get()) != EOF) {
        
        if (address >= MEM_CAPACITY) break;
        
        _memory[address++] = static_cast<BYTE>(byte);

    }

    file.close();

    return 0;

}