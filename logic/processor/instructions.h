#ifndef L_INSTRUCTIONS_H
#define L_INSTRUCTIONS_H

#include "processorstate.h"

class Instructions
{
public:
	static void execute(uint8_t opcode, ProcessorState* state);
};

void ADCA(uint8_t opcode, ProcessorState* state);
void ADDA(uint8_t opcode, ProcessorState* state);
void ANDA(uint8_t opcode, ProcessorState* state);
void ANDCC(uint8_t opcode, ProcessorState* state);

void ASL(uint8_t opcode, ProcessorState* state);
void ASR(uint8_t opcode, ProcessorState* state);

void BCC(uint8_t opcode, ProcessorState* state);
void BCS(uint8_t opcode, ProcessorState* state);
void BEQ(uint8_t opcode, ProcessorState* state);
void BGE(uint8_t opcode, ProcessorState* state);
void BGT(uint8_t opcode, ProcessorState* state);

void BHI(uint8_t opcode, ProcessorState* state);
void BHS(uint8_t opcode, ProcessorState* state);

void BITA(uint8_t opcode, ProcessorState* state);

void BLE(uint8_t opcode, ProcessorState* state);
void BLO(uint8_t opcode, ProcessorState* state);
void BLS(uint8_t opcode, ProcessorState* state);
void BLT(uint8_t opcode, ProcessorState* state);
void BMI(uint8_t opcode, ProcessorState* state);
void BNE(uint8_t opcode, ProcessorState* state);
void BPL(uint8_t opcode, ProcessorState* state);
void BRA(uint8_t opcode, ProcessorState* state);
void BSR(uint8_t opcode, ProcessorState* state);
void BVC(uint8_t opcode, ProcessorState* state);
void BVS(uint8_t opcode, ProcessorState* state);

void CLR(uint8_t opcode, ProcessorState* state);

void CMPA(uint8_t opcode, ProcessorState* state);
void CMPX(uint8_t opcode, ProcessorState* state);
void CMPY(uint8_t opcode, ProcessorState* state);
void CMPSP(uint8_t opcode, ProcessorState* state);

void COM(uint8_t opcode, ProcessorState* state);
void DEC(uint8_t opcode, ProcessorState* state);
void EOR(uint8_t opcode, ProcessorState* state);

void EXG(uint8_t opcode, ProcessorState* state);

void INC(uint8_t opcode, ProcessorState* state);

void JMP(uint8_t opcode, ProcessorState* state);
void JSR(uint8_t opcode, ProcessorState* state);

void LDA(uint8_t opcode, ProcessorState* state);
void LDX(uint8_t opcode, ProcessorState* state);
void LDY(uint8_t opcode, ProcessorState* state);
void LDSP(uint8_t opcode, ProcessorState* state);

void LEAX(uint8_t opcode, ProcessorState* state);
void LEAY(uint8_t opcode, ProcessorState* state);
void LEASP(uint8_t opcode, ProcessorState* state);

void LSL(uint8_t opcode, ProcessorState* state);
void LSR(uint8_t opcode, ProcessorState* state);

void NEG(uint8_t opcode, ProcessorState* state);
void NOP(uint8_t opcode, ProcessorState* state);

void ORA(uint8_t opcode, ProcessorState* state);
void ORCC(uint8_t opcode, ProcessorState* state);

void PSH(uint8_t opcode, ProcessorState* state);
void PUL(uint8_t opcode, ProcessorState* state);

void ROL(uint8_t opcode, ProcessorState* state);
void ROR(uint8_t opcode, ProcessorState* state);

void RTS(uint8_t opcode, ProcessorState* state);
void RTI(uint8_t opcode, ProcessorState* state);

void SBCA(uint8_t opcode, ProcessorState* state);
void SUBA(uint8_t opcode, ProcessorState* state);

void STA(uint8_t opcode, ProcessorState* state);
void STX(uint8_t opcode, ProcessorState* state);
void STY(uint8_t opcode, ProcessorState* state);
void STSP(uint8_t opcode, ProcessorState* state);

void TFR(uint8_t opcode, ProcessorState* state);
void TST(uint8_t opcode, ProcessorState* state);

void HALT(uint8_t opcode, ProcessorState* state);

#endif // L_INSTRUCTIONS_H
