#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef int8_t BYTE;
typedef int16_t HALF_WORD;

class CPU {
    public:
        CPU(); // Power Up State

        // INPUTS

        

        // OUTPUTS
        

        void PrintRegisters(); // Print Registers for Debugging
    private:
        BYTE A;
        BYTE X;
        BYTE Y;
        HALF_WORD PC;
        BYTE S;
        BYTE P;
};

CPU::CPU() {
    A = 0;
    X = 0;
    Y = 0;
    PC = 0xFFFC;
    S = 0xFD;
    P = 0b00110100;

    cout << "POWER UP FINISHED" << endl;
}

void CPU::PrintRegisters() {
    cout << "A: " << (int) A << endl;
    cout << "X: " << (int) X << endl;
    cout << "Y: " << (int) Y << endl;
    cout << "PC: " << (int) PC << endl;
    cout << "S: " << (int) S << endl;
    cout << "P: " << (int) P << endl;
}

