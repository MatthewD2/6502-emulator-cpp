#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef int8_t BYTE;
typedef int16_t HALF_WORD;
typedef bool CLOCK;
typedef bool SIGNAL;

class CPU {
    public:
        CPU(); // Power Up State

        // Access Operations

        void OP_LDA();
        void OP_STA();
        void OP_LDX();
        void OP_LDY();
        void OP_STY();

        // Transfer Operations

        void OP_TAX();
        void OP_TXA();
        void OP_TAY();
        void OP_TYA();

        // Arithmetic Operations

        void OP_ADC();
        void OP_SBC();
        void OP_INC();
        void OP_DEC();
        void OP_INX();
        void OP_DEX();
        void OP_INY();
        void OP_DEY();

        // Shift Operations

        void OP_ASL();
        void OP_LSR();
        void OP_ROL();
        void OP_ROL();
        void OP_ROR();

        // Bitwise Operations

        void OP_AND();
        void OP_ORA();
        void OP_EOR();
        void OP_BIT();

        // Compare Operations

        void OP_CMP();
        void OP_CPX();
        void OP_CPY();

        // Branch Operations

        void OP_BCC();
        void OP_BCS();
        void OP_BEQ();
        void OP_BNE();
        void OP_BPL();
        void OP_BMI();
        void OP_BVC();
        void OP_BVS();

        // Jump Operations

        void OP_JMP();
        void OP_JSR();
        void OP_RTS();
        void OP_BRK();
        void OP_RTI();

        // Stack Operations

        void OP_PHA();
        void OP_PLA();
        void OP_PHP();
        void OP_PLP();
        void OP_TXS();
        void OP_TSX();

        // Flags Operations

        void OP_CLC();
        void OP_SEC();
        void OP_CLI();
        void OP_SEI();
        void OP_CLD();
        void OP_SED();
        void OP_CLV();

        // Other Operations

        void OP_NOP();
        

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

