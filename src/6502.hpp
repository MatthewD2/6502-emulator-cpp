#pragma once

#include "macros.h"
#include "types.h"

#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <stdbool.h>
#include <iomanip>
#include <string.h>

using namespace std;

class CPU {
    public:

        CPU(); // Power Up State

        void EXECUTE(MEM_READ reader, MEM_WRITE writer);

        void RESET();

        void PrintRegisters(); // Print registers values for debugging

        // Interrupts

        void IRQ();
        void NMI();

        // Getters

        BYTE getA();
        BYTE getX();
        BYTE getY();
        ADDRESS getPC();
        BYTE getS();
        BYTE getP();
    
    private:

        // Access Operations

        void OP_LDA(BYTE opcode);
        void OP_STA(BYTE opcode);
        void OP_LDX(BYTE opcode);
        void OP_STX(BYTE opcode);
        void OP_LDY(BYTE opcode);
        void OP_STY(BYTE opcode);

        // Transfer Operations

        void OP_TAX(BYTE opcode);
        void OP_TXA(BYTE opcode);
        void OP_TAY(BYTE opcode);
        void OP_TYA(BYTE opcode);

        // Arithmetic Operations

        void OP_ADC(BYTE opcode);
        void OP_SBC(BYTE opcode);
        void OP_INC(BYTE opcode);
        void OP_DEC(BYTE opcode);
        void OP_INX(BYTE opcode);
        void OP_DEX(BYTE opcode);
        void OP_INY(BYTE opcode);
        void OP_DEY(BYTE opcode);

        // Shift Operations

        void OP_ASL(BYTE opcode);
        void OP_LSR(BYTE opcode);
        void OP_ROL(BYTE opcode);
        void OP_ROR(BYTE opcode);

        // Bitwise Operations

        void OP_AND(BYTE opcode);
        void OP_ORA(BYTE opcode);
        void OP_EOR(BYTE opcode);
        void OP_BIT(BYTE opcode);

        // Compare Operations

        void OP_CMP(BYTE opcode);
        void OP_CPX(BYTE opcode);
        void OP_CPY(BYTE opcode);

        // Branch Operations

        void OP_BCC(BYTE opcode);
        void OP_BCS(BYTE opcode);
        void OP_BEQ(BYTE opcode);
        void OP_BNE(BYTE opcode);
        void OP_BPL(BYTE opcode);
        void OP_BMI(BYTE opcode);
        void OP_BVC(BYTE opcode);
        void OP_BVS(BYTE opcode);

        // Jump Operations

        void OP_JMP(BYTE opcode);
        void OP_JSR(BYTE opcode);
        void OP_RTS(BYTE opcode);
        void OP_BRK(BYTE opcode);
        void OP_RTI(BYTE opcode);

        // Stack Operations

        void OP_PHA(BYTE opcode);
        void OP_PLA(BYTE opcode);
        void OP_PHP(BYTE opcode);
        void OP_PLP(BYTE opcode);
        void OP_TXS(BYTE opcode);
        void OP_TSX(BYTE opcode);

        // Flags Operations

        void OP_CLC(BYTE opcode);
        void OP_SEC(BYTE opcode);
        void OP_CLI(BYTE opcode);
        void OP_SEI(BYTE opcode);
        void OP_CLD(BYTE opcode);
        void OP_SED(BYTE opcode);
        void OP_CLV(BYTE opcode);

        // Other Operations

        void OP_NOP(BYTE opcode);

        // Addressing Modes:

        ADDRESS ADDR_ACC();
        ADDRESS ADDR_ABS();
        ADDRESS ADDR_ABS_X();
        ADDRESS ADDR_ABS_Y();
        ADDRESS ADDR_IMM();
        ADDRESS ADDR_IMP();
        ADDRESS ADDR_IND();
        ADDRESS ADDR_IND_X();
        ADDRESS ADDR_IND_Y();
        ADDRESS ADDR_REL();
        ADDRESS ADDR_ZERO();
        ADDRESS ADDR_ZERO_X();
        ADDRESS ADDR_ZERO_Y();

        void SetOpcodes(); // Populates our instruction look-up table on startup
        
        // Registers

        BYTE A;
        BYTE X;
        BYTE Y;
        ADDRESS PC;
        BYTE S;
        BYTE P;

        // Memory R/W Callbacks

        MEM_READ read;
        MEM_WRITE write;

        // Instruction LUT / Decoder

        INSTRUCTION decoder[OPCODE_LIMIT];

};