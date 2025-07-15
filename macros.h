#pragma once

#include <cstdint>

#define MEM_CAPACITY 0x10000
#define OPCODE_LIMIT 0xFF + 1

#define NEGATIVE(x) (((x) & 0b10000000) != 0)
#define SIGN_EXTEND(x) ((x) |= 0b1111111100000000)
#define SET_ZERO_PAGE(x) ((x) &= 0b0000000011111111)

#define SET_ZERO_FLAG(status, bit)           \
  do {                                       \
    (status) = ((status) & ~0b00000010)      \
             | ( ((bit) ? 0b00000010 : 0) ); \
  } while (0)

#define SET_NEGATIVE_FLAG(status, bit)       \
  do {                                       \
    (status) = ((status) & ~0b10000000)      \
             | ( ((bit) ? 0b10000000 : 0) ); \
  } while (0)

#define SET_CARRY_FLAG(status, bit)          \
  do {                                       \
    (status) = ((status) & ~0b00000001)      \
             | ( ((bit) ? 0b00000001 : 0) ); \
  } while (0)

#define SET_OVERFLOW_FLAG(status, bit)       \
  do {                                       \
    (status) = ((status) & ~0b01000000)      \
             | ( ((bit) ? 0b01000000 : 0) ); \
  } while (0)

#define SET_DECIMAL_FLAG(status, bit)        \
  do {                                       \
    (status) = ((status) & ~0b00001000)      \
             | ( ((bit) ? 0b00001000 : 0) ); \
  } while (0)

#define SET_INTERRUPT_FLAG(status, bit)      \
  do {                                       \
    (status) = ((status) & ~0b00000100)      \
             | ( ((bit) ? 0b00000100 : 0) ); \
  } while (0)

#define SET_B_FLAG(status, bit)              \
  do {                                       \
    (status) = ((status) & ~0b00010000)      \
             | ( ((bit) ? 0b00010000 : 0) ); \
  } while (0)
  
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
    NOP

};