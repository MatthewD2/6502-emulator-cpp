#include "6502.hpp"

CPU::CPU(MEM_READ reader, MEM_WRITE writer) {

    read = reader;

    write = writer;

    A = 0;
    X = 0;
    Y = 0;
    S = 0xFD;
    P = 0b00110100;

    BYTE pc_low_byte = read(RESET_VECTOR_LOW);
    BYTE pc_high_byte = read(RESET_VECTOR_HIGH);

    PC = (pc_high_byte << 8) | pc_low_byte;

    SetOpcodes();

    cout << "POWER UP FINISHED" << endl;

}

void CPU::RESET() {

    BYTE pc_low_byte = read(RESET_VECTOR_LOW);
    BYTE pc_high_byte = read(RESET_VECTOR_HIGH);

    PC = (pc_high_byte << 8) | pc_low_byte;

    S -= 3;
    P |= 0b00000100;

    cout << "RESET FINISHED" << endl;

}

void CPU::EXECUTE() {
    
    while (1) {

        BYTE opcode = read(PC);

        PC++;

        INSTRUCTION instr = decoder[opcode];

        switch (instr) {

            // Access
            case INSTRUCTION::LDA:
                OP_LDA(opcode);
                break;
            case INSTRUCTION::STA:
                OP_STA(opcode);
                break;
            case INSTRUCTION::LDX:
                OP_LDX(opcode);
                break;
            case INSTRUCTION::STX:
                OP_STX(opcode);
                break;
            case INSTRUCTION::LDY:
                OP_LDY(opcode);
                break;
            case INSTRUCTION::STY:
                OP_STY(opcode);
                break;
                
            // Transfer
            case INSTRUCTION::TAX:
                OP_TAX(opcode);
                break;
            case INSTRUCTION::TXA:
                OP_TXA(opcode);
                break;
            case INSTRUCTION::TAY:
                OP_TAY(opcode);
                break;
            case INSTRUCTION::TYA:
                OP_TYA(opcode);
                break;

            // Arithmetic
            case INSTRUCTION::ADC:
                OP_ADC(opcode);
                break;
            case INSTRUCTION::SBC:
                OP_SBC(opcode);
                break;
            case INSTRUCTION::INC:
                OP_INC(opcode);
                break;
            case INSTRUCTION::DEC:
                OP_DEC(opcode);
                break;
            case INSTRUCTION::INX:
                OP_INX(opcode);
                break;
            case INSTRUCTION::DEX:
                OP_DEX(opcode);
                break;
            case INSTRUCTION::INY:
                OP_INY(opcode);
                break;
            case INSTRUCTION::DEY:
                OP_DEY(opcode);
                break;
                
            // Shift
            case INSTRUCTION::ASL:
                OP_ASL(opcode);
                break;
            case INSTRUCTION::LSR:
                OP_LSR(opcode);
                break;
            case INSTRUCTION::ROL:
                OP_ROL(opcode);
                break;
            case INSTRUCTION::ROR:
                OP_ROR(opcode);
                break;

            // Bitwise
            case INSTRUCTION::AND:
                OP_AND(opcode);
                break;
            case INSTRUCTION::ORA:
                OP_ORA(opcode);
                break;
            case INSTRUCTION::EOR:
                OP_EOR(opcode);
                break;
            case INSTRUCTION::BIT:
                OP_BIT(opcode);
                break;

            // Compare
            case INSTRUCTION::CMP:
                OP_CMP(opcode);
                break;
            case INSTRUCTION::CPX:
                OP_CPX(opcode);
                break;
            case INSTRUCTION::CPY:
                OP_CPY(opcode);
                break;

            // Branch
            case INSTRUCTION::BCC:
                OP_BCC(opcode);
                break;
            case INSTRUCTION::BCS:
                OP_BCS(opcode);
                break;
            case INSTRUCTION::BEQ:
                OP_BEQ(opcode);
                break;
            case INSTRUCTION::BNE:
                OP_BNE(opcode);
                break;
            case INSTRUCTION::BPL:
                OP_BPL(opcode);
                break;
            case INSTRUCTION::BMI:
                OP_BMI(opcode);
                break;
            case INSTRUCTION::BVC:
                OP_BVC(opcode);
                break;
            case INSTRUCTION::BVS:
                OP_BVS(opcode);
                break;

            // Jump
            case INSTRUCTION::JMP:
                OP_JMP(opcode);
                break;
            case INSTRUCTION::JSR:
                OP_JSR(opcode);
                break;
            case INSTRUCTION::RTS:
                OP_RTS(opcode);
                break;
            case INSTRUCTION::RTI:
                OP_RTI(opcode);
                break;
            case INSTRUCTION::BRK:
                OP_BRK(opcode);
                break;
            
            // Stack
            case INSTRUCTION::PHA:
                OP_PHA(opcode);
                break;
            case INSTRUCTION::PLA:
                OP_PLA(opcode);
                break;
            case INSTRUCTION::PHP:
                OP_PHP(opcode);
                break;
            case INSTRUCTION::PLP:
                OP_PLP(opcode);
                break;
            case INSTRUCTION::TSX:
                OP_TSX(opcode);
                break;
            case INSTRUCTION::TXS:
                OP_TXS(opcode);
                break;

            // Flags
            case INSTRUCTION::CLC:
                OP_CLC(opcode);
                break;
            case INSTRUCTION::SEC:
                OP_SEC(opcode);
                break;
            case INSTRUCTION::CLI:
                OP_CLI(opcode);
                break;
            case INSTRUCTION::SEI:
                OP_SEI(opcode);
                break;
            case INSTRUCTION::CLD:
                OP_CLD(opcode);
                break;
            case INSTRUCTION::SED:
                OP_SED(opcode);
                break;
            case INSTRUCTION::CLV:
                OP_CLV(opcode);
                break;

            // Other
            case INSTRUCTION::NOP:
                OP_NOP(opcode);
                break;
            
            default:
                cout << "End of Program or Illegal Opcode Found" << endl;
                return; // exit execution once we come across a non-existant operation
        }

    }

}

void CPU::SetOpcodes() {

    memset(decoder, INSTRUCTION::ILL, sizeof(INSTRUCTION) * DECODER_CAPACITY);

    // Access
    decoder[0xA9] = INSTRUCTION::LDA;
    decoder[0xA5] = INSTRUCTION::LDA;
    decoder[0xB5] = INSTRUCTION::LDA;
    decoder[0xAD] = INSTRUCTION::LDA;
    decoder[0xBD] = INSTRUCTION::LDA;
    decoder[0xB9] = INSTRUCTION::LDA;
    decoder[0xA1] = INSTRUCTION::LDA;
    decoder[0xB1] = INSTRUCTION::LDA;

    decoder[0xA2] = INSTRUCTION::LDX;
    decoder[0xA6] = INSTRUCTION::LDX;
    decoder[0xB6] = INSTRUCTION::LDX;
    decoder[0xAE] = INSTRUCTION::LDX;
    decoder[0xBE] = INSTRUCTION::LDX;

    decoder[0xA0] = INSTRUCTION::LDY;
    decoder[0xA4] = INSTRUCTION::LDY;
    decoder[0xB4] = INSTRUCTION::LDY;
    decoder[0xAC] = INSTRUCTION::LDY;
    decoder[0xBC] = INSTRUCTION::LDY;

    decoder[0x85] = INSTRUCTION::STA;
    decoder[0x95] = INSTRUCTION::STA;
    decoder[0x8D] = INSTRUCTION::STA;
    decoder[0x9D] = INSTRUCTION::STA;
    decoder[0x99] = INSTRUCTION::STA;
    decoder[0x81] = INSTRUCTION::STA;
    decoder[0x91] = INSTRUCTION::STA;

    decoder[0x86] = INSTRUCTION::STX;
    decoder[0x96] = INSTRUCTION::STX;
    decoder[0x8E] = INSTRUCTION::STX;

    decoder[0x84] = INSTRUCTION::STY;
    decoder[0x94] = INSTRUCTION::STY;
    decoder[0x8C] = INSTRUCTION::STY;

    // Transfer
    decoder[0xAA] = INSTRUCTION::TAX;
    decoder[0x8A] = INSTRUCTION::TXA;
    decoder[0xA8] = INSTRUCTION::TAY;
    decoder[0x98] = INSTRUCTION::TYA;
    decoder[0xBA] = INSTRUCTION::TSX;
    decoder[0x9A] = INSTRUCTION::TXS;

    // Arithmetic
    decoder[0x69] = INSTRUCTION::ADC;
    decoder[0x65] = INSTRUCTION::ADC;
    decoder[0x75] = INSTRUCTION::ADC;
    decoder[0x6D] = INSTRUCTION::ADC;
    decoder[0x7D] = INSTRUCTION::ADC;
    decoder[0x79] = INSTRUCTION::ADC;
    decoder[0x61] = INSTRUCTION::ADC;
    decoder[0x71] = INSTRUCTION::ADC;

    decoder[0xE9] = INSTRUCTION::SBC;
    decoder[0xE5] = INSTRUCTION::SBC;
    decoder[0xF5] = INSTRUCTION::SBC;
    decoder[0xED] = INSTRUCTION::SBC;
    decoder[0xFD] = INSTRUCTION::SBC;
    decoder[0xF9] = INSTRUCTION::SBC;
    decoder[0xE1] = INSTRUCTION::SBC;
    decoder[0xF1] = INSTRUCTION::SBC;

    decoder[0xE6] = INSTRUCTION::INC;
    decoder[0xF6] = INSTRUCTION::INC;
    decoder[0xEE] = INSTRUCTION::INC;
    decoder[0xFE] = INSTRUCTION::INC;

    decoder[0xC6] = INSTRUCTION::DEC;
    decoder[0xD6] = INSTRUCTION::DEC;
    decoder[0xCE] = INSTRUCTION::DEC;
    decoder[0xDE] = INSTRUCTION::DEC;

    decoder[0xE8] = INSTRUCTION::INX;
    decoder[0xCA] = INSTRUCTION::DEX;
    decoder[0xC8] = INSTRUCTION::INY;
    decoder[0x88] = INSTRUCTION::DEY;

    // Shift
    decoder[0x0A] = INSTRUCTION::ASL;
    decoder[0x06] = INSTRUCTION::ASL;
    decoder[0x16] = INSTRUCTION::ASL;
    decoder[0x0E] = INSTRUCTION::ASL;
    decoder[0x1E] = INSTRUCTION::ASL;

    decoder[0x4A] = INSTRUCTION::LSR;
    decoder[0x46] = INSTRUCTION::LSR;
    decoder[0x56] = INSTRUCTION::LSR;
    decoder[0x4E] = INSTRUCTION::LSR;
    decoder[0x5E] = INSTRUCTION::LSR;

    decoder[0x2A] = INSTRUCTION::ROL;
    decoder[0x26] = INSTRUCTION::ROL;
    decoder[0x36] = INSTRUCTION::ROL;
    decoder[0x2E] = INSTRUCTION::ROL;
    decoder[0x3E] = INSTRUCTION::ROL;

    decoder[0x6A] = INSTRUCTION::ROR;
    decoder[0x66] = INSTRUCTION::ROR;
    decoder[0x76] = INSTRUCTION::ROR;
    decoder[0x6E] = INSTRUCTION::ROR;
    decoder[0x7E] = INSTRUCTION::ROR;

    // Bitwise
    decoder[0x29] = INSTRUCTION::AND;
    decoder[0x25] = INSTRUCTION::AND;
    decoder[0x35] = INSTRUCTION::AND;
    decoder[0x2D] = INSTRUCTION::AND;
    decoder[0x3D] = INSTRUCTION::AND;
    decoder[0x39] = INSTRUCTION::AND;
    decoder[0x21] = INSTRUCTION::AND;
    decoder[0x31] = INSTRUCTION::AND;

    decoder[0x09] = INSTRUCTION::ORA;
    decoder[0x05] = INSTRUCTION::ORA;
    decoder[0x15] = INSTRUCTION::ORA;
    decoder[0x0D] = INSTRUCTION::ORA;
    decoder[0x1D] = INSTRUCTION::ORA;
    decoder[0x19] = INSTRUCTION::ORA;
    decoder[0x01] = INSTRUCTION::ORA;
    decoder[0x11] = INSTRUCTION::ORA;

    decoder[0x49] = INSTRUCTION::EOR;
    decoder[0x45] = INSTRUCTION::EOR;
    decoder[0x55] = INSTRUCTION::EOR;
    decoder[0x4D] = INSTRUCTION::EOR;
    decoder[0x5D] = INSTRUCTION::EOR;
    decoder[0x59] = INSTRUCTION::EOR;
    decoder[0x41] = INSTRUCTION::EOR;
    decoder[0x51] = INSTRUCTION::EOR;

    decoder[0x24] = INSTRUCTION::BIT;
    decoder[0x2C] = INSTRUCTION::BIT;

    // Compare
    decoder[0xC9] = INSTRUCTION::CMP;
    decoder[0xC5] = INSTRUCTION::CMP;
    decoder[0xD5] = INSTRUCTION::CMP;
    decoder[0xCD] = INSTRUCTION::CMP;
    decoder[0xDD] = INSTRUCTION::CMP;
    decoder[0xD9] = INSTRUCTION::CMP;
    decoder[0xC1] = INSTRUCTION::CMP;
    decoder[0xD1] = INSTRUCTION::CMP;

    decoder[0xE0] = INSTRUCTION::CPX;
    decoder[0xE4] = INSTRUCTION::CPX;
    decoder[0xEC] = INSTRUCTION::CPX;

    decoder[0xC0] = INSTRUCTION::CPY;
    decoder[0xC4] = INSTRUCTION::CPY;
    decoder[0xCC] = INSTRUCTION::CPY;

    // Branch
    decoder[0x90] = INSTRUCTION::BCC;
    decoder[0xB0] = INSTRUCTION::BCS;
    decoder[0xF0] = INSTRUCTION::BEQ;
    decoder[0xD0] = INSTRUCTION::BNE;
    decoder[0x10] = INSTRUCTION::BPL;
    decoder[0x30] = INSTRUCTION::BMI;
    decoder[0x50] = INSTRUCTION::BVC;
    decoder[0x70] = INSTRUCTION::BVS;

    // Jump
    decoder[0x4C] = INSTRUCTION::JMP;
    decoder[0x6C] = INSTRUCTION::JMP;
    decoder[0x20] = INSTRUCTION::JSR;
    decoder[0x60] = INSTRUCTION::RTS;
    decoder[0x00] = INSTRUCTION::BRK;
    decoder[0x40] = INSTRUCTION::RTI;

    // Stack
    decoder[0x48] = INSTRUCTION::PHA;
    decoder[0x68] = INSTRUCTION::PLA;
    decoder[0x08] = INSTRUCTION::PHP;
    decoder[0x28] = INSTRUCTION::PLP;

    // Flags
    decoder[0x18] = INSTRUCTION::CLC;
    decoder[0x38] = INSTRUCTION::SEC;
    decoder[0x58] = INSTRUCTION::CLI;
    decoder[0x78] = INSTRUCTION::SEI;
    decoder[0xD8] = INSTRUCTION::CLD;
    decoder[0xF8] = INSTRUCTION::SED;
    decoder[0xB8] = INSTRUCTION::CLV;

    // Other
    decoder[0xEA] = INSTRUCTION::NOP;
}

void CPU::PrintRegisters() {
    
    cout << "A: " << (int) A << endl;
    
    cout << "X: " << (int) X << endl;
    
    cout << "Y: " << (int) Y << endl;
    
    cout << "PC: " << (int) PC << endl;
    
    cout << "S: " << (int) S << endl;
    
    cout << "P: " << (int) P << endl;

}

ADDRESS CPU::ADDR_ACC() {
    
    return 0;

}

ADDRESS CPU::ADDR_ABS() {

    BYTE low_byte = read(PC);
    
    PC++;

    BYTE high_byte = read(PC);

    PC++;

    ADDRESS address = (high_byte << 8) | low_byte;

    return address;

}

ADDRESS CPU::ADDR_ABS_X() {
    
    BYTE low_byte = read(PC);

    PC++;

    BYTE high_byte = read(PC);

    PC++;

    ADDRESS address = (high_byte << 8) | low_byte;

    address += X;

    return address;

}

ADDRESS CPU::ADDR_ABS_Y() {
    
    BYTE low_byte = read(PC);

    PC++;

    BYTE high_byte = read(PC);

    PC++;

    ADDRESS address = (high_byte << 8) | low_byte;

    address += Y;

    return address;

}

ADDRESS CPU::ADDR_IMM() {

    ADDRESS address = PC;

    PC++;
    
    return address;

}

ADDRESS CPU::ADDR_IMP() {

    return 0;

}

ADDRESS CPU::ADDR_IND() {

    BYTE low_byte = read(PC);

    PC++;

    BYTE high_byte = read(PC);

    PC++;

    ADDRESS pointer = (high_byte << 8) | low_byte;

    BYTE addr_low_byte = read(pointer);

    /* Note: this pointer increment implements a bug in the
       original MOS 6502 in which if the pointer update reaches the
       end of the page, there is a wrap-around back to the
       beginning of the same page */

    pointer = (pointer & 0b1111111100000000) + ((pointer + 1) & 0b0000000011111111);

    BYTE addr_high_byte = read(pointer);

    ADDRESS address = (addr_high_byte << 8) | addr_low_byte;

    return address;

}

ADDRESS CPU::ADDR_IND_X() {
    
    BYTE low_byte = read(PC);

    PC++;

    BYTE high_byte = 0x00;

    ADDRESS pointer = ((high_byte << 8) | low_byte) + X;

    SET_ZERO_PAGE(pointer);

    BYTE addr_low_byte = read(pointer);

    pointer++;

    SET_ZERO_PAGE(pointer);

    BYTE addr_high_byte = read(pointer);

    ADDRESS address = (addr_high_byte << 8) | addr_low_byte;

    return address;

}

ADDRESS CPU::ADDR_IND_Y() {

    BYTE low_byte = read(PC);

    PC++;

    BYTE high_byte = 0x00;

    PC++;

    ADDRESS pointer = (high_byte << 8) | low_byte;

    BYTE addr_low_byte = read(pointer);

    pointer++;
    
    SET_ZERO_PAGE(pointer);

    BYTE addr_high_byte = read(pointer);

    ADDRESS address = ((addr_high_byte << 8) | addr_low_byte) + Y;

    return address;

}

ADDRESS CPU::ADDR_REL() {
    
    BYTE offset = read(PC);
    
    PC++;

    ADDRESS address;

    if (NEGATIVE(offset)) {

        address = (ADDRESS) offset;
        
        SIGN_EXTEND(address);
        
        address += PC;
        
        return address;
    }

    address = (ADDRESS) offset + PC;

    return address;

}

ADDRESS CPU::ADDR_ZERO() {

    BYTE low_byte = read(PC);
    
    PC++;

    BYTE high_byte = 0x00;

    ADDRESS address = (high_byte << 8) | low_byte;

    SET_ZERO_PAGE(address);

    return address;

}

ADDRESS CPU::ADDR_ZERO_X() {

    BYTE low_byte = read(PC);
    
    PC++;

    BYTE high_byte = 0x00;

    ADDRESS address = (high_byte << 8) | low_byte;

    address += X;

    SET_ZERO_PAGE(address);

    return address;

}

ADDRESS CPU::ADDR_ZERO_Y() {

    BYTE low_byte = read(PC);
    
    PC++;

    BYTE high_byte = 0x00;

    ADDRESS address = (high_byte << 8) | low_byte;

    address += Y;

    SET_ZERO_PAGE(address);

    return address;

}

void CPU::OP_LDA(BYTE opcode) {
    
    ADDRESS address; 

    switch (opcode) {
        case (0xA9):
            address = ADDR_IMM();
            break;
        case (0xA5):
            address = ADDR_ZERO();
            break;
        case (0xB5):
            address = ADDR_ZERO_X();
            break;
        case (0xAD):
            address = ADDR_ABS();
            break;
        case (0xBD):
            address = ADDR_ABS_X();
            break;
        case (0xB9):
            address = ADDR_ABS_Y();
            break;
        case (0xA1):
            address = ADDR_IND_X();
            break;
        case (0xB1):
            address = ADDR_IND_Y();
            break;
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);
    
    A = memory;

    SET_ZERO_FLAG(P, A == 0);
    
    SET_NEGATIVE_FLAG(P, A & 0b10000000);

}

void CPU::OP_STA(BYTE opcode) {

    ADDRESS address; 

    switch (opcode) {
        case (0x85):
            address = ADDR_ZERO();
            break;
        case (0x95):
            address = ADDR_ZERO_X();
            break;
        case (0x8D):
            address = ADDR_ABS();
            break;
        case (0x9D):
            address = ADDR_ABS_X();
            break;
        case (0x99):
            address = ADDR_ABS_Y();
            break;
        case (0x81):
            address = ADDR_IND_X();
            break;
        case (0x91):
            address = ADDR_IND_Y();
            break;
        default:
            address = 0;
            break;
    }

    write(address, A);
    
}

void CPU::OP_LDX(BYTE opcode) {

    ADDRESS address; 

    switch (opcode) {
        case (0xA2):
            address = ADDR_IMM();
            break;
        case (0xA6):
            address = ADDR_ZERO();
            break;
        case (0xB6):
            address = ADDR_ZERO_Y();
            break;
        case (0xAE):
            address = ADDR_ABS();
            break;
        case (0xBE):
            address = ADDR_ABS_Y();
            break;
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);
    
    X = memory;

    SET_ZERO_FLAG(P, X == 0);
    
    SET_NEGATIVE_FLAG(P, X & 0b10000000);

}

void CPU::OP_STX(BYTE opcode) {
    
    ADDRESS address;

    switch (opcode) {
        case (0x86):
            address = ADDR_ZERO();
            break;
        case (0x96):
            address = ADDR_ZERO_Y();
            break;
        case (0x8E):
            address = ADDR_ABS();
            break;
        default:
            address = 0;
            break;
    }

    write(address, X);
    
}


void CPU::OP_LDY(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xA0):
            address = ADDR_IMM();
            break;
        case (0xA4):
            address = ADDR_ZERO();
            break;
        case (0xB4):
            address = ADDR_ZERO_Y();
            break;
        case (0xAC):
            address = ADDR_ABS();
            break;
        case (0xBC):
            address = ADDR_ABS_X();
            break;
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);

    Y = memory;

    SET_ZERO_FLAG(P, Y == 0);
    
    SET_NEGATIVE_FLAG(P, Y & 0b10000000);

}

void CPU::OP_STY(BYTE opcode) {
    
    ADDRESS address; 

    switch (opcode) {
        case (0x84):
            address = ADDR_ZERO();
            break;
        case (0x94):
            address = ADDR_ZERO_X();
            break;
        case (0x8C):
            address = ADDR_ABS();
            break;
        default:
            address = 0;
            break;
    }

    write(address, Y);

}

void CPU::OP_TAX(BYTE opcode) {

    ADDRESS address; 

    switch (opcode) {
        case (0xAA):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    X = A;

    SET_ZERO_FLAG(P, X == 0);

    SET_NEGATIVE_FLAG(P, X & 0b10000000);

}
    
void CPU::CPU::OP_TXA(BYTE opcode) {
    
    ADDRESS address; 
        
    switch (opcode) {
        case (0x8A):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    A = X;

    SET_ZERO_FLAG(P, A == 0);

    SET_NEGATIVE_FLAG(P, A & 0b10000000);

}

void CPU::OP_TAY(BYTE opcode) {
    
    ADDRESS address; 

    switch (opcode) {
        case (0xA8):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    Y = A;

    SET_ZERO_FLAG(P, Y == 0);
    
    SET_NEGATIVE_FLAG(P, Y & 0b10000000);
    
}

void CPU::OP_TYA(BYTE opcode) {
    
    ADDRESS address; 
        
    switch (opcode) {
        case (0x98):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    A = Y;

    SET_ZERO_FLAG(P, A == 0);

    SET_NEGATIVE_FLAG(P, A & 0b10000000);

}

void CPU::OP_AND(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x29):
            address = ADDR_IMM();
            break;
        case (0x25):
            address = ADDR_ZERO();
            break;
        case (0x35):
            address = ADDR_ZERO_Y();
            break;
        case (0x2D):
            address = ADDR_ABS();
            break;
        case (0x3D):
            address = ADDR_ABS_X();
            break;
        case (0x39):
            address = ADDR_ABS_Y();
        case (0x21):
            address = ADDR_IND_X();
        case (0x31):
            address = ADDR_IND_Y();
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);

    A = A & memory;

    SET_ZERO_FLAG(P, A == 0);
    
    SET_NEGATIVE_FLAG(P, A & 0b10000000);

}

void CPU::OP_ORA(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x09):
            address = ADDR_IMM();
            break;
        case (0x05):
            address = ADDR_ZERO();
            break;
        case (0x15):
            address = ADDR_ZERO_Y();
            break;
        case (0x0D):
            address = ADDR_ABS();
            break;
        case (0x1D):
            address = ADDR_ABS_X();
            break;
        case (0x19):
            address = ADDR_ABS_Y();
        case (0x01):
            address = ADDR_IND_X();
        case (0x11):
            address = ADDR_IND_Y();
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);

    A = A | memory;

    SET_ZERO_FLAG(P, A == 0);
    
    SET_NEGATIVE_FLAG(P, A & 0b10000000);

}

void CPU::OP_EOR(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x49):
            address = ADDR_IMM();
            break;
        case (0x45):
            address = ADDR_ZERO();
            break;
        case (0x55):
            address = ADDR_ZERO_Y();
            break;
        case (0x4D):
            address = ADDR_ABS();
            break;
        case (0x5D):
            address = ADDR_ABS_X();
            break;
        case (0x59):
            address = ADDR_ABS_Y();
        case (0x41):
            address = ADDR_IND_X();
        case (0x51):
            address = ADDR_IND_Y();
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);

    A = A ^ memory;

    SET_ZERO_FLAG(P, A == 0);

    SET_NEGATIVE_FLAG(P, A & 0b10000000);

}

void CPU::OP_BIT(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x24):
            address = ADDR_ZERO();
            break;
        case (0x2C):
            address = ADDR_ABS();
            break;
        default:
            address = 0;
    }

    BYTE memory = read(address);

    BYTE result = A & memory;

    SET_ZERO_FLAG(P, result == 0);

    SET_OVERFLOW_FLAG(P, memory & 0b01000000);

    SET_NEGATIVE_FLAG(P, memory & 0b10000000);
    
}

void CPU::OP_ADC(BYTE opcode) {
    
    ADDRESS address;

    switch (opcode) {
        case (0x69):
            address = ADDR_IMM();
            break;
        case (0x65):
            address = ADDR_ZERO();
            break;
        case (0x75):
            address = ADDR_ZERO_Y();
            break;
        case (0x6D):
            address = ADDR_ABS();
            break;
        case (0x7D):
            address = ADDR_ABS_X();
            break;
        case (0x79):
            address = ADDR_ABS_Y();
        case (0x61):
            address = ADDR_IND_X();
        case (0x71):
            address = ADDR_IND_Y();
        default:
            address = 0;
            break;
    }
    
    BYTE memory = read(address);
    
    SIGNAL carry = P & 0b00000001;

    unsigned int result = A + memory + carry;

    SIGNAL decimal = P & 0b00001000;

    if (decimal) {
        
        unsigned int low_nibble = (A & 0b1111) + (memory & 0b1111) + (carry & 0b1111);

        // Adjustments needed in case there is carry not accounted for in typical hex addition
        
        result += low_nibble > DECIMAL_LARGEST_DIGIT ? NIBBLE_ADJUST : NO_NIBBLE_ADJUST;

        result += result > BCD_BYTE_MAX ? BCD_BYTE_ADJUST : BCD_BYTE_NO_ADJUST;

        SET_CARRY_FLAG(P, result > BCD_BYTE_MAX);

        SET_ZERO_FLAG(P, (result & 0b11111111) == 0);

        SET_OVERFLOW_FLAG(P, (result ^ A) & (result ^ memory) & 0x80);

        SET_NEGATIVE_FLAG(P, result & 0b10000000);
        
        A = result & 0b11111111;
        
    } else {

        SET_CARRY_FLAG(P, result > BYTE_MAX);

        SET_ZERO_FLAG(P, (result & 0b11111111) == 0);

        SET_OVERFLOW_FLAG(P, (result ^ A) & (result ^ memory) & 0x80);

        SET_NEGATIVE_FLAG(P, result & 0b10000000);

        A = result & 0b11111111;

    }

}

void CPU::OP_SBC(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xE9):
            address = ADDR_IMM();
            break;
        case (0xE5):
            address = ADDR_ZERO();
            break;
        case (0xF5):
            address = ADDR_ZERO_Y();
            break;
        case (0xED):
            address = ADDR_ABS();
            break;
        case (0xFD):
            address = ADDR_ABS_X();
            break;
        case (0xF9):
            address = ADDR_ABS_Y();
        case (0xE1):
            address = ADDR_IND_X();
        case (0xF1):
            address = ADDR_IND_Y();
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);
    
    SIGNAL carry = P & 0b00000001;

    unsigned int result = A + ~memory + carry;

    SIGNAL decimal = P & 0b00001000;

    if (decimal) {

        unsigned int low_nibble = (A & 0b1111) +  (~memory & 0b1111) + (carry & 0b1111);

        result -= (!(low_nibble & 0b10000000)) ? NIBBLE_ADJUST : NO_NIBBLE_ADJUST;

        result -= (result > BCD_BYTE_MAX) ? BCD_BYTE_ADJUST : BCD_BYTE_NO_ADJUST;

        SET_CARRY_FLAG(P, (result & 0b100000000) != 0);

        SET_ZERO_FLAG(P, (result & 0b11111111) == 0);
        
        SET_OVERFLOW_FLAG(P, (result ^ A) & (result ^ (~memory)) & 0x80);

        SET_NEGATIVE_FLAG(P, result & 0b10000000);

        A = result & 0b11111111;

    } else {

        SET_CARRY_FLAG(P, (result & 0b100000000) != 0);

        SET_ZERO_FLAG(P, (result & 0b11111111) == 0);
        
        SET_OVERFLOW_FLAG(P, (result ^ A) & (result ^ (~memory)) & 0x80);

        SET_NEGATIVE_FLAG(P, result & 0b10000000);

        A = result & 0b11111111;

    }

}

void CPU::OP_INC(BYTE opcode) {
    
    ADDRESS address;

    switch (opcode) {
        case (0xE6):
            address = ADDR_ZERO();
            break;
        case (0xF6):
            address = ADDR_ZERO_X();
            break;
        case (0xEE):
            address = ADDR_ABS();
            break;
        case (0xFE):
            address = ADDR_ABS_X();
            break;
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);

    memory = memory + 1;

    write(address, memory);

    SET_ZERO_FLAG(P, memory == 0);
    SET_NEGATIVE_FLAG(P, memory & 0b10000000);

}

void CPU::OP_DEC(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xC6):
            address = ADDR_ZERO();
            break;
        case (0xD6):
            address = ADDR_ZERO_X();
            break;
        case (0xCE):
            address = ADDR_ABS();
            break;
        case (0xDE):
            address = ADDR_ABS_X();
            break;
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);

    memory = memory - 1;

    write(address, memory);

    SET_ZERO_FLAG(P, memory == 0);
    SET_NEGATIVE_FLAG(P, memory & 0b10000000);

}

void CPU::OP_INX(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xE8):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    X = X + 1;

    SET_ZERO_FLAG(P, X == 0);

    SET_NEGATIVE_FLAG(P, X & 0b10000000);

}

void CPU::OP_DEX(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xCA):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    X = X - 1;

    SET_ZERO_FLAG(P, X == 0);

    SET_NEGATIVE_FLAG(P, X & 0b10000000);

}

void CPU::OP_INY(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xC8):  
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    Y = Y + 1;

    SET_ZERO_FLAG(P, Y == 0);

    SET_NEGATIVE_FLAG(P, Y & 0b10000000);

}

void CPU::OP_DEY(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x88):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    Y = Y - 1;

    SET_ZERO_FLAG(P, Y == 0);

    SET_NEGATIVE_FLAG(P, Y & 0b10000000);

}

void CPU::OP_ASL(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x0A):
            address = ADDR_ACC();
            break;
        case (0x06):
            address = ADDR_ZERO();
            break;
        case (0x16):
            address = ADDR_ZERO_X();
            break;
        case (0x0E):
            address = ADDR_ABS();
            break;
        case (0x1E):
            address = ADDR_ABS_X();
            break;
        default:
            address = 0;
            break;
    }

    if (opcode == 0x0A) { // Accumulator

        SIGNAL carry = A & 0b10000000;
        
        SET_CARRY_FLAG(P, carry);

        A = A << 1;
        
        SET_ZERO_FLAG(P, A == 0);
        
        SET_NEGATIVE_FLAG(P, A & 0b10000000);
        
    } else { // Memory

        BYTE memory = read(address);

        SIGNAL carry = memory & 0b10000000;
        
        SET_CARRY_FLAG(P, carry);

        memory = memory << 1;

        SET_ZERO_FLAG(P, memory == 0);
        
        SET_NEGATIVE_FLAG(P, memory & 0b10000000);
        
        write(address, memory);

    }

}

void CPU::OP_LSR(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x4A):
            address = ADDR_ACC();
            break;
        case (0x46):
            address = ADDR_ZERO();
            break;
        case (0x56):
            address = ADDR_ZERO_X();
            break;
        case (0x4E):
            address = ADDR_ABS();
            break;
        case (0x5E):
            address = ADDR_ABS_X();
            break;
        default:
            address = 0;
            break;
    }

    if (opcode == 0x4A) { // Accumulator
    
        SIGNAL carry = A & 0b00000001;
        
        SET_CARRY_FLAG(P, carry);

        A = A >> 1;

        SET_ZERO_FLAG(P, A == 0);

        SET_NEGATIVE_FLAG(P, A & 0b10000000);

    } else { // Memory

        BYTE memory = read(address);

        SIGNAL carry = memory & 0b00000001;

        SET_CARRY_FLAG(P, carry);

        memory = memory >> 1;

        SET_ZERO_FLAG(P, memory == 0);

        SET_NEGATIVE_FLAG(P, memory & 0b10000000);

        write(address, memory);

    }

}

void CPU::OP_ROL(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x2A):
            address = ADDR_ACC();
            break;
        case (0x26):
            address = ADDR_ZERO();
            break;
        case (0x36):
            address = ADDR_ZERO_X();
            break;
        case (0x2E):
            address = ADDR_ABS();
            break;
        case (0x3E):
            address = ADDR_ABS_X();
            break;
        default:
            address = 0;
            break;
    }

    if (opcode == 0x2A) { // Accumulator
        
        SIGNAL old_carry = P & 0b00000001;

        SIGNAL carry = A & 0b10000000;

        SET_CARRY_FLAG(P, carry);

        A = A << 1;

        SET_CARRY_FLAG(A, old_carry);

        SET_ZERO_FLAG(P, A == 0);

        SET_NEGATIVE_FLAG(P, A & 0b10000000);
        

    } else { // Memory

        BYTE memory = read(address);

        SIGNAL old_carry = P & 0b00000001;

        SIGNAL carry = memory & 0b10000000;

        SET_CARRY_FLAG(P, carry);

        memory = memory << 1;

        SET_CARRY_FLAG(memory, old_carry);

        SET_ZERO_FLAG(P, memory == 0);

        SET_NEGATIVE_FLAG(P, memory & 0b10000000);

        write(address, memory);

    }

}

void CPU::OP_ROR(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x6A):
            address = ADDR_ACC();
            break;
        case (0x66):
            address = ADDR_ZERO();
            break;
        case (0x76):
            address = ADDR_ZERO_X();
            break;
        case (0x6E):
            address = ADDR_ABS();
            break;
        case (0x7E):
            address = ADDR_ABS_X();
            break;
        default:
            address = 0;
            break;
    }

    if (opcode == 0x6A) { // Accumulator

        SIGNAL old_carry = P & 0b10000000;

        SIGNAL carry = A & 0b00000001;

        SET_CARRY_FLAG(P, carry);

        A = A >> 1;

        SET_NEGATIVE_FLAG(A, old_carry);
        
        SET_ZERO_FLAG(P, A == 0);

        SET_NEGATIVE_FLAG(P, A & 0b10000000);

    } else { // Memory
        
        BYTE memory = read(address);

        SIGNAL old_carry = P & 0b10000000;

        SIGNAL carry = memory & 0b00000001;

        SET_CARRY_FLAG(P, carry);

        memory = memory >> 1;

        SET_NEGATIVE_FLAG(A, old_carry);
        
        SET_ZERO_FLAG(P, memory == 0);

        SET_NEGATIVE_FLAG(P, memory & 0b10000000);

        write(address, memory);

    }

}

void CPU::OP_CMP(BYTE opcode) {
    
    ADDRESS address;

    switch (opcode) {
        case (0xC9):
            address = ADDR_IMM();
        case (0xC5):
            address = ADDR_ZERO();
            break;
        case (0xD5):
            address = ADDR_ZERO_X();
            break;
        case (0xCD):
            address = ADDR_ABS();
            break;
        case (0xDD):
            address = ADDR_ABS_X();
            break;
        case (0xD9):
            address = ADDR_ABS_Y();
            break;
        case (0xC1):
            address = ADDR_IND_X();
            break;
        case (0xD1):
            address = ADDR_IND_Y();
            break;
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);

    BYTE result = A - memory;

    SET_CARRY_FLAG(P, A >= memory);
    
    SET_ZERO_FLAG(P, A == memory);
    
    SET_NEGATIVE_FLAG(P, result & 0b10000000);

}

void CPU::OP_CPX(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xE0):
            address = ADDR_IMM();
        case (0xE4):
            address = ADDR_ZERO();
            break;
        case (0xEC):
            address = ADDR_ABS();
            break;
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);

    BYTE result = X - memory;

    SET_CARRY_FLAG(P, X >= memory);
    
    SET_ZERO_FLAG(P, X == memory);
    
    SET_NEGATIVE_FLAG(P, result & 0b10000000);

}

void CPU::OP_CPY(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xC0):
            address = ADDR_IMM();
        case (0xC4):
            address = ADDR_ZERO();
            break;
        case (0xCC):
            address = ADDR_ABS();
            break;
        default:
            address = 0;
            break;
    }

    BYTE memory = read(address);

    BYTE result = Y - memory;

    SET_CARRY_FLAG(P, Y >= memory);
    
    SET_ZERO_FLAG(P, Y == memory);
    
    SET_NEGATIVE_FLAG(P, result & 0b10000000);

}

void CPU::OP_BCC(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x90):
            address = ADDR_REL();
        default:
            address = 0;
            break;
    }

    SIGNAL carry = P & 0b00000001;

    if (!carry) {
        
        /* Since in relative addressing, we already retrieve offset.
         we simply need to set PC to be address */
        
        PC = address; 
    }

}

void CPU::OP_BCS(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x90):
            address = ADDR_REL();
        default:
            address = 0;
            break;
    }

    SIGNAL carry = P & 0b00000001;

    if (carry) {
        
        /* Since in relative addressing, we already retrieve offset.
         we simply need to set PC to be address */
        
        PC = address; 
    }

}

void CPU::OP_BEQ(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xF0):
            address = ADDR_REL();
        default:
            address = 0;
            break;
    }

    SIGNAL zero = P & 0b00000010;

    if (zero) {
        
        /* Since in relative addressing, we already retrieve offset.
         we simply need to set PC to be address */
        
        PC = address; 
    }

}

void CPU::OP_BNE(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xD0):
            address = ADDR_REL();
        default:
            address = 0;
            break;
    }

    SIGNAL zero = P & 0b00000010;

    if (!zero) {
        
        /* Since in relative addressing, we already retrieve offset.
         we simply need to set PC to be address */
        
        PC = address; 
    }

}

void CPU::OP_BPL(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x10):
            address = ADDR_REL();
        default:
            address = 0;
            break;
    }


    SIGNAL negative = P & 0b10000000;

    if (!negative) {
        
        /* Since in relative addressing, we already retrieve offset.
         we simply need to set PC to be address */
        
        PC = address; 
    }

}

void CPU::OP_BMI(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x30):
            address = ADDR_REL();
        default:
            address = 0;
            break;
    }

    SIGNAL negative = P & 0b10000000;

    if (negative) {
        
        /* Since in relative addressing, we already retrieve offset.
         we simply need to set PC to be address */
        
        PC = address; 
    }

}

void CPU::OP_BVC(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x50):
            address = ADDR_REL();
        default:
            address = 0;
            break;
    }

    SIGNAL overflow = P & 0b01000000;

    if (!overflow) {
        
        /* Since in relative addressing, we already retrieve offset.
         we simply need to set PC to be address */
        
        PC = address; 
    }

}

void CPU::OP_BVS(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x70):
            address = ADDR_REL();
        default:
            address = 0;
            break;
    }

    SIGNAL overflow = P & 0b01000000;

    if (!overflow) {
        
        /* Since in relative addressing, we already retrieve offset.
         we simply need to set PC to be address */
        
        PC = address; 
    }

}

void CPU::OP_JMP(BYTE opcode) {
    
    ADDRESS address;

    switch (opcode) {
        case (0x4C):
            address = ADDR_ABS();
            break;
        case (0x6C):
            address = ADDR_IND();
            break;
        default:
            address = 0;
            break;
    }

    PC = address;

}

void CPU::OP_JSR(BYTE opcode) {
    
    ADDRESS address;

    switch (opcode) {
        case (0x20):
            address = ADDR_ABS();
            break;
        default:
            address = 0;
            break;
    }

    ADDRESS return_address = PC - 1;

    BYTE ra_high_byte = return_address >> 8;

    BYTE ra_low_byte = return_address & 0b11111111;

    write(0x0100 + S, ra_high_byte);
    
    S = S - 1;

    write(0x0100 + S, ra_low_byte);

    S = S - 1;

    PC = address;

}

void CPU::OP_RTS(BYTE opcode) {
    
    ADDRESS address;

    switch (opcode) {
        case (0x60):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    ADDRESS return_address = 0;

    BYTE ra_low_byte = read(0x0100 + S);

    S = S + 1;

    return_address |= ra_low_byte;

    BYTE ra_high_byte = read(0x0100 + S);

    S = S + 1;

    return_address |= (ra_high_byte << 8);

    PC = return_address + 1;

}

void CPU::OP_BRK(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x00):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    PC++; // skip the next byte

    BYTE pc_high_byte = PC >> 8;

    BYTE pc_low_byte = PC & 0b11111111;

    write(0x0100 + S, pc_high_byte);
    
    S = S - 1;

    write(0x0100 + S, pc_low_byte);

    S = S - 1;

    BYTE flags = P | 0b00110000;

    write(0x0100 + S, flags);

    S = S - 1;

    pc_low_byte = read(IRQ_VECTOR_LOW);
    
    pc_high_byte = read(IRQ_VECTOR_HIGH);

    PC = (pc_high_byte << 8) | pc_low_byte;

    SET_INTERRUPT_FLAG(P, 1);

}

void CPU::OP_RTI(BYTE opcode) {
    
    ADDRESS address;

    switch (opcode) {
        case (0x40):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    BYTE flags = read(0x0100 + S);

    S = S + 1;

    BYTE pc_low_byte = read(0x0100 + S);

    S = S + 1;

    BYTE pc_high_byte = read(0x0100 + S);

    S = S + 1;

    PC = (pc_high_byte << 8) | pc_low_byte;

    SET_CARRY_FLAG(P, flags & 0b00000001);

    SET_ZERO_FLAG(P, flags & 0b00000010);

    SET_INTERRUPT_FLAG(P, flags & 0b00000100);

    SET_DECIMAL_FLAG(P, flags & 0b00001000);

    SET_OVERFLOW_FLAG(P, flags & 0b01000000);

    SET_NEGATIVE_FLAG(P, flags & 0b10000000);

}

void CPU::IRQ() {

    SIGNAL interrupt_disable = P & 0b00000100;

    if (!interrupt_disable) {

        BYTE pc_high_byte = PC >> 8;

        BYTE pc_low_byte = PC & 0b11111111;
        
        write(0x0100 + S, pc_high_byte);

        S = S - 1;

        write(0x0100 + S, pc_low_byte);

        S = S - 1;

        BYTE flags = P | 0b00100000;

        write(0x0100 + S, flags);

        SET_INTERRUPT_FLAG(P, 1);

        pc_low_byte = read(IRQ_VECTOR_LOW);
        
        pc_high_byte = read(IRQ_VECTOR_HIGH);

        PC = (pc_high_byte << 8) | pc_low_byte;

    }

}

void CPU::NMI() {

        BYTE pc_high_byte = PC >> 8;

        BYTE pc_low_byte = PC & 0b11111111;
        
        write(0x0100 + S, pc_high_byte);

        S = S - 1;

        write(0x0100 + S, pc_low_byte);

        S = S - 1;

        BYTE flags = P | 0b00100000;

        write(0x0100 + S, flags);

        SET_INTERRUPT_FLAG(P, 1);

        pc_low_byte = read(NMI_VECTOR_LOW);
        
        pc_high_byte = read(NMI_VECTOR_HIGH);

        PC = (pc_high_byte << 8) | pc_low_byte;

}

void CPU::OP_PHA(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x48):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    write(0x0100 + S, A);

    S = S - 1;

}

void CPU::OP_PHP(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x08):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    BYTE status = P;

    status = status | 0b00110000;

    write(0x0100 + S, status);

    S = S - 1;

}

void CPU::OP_PLA(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x68):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    S = S + 1;

    A = read(0x0100 + S);

    SET_ZERO_FLAG(P, A == 0);
    
    SET_NEGATIVE_FLAG(P, A & 0b10000000);

}

void CPU::OP_PLP(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x28):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    S = S + 1;

    BYTE memory = read(0x0100 + S);

    SET_CARRY_FLAG(P, memory & 0b00000001);
    
    SET_ZERO_FLAG(P, memory & 0b00000010);
    
    SET_INTERRUPT_FLAG(P, memory & 0b00000100);
    
    SET_DECIMAL_FLAG(P, memory & 0b00001000);
    
    SET_OVERFLOW_FLAG(P, memory & 0b01000000);

    SET_NEGATIVE_FLAG(P, memory & 0b10000000);

}

void CPU::OP_TXS(BYTE opcode) {
    
    ADDRESS address;

    switch (opcode) {
        case (0x9A):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    S = X;

}

void CPU::OP_TSX(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xBA):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    X = S;

    SET_ZERO_FLAG(P, X == 0);
    
    SET_NEGATIVE_FLAG(P, X & 0b10000000);

}

void CPU::OP_CLC(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x18):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    SET_CARRY_FLAG(P, 0);

}

void CPU::OP_SEC(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x38):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    SET_CARRY_FLAG(P, 1);

}

void CPU::OP_CLI(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x58):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    SET_INTERRUPT_FLAG(P, 0);

}

void CPU::OP_SEI(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0x78):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    SET_INTERRUPT_FLAG(P, 1);

}

void CPU::OP_CLD(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xD8):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    SET_DECIMAL_FLAG(P, 0);

}

void CPU::OP_SED(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xF8):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    SET_DECIMAL_FLAG(P, 1);

}

void CPU::OP_CLV(BYTE opcode) {

    ADDRESS address;

    switch (opcode) {
        case (0xB8):
            address = ADDR_IMP();
            break;
        default:
            address = 0;
            break;
    }

    SET_OVERFLOW_FLAG(P, 0);

}

void CPU::OP_NOP(BYTE opcode) {
    
    ADDRESS address;

    switch(opcode) {
        case (0xEA):
            address = ADDR_IMP();
        default:
            address = 0;
            break;
    }

}

BYTE CPU::getA() {

    return A;

}

BYTE CPU::getX() {

    return X;

}

BYTE CPU::getY() {

    return Y;

}

ADDRESS CPU::getPC() {

    return PC;
}

BYTE CPU::getP() {

    return P;

}

BYTE CPU::getS() {
    
    return S;

}