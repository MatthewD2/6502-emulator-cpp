#include "6502.hpp"
#include "RAM.hpp"

BYTE _memory[MEM_CAPACITY];

BYTE READ(ADDRESS addr) {
    
    return _memory[addr];

}

void WRITE(ADDRESS addr, BYTE data) {

    _memory[addr] = data;

}

int LOAD_ROM(const string& filename) {

    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        
        cerr << "Failed to open binary" << endl;

        return 1;

    }

    memset(_memory, ILLEGAL_OP, sizeof(BYTE) * MEM_CAPACITY);

    int byte;
    
    ADDRESS address = 0x8000;
    
    while ((byte = file.get()) != EOF) {
        
        if (address >= MEM_CAPACITY) break;
        
        _memory[address++] = static_cast<BYTE>(byte);

    }

    file.close();

    cout << "FINISHED LOADING ROM" << endl;

    return 0;

}

int main() {

    LOAD_ROM("../tests/test.bin");

    return 0;
}