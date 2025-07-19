#pragma once

#define MEM_CAPACITY 0x10000

#define DECODER_CAPACITY 0xFF + 1

#define BYTE_MAX 0xFF
#define BCD_BYTE_MAX 0x99
#define DECIMAL_LARGEST_DIGIT 9
#define NIBBLE_ADJUST 0x6
#define NO_NIBBLE_ADJUST 0
#define BCD_BYTE_ADJUST 0x60
#define BCD_BYTE_NO_ADJUST 0

#define NMI_VECTOR_LOW 0xFFFA
#define NMI_VECTOR_HIGH 0xFFFB
#define IRQ_VECTOR_LOW 0xFFFE
#define IRQ_VECTOR_HIGH 0xFFFF
#define RESET_VECTOR_LOW 0xFFFC
#define RESET_VECTOR_HIGH 0xFFFD
#define BRK_VECTOR_LOW 0xFFFE
#define BRK_VECTOR_HIGH 0xFFFF

#define ILLEGAL_OP 0x03

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
  
