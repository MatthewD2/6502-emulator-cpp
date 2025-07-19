#pragma once

#include <cstdint>
#include <exception>

typedef uint8_t BYTE;
typedef bool CLOCK;
typedef bool SIGNAL;
typedef uint16_t ADDRESS;
typedef BYTE (*MEM_READ)(ADDRESS);
typedef void (*MEM_WRITE)(ADDRESS, BYTE);

enum INSTRUCTION {

    // Access
    LDA, STA, LDX, STX, LDY, STY,
    
    //Transfer
    TAX, TXA, TAY, TYA, 
    
    //Arithmetic
    ADC, SBC, INC, DEC, INX, DEX, INY, DEY,
    
    //Shift
    ASL, LSR, ROL, ROR,
    
    //Bitwise
    AND, ORA, EOR, BIT,
    
    //Compare
    CMP, CPX, CPY,
    
    //Branch
    BCC, BCS, BEQ, BNE, BPL, BMI, BVC, BVS,
    
    //Jump
    JMP, JSR, RTS, BRK, RTI,
    
    //Stack
    PHA, PLA, PHP, PLP, TXS, TSX,
    
    //Flags
    CLC, SEC, CLI, SEI, CLD, SED, CLV,
    
    //Other
    NOP,

    // Illegal
    ILL

};