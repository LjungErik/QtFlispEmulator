#include "processorstate.h"
#include "instructions.h"
#include "registers.h"

uint8_t readData(uint8_t code, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = state->readNextPC();

    switch (code)
    {
    case 0x10:
        data = state->readMemory(data);
        break;
    case 0x20: {
        uint8_t sp = reg->SP();
        data = state->readMemory(data + sp);
        break;
    }
    case 0x30: {
        uint8_t x = reg->X();
        data = state->readMemory(data + x);
        break;
    }
    case 0x40: {
        uint8_t y = reg->Y();
        data = state->readMemory(data + y);
        break;
    }
    }

    return data;
}

uint8_t readAddress(uint8_t code, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    int16_t address = 0;

    switch (code)
    {
        case 0x30: {
            address = state->readNextPC();
            break;
        }
        case 0x40: {
            uint8_t n = state->readNextPC();
            uint8_t sp = reg->SP();
            address = n + sp;
            break;
        }
        case 0x50: {
            uint8_t n = state->readNextPC();
            uint8_t x = reg->X();
            address = n + x;
            break;
        }
        case 0x60: {
            uint8_t y = reg->X();
            uint8_t a = reg->A();
            address = a + y;
            break;
        }
        case 0x70: {
            uint8_t n = state->readNextPC();
            uint8_t y = reg->Y();
            address = n + y;
            break;
        }
        case 0x80: {
            uint8_t y = reg->Y();
            uint8_t a = reg->A();
            address = a + y;
            break;
        }
    }

    return address;
}

#define MAX_INSTRUCTIONS 256

typedef void (*Inst) (uint8_t opcode, ProcessorState* state);

const Inst INSTRUCTIONS[MAX_INSTRUCTIONS] = {
    NOP,  ANDCC, ORCC, NULL, NULL, CLR,  NEG,  INC,  DEC,  TST,  COM, LSL, LSR,  ROL,  ROR,   ASR, 
    PSH,  PSH,   PSH,  PSH,  PUL,  PUL,  PUL,  PUL,  TFR,  TFR,  TFR, TFR, TFR,  TFR,  TFR,   TFR,
    BSR,  BRA,   BMI,  BPL,  BEQ,  BNE,  BVS,  BVC,  BCS,  BCC,  BHI, BLS, BGT,  BGE,  BLE,   BLT,
    STX,  STY,   STSP, JMP,  JSR,  CLR,  NEG,  INC,  DEC,  TST,  COM, LSL, LSR,  ROL,  ROR,   ASR,
    STX,  STY,   STSP, RTS,  RTI,  CLR,  NEG,  INC,  DEC,  TST,  COM, LSL, LSR,  ROL,  ROR,   ASR,
    STX,  STY,   STSP, JMP,  JSR,  CLR,  NEG,  INC,  DEC,  TST,  COM, LSL, LSR,  ROL,  ROR,   ASR,
    STX,  STY,   STSP, JMP,  JSR,  CLR,  NEG,  INC,  DEC,  TST,  COM, LSL, LSR,  ROL,  ROR,   ASR,
    STX,  STY,   STSP, JMP,  JSR,  CLR,  NEG,  INC,  DEC,  TST,  COM, LSL, LSR,  ROL,  ROR,   ASR,
    STX,  STY,   STSP, JMP,  JSR,  CLR,  NEG,  INC,  DEC,  TST,  COM, LSL, LSR,  ROL,  ROR,   ASR,
    LDX,  LDY,   LDSP, SBCA, SUBA, ADCA, ADDA, CMPA, BITA, ANDA, ORA, EOR, CMPX, CMPY, CMPSP, EXG,
    LDX,  LDY,   LDSP, SBCA, SUBA, ADCA, ADDA, CMPA, BITA, ANDA, ORA, EOR, CMPX, CMPY, CMPSP, EXG,
    LDX,  LDY,   LDSP, SBCA, SUBA, ADCA, ADDA, CMPA, BITA, ANDA, ORA, EOR, CMPX, CMPY, CMPSP, EXG,
    LDX,  LDY,   LDSP, SBCA, SUBA, ADCA, ADDA, CMPA, BITA, ANDA, ORA, EOR, CMPX, CMPY, CMPSP, EXG,
    LDX,  LDY,   LDSP, SBCA, SUBA, ADCA, ADDA, CMPA, BITA, ANDA, ORA, EOR, CMPX, CMPY, CMPSP, NULL,
    NULL, STA,   STA,  STA,  STA,  STA,  STA,  STA,  STA,  STA,  STA, STA, STA,  STA,  STA,   NULL,
    LDA,  LDA,   LDA,  LDA,  LDA,  LDA,  LDA,  LDA,  LDA,  LDA,  LDA, LDA, LDA,  LDA,  LDA,   HALT
};

void Instructions::execute(uint8_t opcode, ProcessorState* state)
{
    Inst f = INSTRUCTIONS[opcode];
    if (f != NULL) {
        f(opcode, state);
    }
}

void NOP(uint8_t opcode, ProcessorState* state)
{}

void ADCA(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t carry = C_BIT & reg->CC();
    uint8_t data = readData((opcode - 0x95), state);

    uint8_t a = reg->A();
    uint8_t flags = 0;

    uint8_t sum = state->add(a, data, carry, flags);
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);

    reg->CC(flags);
    reg->A(sum);
}

void ADDA(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode - 0x96), state);

    uint8_t a = reg->A();
    uint8_t flags = 0;

    uint8_t result = state->add(a, data, 0x00, flags);
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);

    reg->CC(flags);
    reg->A(result);
}

void ANDA(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode - 0x99), state);

    uint8_t a = reg->A();
    uint8_t flags = 0;

    uint8_t result = state->logicalAnd(a, data, flags);
    flags = (reg->CC() & 0xF0) | (flags & 0x0E);

    reg->CC(flags);
    reg->A(result);
}

void ANDCC(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = state->readNextPC();

    uint8_t CC = reg->CC();

    reg->CC(CC & data);
}

void ASL(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x0B), state);

    uint8_t flags = 0;

    if (opcode == 0x0B) {
        uint8_t data = reg->A();
        data = state->leftLogicalShift(data, flags);
        reg->A(data);
    }
    else {
        uint8_t data = state->readMemory(address);
        data = state->leftLogicalShift(data, flags);
        state->writeMemory(address, data);
    }

    flags = (reg->CC() & 0xF0) | (flags & 0x0F);
    reg->CC(flags);
}

void ASR(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x0F), state);

    uint8_t flags = 0;

    if (opcode == 0x0F) {
        uint8_t data = reg->A();
        data = state->rightLogicalShift(data, flags);
        reg->A(data);
    }
    else {
        uint8_t data = state->readMemory(address);
        data = state->rightLogicalShift(data, flags);
        state->writeMemory(address, data);
    }

    flags = (reg->CC() & 0xF0) | (flags & 0x0F);
    reg->CC(flags);
}

void BCC(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if ((reg->CC() & C_BIT) == 0)
    {
        reg->PC(pc);
    }
}

void BCS(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if ((reg->CC() & C_BIT) != 0)
    {
        reg->PC(pc);
    }
}

void BEQ(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if ((reg->CC() & Z_BIT) != 0)
    {
        reg->PC(pc);
    }
}

void BGE(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t cc = reg->CC();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if (((cc & N_BIT) ^ (cc & V_BIT)) == 0)
    {
        reg->PC(pc);
    }
}

void BGT(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t cc = reg->CC();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if ((((cc & N_BIT) ^ (cc & V_BIT)) + (cc & Z_BIT)) == 0)
    {
        reg->PC(pc);
    }
}

void BHI(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t cc = reg->CC();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if (((cc & C_BIT) + (cc & Z_BIT)) == 0)
    {
        reg->PC(pc);
    }
}

void BHS(uint8_t opcode, ProcessorState* state)
{
    BCC(opcode, state);
}

void BITA(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode - 0x98), state);

    uint8_t a = reg->A();
    uint8_t flags = 0;

    state->logicalAnd(a, data, flags);
    flags = (reg->CC() & 0xF1) | (flags & 0x0E);

    reg->CC(flags);
}

void BLE(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t cc = reg->CC();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if ((((cc & N_BIT) ^ (cc & V_BIT)) + (cc & Z_BIT)) != 0)
    {
        reg->PC(pc);
    }
}

void BLO(uint8_t opcode, ProcessorState* state)
{
    BCS(opcode, state);
}

void BLS(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t cc = reg->CC();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if (((cc & C_BIT) + (cc & Z_BIT)) != 0)
    {
        reg->PC(pc);
    }
}

void BLT(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t cc = reg->CC();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if (((cc & N_BIT) ^ (cc & V_BIT)) != 0)
    {
        reg->PC(pc);
    }
}

void BMI(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t cc = reg->CC();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if ((cc & N_BIT) != 0)
    {
        reg->PC(pc);
    }
}

void BNE(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t cc = reg->CC();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if ((cc & Z_BIT) == 0)
    {
        reg->PC(pc);
    }
}

void BPL(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t cc = reg->CC();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if ((cc & N_BIT) == 0)
    {
        reg->PC(pc);
    }
}

void BRA(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t offset = state->readNextPC();

    uint8_t pc = reg->PC() + offset;

    reg->PC(pc);
}

void BSR(uint8_t opcode, ProcessorState* state)
{
    /* Branch subroutine, */
    Registers* reg = state->getRegisters();
    uint8_t offset = state->readNextPC();
    uint8_t sp = reg->SP() - 1;
    uint8_t pc = reg->PC();

    reg->SP(sp);
    state->writeMemory(sp, pc);
    reg->PC(pc + offset);
}

void BVC(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t cc = reg->CC();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if ((cc & V_BIT) == 0)
    {
        reg->PC(pc);
    }
}

void BVS(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t cc = reg->CC();
    uint8_t offset = state->readNextPC();
    uint8_t pc = reg->PC() + offset;

    if ((cc & V_BIT) != 0)
    {
        reg->PC(pc);
    }
}

void CLR(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();

    uint8_t address = readAddress((opcode - 0x05), state);

    if (opcode == 0x05) {
        reg->A(0);
    }
    else {
        state->writeMemory(address, 0);
    }

    uint8_t flags = 0x04;
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);
    reg->CC(flags);
}

void CMPA(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode - 0x97), state);

    uint8_t a = reg->A();

    uint8_t flags = 0;
    state->sub(a, data, 0x00, flags);
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);

    reg->CC(flags);
}

void CMPX(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode - 0x9C), state);

    uint8_t x = reg->X();

    uint8_t flags = 0;
    state->sub(x, data, 0x00, flags);
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);

    reg->CC(flags);
}

void CMPY(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode - 0x9D), state);

    uint8_t y = reg->Y();

    uint8_t flags = 0;
    state->sub(y, data, 0x00, flags);
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);

    reg->CC(flags);
}

void CMPSP(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode - 0x9E), state);

    uint8_t sp = reg->SP();

    uint8_t flags = 0;
    state->sub(sp, data, 0x00, flags);
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);

    reg->CC(flags);
}

void COM(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x0A), state);

    uint8_t flags = 0;
    
    if (opcode == 0x0A) {
        uint8_t data = reg->A();
        data = state->complement(data, flags);
        reg->A(data);
    } 
    else {
        uint8_t data = state->readMemory(address);
        data = state->complement(data, flags);
        state->writeMemory(address, data);
    }

    flags = (reg->CC() & 0xF1) | (flags & 0x0E);
    reg->CC(flags);
}

void DEC(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x08), state);

    uint8_t flags = 0;

    if (opcode == 0x08) {
        uint8_t data = reg->A();
        data = state->sub(data, 0x01, 0x00, flags);
        reg->A(data);
    }
    else {
        uint8_t data = state->readMemory(address);
        data = state->sub(data, 0x01, 0x00, flags);
        state->writeMemory(address, data);
    }

    flags = (reg->CC() & 0xF1) | (flags & 0x0E);
    reg->CC(flags);
}

void EOR(uint8_t opcode, ProcessorState* state) 
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode - 0x9B), state);

    uint8_t flags = 0;
    uint8_t result = state->logicalXOR(reg->A(), data, flags);

    flags = (reg->CC() & 0xF1) | (flags & 0x0E);
    reg->CC(flags);
    reg->A(result);
}

void EXG(uint8_t opcode, ProcessorState* state) {
    Registers* reg = state->getRegisters();

    switch (opcode)
    {
        case 0x9F: {
            uint8_t temp = reg->A();
            reg->A(reg->CC());
            reg->CC(temp);
            break;
        }
        case 0xAF: {
            uint8_t temp = reg->X();
            reg->X(reg->Y());
            reg->Y(temp);
            break;
        }
        case 0xBF: {
            uint8_t temp = reg->X();
            reg->X(reg->SP());
            reg->SP(temp);
            break;
        }
        case 0xCF: {
            uint8_t temp = reg->Y();
            reg->Y(reg->SP());
            reg->SP(temp);
            break;
        }
    }
}

void INC(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x07), state);

    uint8_t flags = 0;

    if (opcode == 0x07) {
        uint8_t data = reg->A();
        data = state->add(data, 0x01, 0x00, flags);
        reg->A(data);
    }
    else {
        uint8_t data = state->readMemory(address);
        data = state->add(data, 0x01, 0x00, flags);
        state->writeMemory(address, data);
    }

    flags = (reg->CC() & 0xF1) | (flags & 0x0E);
    reg->CC(flags);
}

void JMP(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode-0x03), state);

    reg->PC(address);
}

void JSR(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode-0x04), state);
    
    uint8_t sp = reg->SP()-1;
    reg->SP(sp);
    state->writeMemory(sp, reg->PC());

    reg->PC(address);
}

void LDA(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t A = 0;

    switch (opcode)
    {
        case 0xF0: {
            A = state->readNextPC();
            break;
        }
        case 0xF1: {
            uint8_t address = state->readNextPC();
            A = state->readMemory(address); 
            break;
        }
        case 0xF2: {
            uint8_t n = state->readNextPC();
            A = state->readMemory(n + reg->SP());
            break;
        }
        case 0xF3: {
            uint8_t n = state->readNextPC();
            A = state->readMemory(n + reg->X());
            break;
        }
        case 0xF4: {
            A = state->readMemory(reg->A() + reg->X());
            break;
        }
        case 0xF5: {
            uint8_t address = reg->X();
            A = state->readMemory(address);
            reg->X(address+1);
            break;
        }
        case 0xF6: {
            uint8_t address = reg->X();
            A = state->readMemory(address);
            reg->X(address-1);
            break;
        }
        case 0xF7: {
            uint8_t address = reg->X() + 1;
            A = state->readMemory(address);
            reg->X(address);
            break;
        }
        case 0xF8: {
            uint8_t address = reg->X() - 1;
            A = state->readMemory(address);
            reg->X(address);
            break;
        }
        case 0xF9: {
            uint8_t n = state->readNextPC();
            A = state->readMemory(n + reg->Y());
            break;
        }
        case 0xFA: {
            A = state->readMemory(reg->A() + reg->Y());
            break;
        }
        case 0xFB: {
            uint8_t address = reg->Y();
            A = state->readMemory(address);
            reg->Y(address+1);
            break;
        }
        case 0xFC: {
            uint8_t address = reg->Y();
            A = state->readMemory(address);
            reg->Y(address-1);
            break;
        }
        case 0xFD: {
            uint8_t address = reg->Y() + 1;
            A = state->readMemory(address);
            reg->Y(address);
            break;
        }
        case 0xFE: {
            uint8_t address = reg->Y() - 1;
            A = state->readMemory(address);
            reg->Y(address);
            break;
        }
    }

    uint8_t flags = state->readFlags(A);
    flags = (reg->CC() & 0xF1) | (flags & 0x0E);
    reg->A(A);
    reg->CC(flags);
}

void LDX(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode - 0x90), state);

    uint8_t flags = state->readFlags(data);
    flags = (reg->CC() & 0xF1) | (flags & 0x0E);
    reg->X(data);
    reg->CC(flags);
}

void LDY(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode - 0x91), state);

    uint8_t flags = state->readFlags(data);
    flags = (reg->CC() & 0xF1) | (flags & 0x0E);
    reg->Y(data);
    reg->CC(flags);
}

void LDSP(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode - 0x91), state);

    uint8_t flags = state->readFlags(data);
    flags = (reg->CC() & 0xF1) | (flags & 0x0E);
    reg->SP(data);
    reg->CC(flags);
}

void LEAX(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = state->readNextPC();

    switch (opcode)
    {
    case 0xCC:
        data = reg->X() + data;
        break;
    case 0xDC:
        data = reg->SP() + data;
        break;
    }

    reg->X(data);
}

void LEAY(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = state->readNextPC();

    switch (opcode)
    {
    case 0xCD:
        data = reg->Y() + data;
        break;
    case 0xDD:
        data = reg->SP() + data;
        break;
    }

    reg->Y(data);
}

void LEASP(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = state->readNextPC();

    switch (opcode)
    {
    case 0xBE:
        data = reg->SP() + data;
        break;
    case 0xCE:
        data = reg->X() + data;
        break;
    case 0xDE:
        data = reg->Y() + data;
        break;
    }

    reg->SP(data);
}

void LSL(uint8_t opcode, ProcessorState* state)
{
    return ASL(opcode, state);
}

void LSR(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x0C), state);

    uint8_t flags = 0;

    if (opcode == 0x0C) {
        uint8_t data = reg->A();
        data = state->rightLogicalShift(data, flags);
        data = data & 0x7F;
        reg->A(data);
    }
    else {
        uint8_t data = state->readMemory(address);
        data = state->rightLogicalShift(data, flags);
        data = data & 0x7F;
        state->writeMemory(address, data);
    }

    flags = flags & 0xF7;
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);
    reg->CC(flags);
}

void NEG(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x06), state);

    uint8_t flags = 0;

    if (opcode == 0x06) {
        uint8_t data = reg->A();
        data = state->negate(data, flags);
        reg->A(data);
    }
    else {
        uint8_t data = state->readMemory(address);
        data = state->negate(data, flags);
        state->writeMemory(address, data);
    }

    flags = (reg->CC() & 0xF0) | (flags & 0x0F);
    reg->CC(flags);
}

void ORA(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode-0x9A), state);

    uint8_t flags = 0;
    uint8_t result = state->logicalOR(reg->A(), data, flags);

    flags = (reg->CC() & 0xF1) | (flags & 0x0E);
    reg->CC(flags);
    reg->A(result);
}

void ORCC(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = state->readNextPC();

    reg->CC(reg->CC() | data);
}

void PSH(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t sp = reg->SP() - 1;
    reg->SP(sp);
    switch(opcode) {
        case 0x10:
            state->writeMemory(sp, reg->A());
            break;
        case 0x11:
            state->writeMemory(sp, reg->X());
            break;
        case 0x12:
            state->writeMemory(sp, reg->Y());
            break;
        case 0x13:
            state->writeMemory(sp, reg->CC());
            break;
    }
}

void PUL(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t sp = reg->SP();
    uint8_t data = state->readMemory(sp);

    switch(opcode) {
        case 0x14:
            reg->A(data);
            break;
        case 0x15:
            reg->X(data);
            break;
        case 0x16:
            reg->Y(data);
            break;
        case 0x17:
            reg->CC(data);
            break;
    }

    reg->SP(sp+1);
}

void ROL(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x0D), state);

    uint8_t flags = 0;

    if (opcode == 0x0D) {
        uint8_t data = reg->A();
        data = state->leftRotateLogicalShift(data, flags);
        reg->A(data);
    }
    else {
        uint8_t data = state->readMemory(address);
        data = state->leftRotateLogicalShift(data, flags);
        state->writeMemory(address, data);
    }
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);
    reg->CC(flags);
}

void ROR(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x0E), state);

    uint8_t flags = 0;

    if (opcode == 0x0D) {
        uint8_t data = reg->A();
        data = state->rightRotateLogicalShift(data, flags);
        reg->A(data);
    }
    else {
        uint8_t data = state->readMemory(address);
        data = state->rightRotateLogicalShift(data, flags);
        state->writeMemory(address, data);
    }

    uint8_t cc = reg->CC();
    flags &= 0xF7;
    if ((cc & 0x01) != 0)
    {
        flags |= 0x08;
    }

    flags = (reg->CC() & 0xF0) | (flags & 0x0F);
    reg->CC(flags);
}

void RTS(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t sp = reg->SP();
    uint8_t pc = state->readMemory(sp);

    reg->PC(pc);
    reg->SP(sp + 1);
}

void RTI(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t sp = reg->SP();
    uint8_t data = state->readMemory(sp);
    reg->CC(data);
    sp += 1;
    data = state->readMemory(sp);
    reg->A(data);
    sp += 1;
    data = state->readMemory(sp);
    reg->X(data);
    sp += 1;
    data = state->readMemory(sp);
    reg->Y(data);
    sp += 1;
    data = state->readMemory(sp);
    reg->PC(data);
    reg->SP(sp + 1);
}

void SBCA(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode-0x93), state);
    uint8_t carry = reg->CC() & C_BIT;

    uint8_t flags = 0;
    uint8_t result = state->sub(reg->A(), data, carry, flags);

    reg->A(result);
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);
    reg->CC(flags);
}

void SUBA(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t data = readData((opcode-0x94), state);

    uint8_t flags = 0;
    uint8_t result = state->sub(reg->A(), data, 0x00, flags);

    reg->A(result);
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);
    reg->CC(flags);
}

void STA(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = 0;

    switch (opcode)
    {
        case 0xE1: {
            address = state->readNextPC();
            break;
        }
        case 0xE2: {
            uint8_t n = state->readNextPC();
            address = n + reg->SP();
            break;
        }
        case 0xE3: {
            uint8_t n = state->readNextPC();
            address = n + reg->X();
            break;
        }
        case 0xE4: {
            address = reg->A() + reg->X();
            break;
        }
        case 0xE5: {
            address = reg->X();
            reg->X(address+1);
            break;
        }
        case 0xE6: {
            address = reg->X();
            reg->X(address-1);
            break;
        }
        case 0xE7: {
            address = reg->X() + 1;
            reg->X(address);
            break;
        }
        case 0xE8: {
            address = reg->X() - 1;
            reg->X(address);
            break;
        }
        case 0xE9: {
            uint8_t n = state->readNextPC();
            address = n + reg->Y();
            break;
        }
        case 0xEA: {
            address = reg->A() + reg->Y();
            break;
        }
        case 0xEB: {
            address = reg->Y();
            reg->Y(address+1);
            break;
        }
        case 0xEC: {
            address = reg->Y();
            reg->Y(address-1);
            break;
        }
        case 0xED: {
            address = reg->Y() + 1;
            reg->Y(address);
            break;
        }
        case 0xEE: {
            address = reg->Y() - 1;
            reg->Y(address);
            break;
        }
    }

    state->writeMemory(address, reg->A());
}

void STX(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x00), state);

    state->writeMemory(address, reg->X());
}

void STY(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x01), state);

    state->writeMemory(address, reg->Y());
}

void STSP(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode - 0x02), state);

    state->writeMemory(address, reg->SP());
}

void TFR(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();

    switch (opcode)
    {
    case 0x18:
        reg->CC(reg->A());
        break;
    case 0x19:
        reg->A(reg->CC());
        break;
    case 0x1A:
        reg->Y(reg->X());
        break;
    case 0x1B:
        reg->X(reg->Y());
        break;
    case 0x1C:
        reg->SP(reg->X());
        break;
    case 0x1D:
        reg->X(reg->SP());
        break;
    case 0x1E:
        reg->SP(reg->Y());
        break;
    case 0x1F:
        reg->Y(reg->SP());
        break;
    }
}

void TST(uint8_t opcode, ProcessorState* state)
{
    Registers* reg = state->getRegisters();
    uint8_t address = readAddress((opcode-0x09), state);

    uint8_t flags = 0;
    uint8_t data = 0;

    if (opcode == 0x09){
        data = reg->A();
        
    } else {
        data = state->readMemory(address);
    }

    state->sub(data, 0x00, 0x00, flags);
    flags = (reg->CC() & 0xF0) | (flags & 0x0F);
    reg->CC(flags);
}

void HALT(uint8_t opcode, ProcessorState* state)
{
    state->exit();
}