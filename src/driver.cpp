#include "6502.hpp"

BYTE _memory[MEM_CAPACITY];

BYTE READ(ADDRESS addr) {
    
    return _memory[addr];

}

void WRITE(ADDRESS addr, BYTE data) {

    _memory[addr] = data;

}

/* For debugging purposes: prints out individual bytes in hexadecimal
    format. */

void HEX_PRINT(BYTE byte) {
        
        cout 
        << "0x"
        << hex 
        << uppercase
        << std::setw(2) 
        << setfill('0')
        << (int) (byte)
        << dec
        << endl;

}

/* Takes as an argument the filename/location of the binary
    to execute as well as a base address to store the binary in memory. */

int LOAD_ROM(const string& filename, ADDRESS base_addr) {

    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        
        cerr << "Failed to open binary" << endl;

        return 1;

    }

    memset(_memory, ILLEGAL_OP, sizeof(BYTE) * MEM_CAPACITY);

    int byte;
    
    ADDRESS address = base_addr;
    
    while ((byte = file.get()) != EOF) {
        
        if (address >= 0xFFFF) break;
        
        _memory[address++] = static_cast<BYTE>(byte);

    }

    file.close();

    cout << "FINISHED LOADING ROM" << endl;

    return 0;

}

int main() {

    LOAD_ROM("../tests/nestest.nes", 0xC000);

    CPU test = CPU(READ, WRITE);

    test.EXECUTE();

    return 0;
}