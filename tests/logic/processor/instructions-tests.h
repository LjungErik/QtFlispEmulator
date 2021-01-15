#ifndef INSTRUCTIONSTESTS_H
#define INSTRUCTIONSTESTS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "processor/instructions.h"

using namespace testing;

TEST(InstructionsTests, ADCA_Test)
{
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0x01);
    reg->A(0xFF);
    reg->CC(0x00);
    //act
    ADCA(0x95, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x05);
}


TEST(InstructionsTests, ADDA_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0x01);
    reg->A(0xFF);
    reg->CC(0x00);
    //act
    ADDA(0x96, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00) << "Failed Expected A: " << int(reg->A()) << " != " << 0x00;
    EXPECT_TRUE(reg->CC() == 0x05) << "Failed Expected CC: " << int(reg->CC()) << " != " << 0x05;
}

TEST(InstructionsTests, ANDA_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0x00);
    reg->A(0xFF);
    reg->CC(0x02);
    //act
    ANDA(0x99, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00) << "Failed Expected A: " << int(reg->A()) << " != " << 0x00;
    EXPECT_TRUE(reg->CC() == 0x04) << "Failed Expected CC: " << int(reg->CC()) << " != " << 0x04;
}

TEST(InstructionsTests, ANDCC_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0x04);
    reg->A(0xFF);
    reg->CC(0x06);
    //act
    ANDCC(0x01, state);
    //assert
    EXPECT_TRUE(reg->A() == 0xFF) << "Failed Expected A: " << int(reg->A()) << " != " << 0xFF;
    EXPECT_TRUE(reg->CC() == 0x04) << "Failed Expected CC: " << int(reg->CC()) << " != " << 0x04;
}

TEST(InstructionsTests, ASL_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->A(0x80);
    reg->CC(0x00);
    //act
    ASL(0x0B, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00) << "Failed Expected A: " << int(reg->A()) << " != " << 0x00;
    EXPECT_TRUE(reg->CC() == 0x07) << "Failed Expected CC: " << int(reg->CC()) << " != " << 0x05;
}

TEST(InstructionsTests, ASR_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->A(0x01);
    reg->CC(0x00);
    //act
    ASR(0x0F, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00) << "Failed Expected A: " << int(reg->A()) << " != " << 0x00;
    EXPECT_TRUE(reg->CC() == 0x05) << "Failed Expected CC: " << int(reg->CC()) << " != " << 0x05;
}

TEST(InstructionsTests, BCC_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x00);
    //act
    BCC(0x29, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x01);
    //act
    BCC(0x29, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BCS_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x01);
    //act
    BCS(0x28, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x00);
    //act
    BCS(0x28, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BEQ_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x04);
    //act
    BEQ(0x24, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x00);
    //act
    BEQ(0x24, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BGE_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x00);
    //act
    BGE(0x2D, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x08);
    //act
    BGE(0x2D, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BGT_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x00);
    //act
    BGT(0x2C, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x04);
    //act
    BGT(0x2C, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BHI_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x00);
    //act
    BHI(0x2A, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x01);
    //act
    BHI(0x2A, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BITA_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0xFF);
    reg->A(0xFF);
    reg->CC(0x03);
    //act
    BITA(0x98, state);
    //assert
    EXPECT_TRUE(reg->CC() == 0x09);

    reg->A(0x00);
    reg->CC(0x01);
    //act
    BITA(0x98, state);
    //assert
    EXPECT_TRUE(reg->CC() == 0x05);
}

TEST(InstructionsTests, BLE_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x08);
    //act
    BLE(0x2E, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x01);
    //act
    BLE(0x2E, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BLS_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x04);
    //act
    BLS(0x2B, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x00);
    //act
    BLS(0x2B, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BLT_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x02);
    //act
    BLT(0x2F, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x00);
    //act
    BLT(0x2F, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BMI_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x08);
    //act
    BMI(0x22, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x04);
    //act
    BMI(0x22, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BNE_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x02);
    //act
    BNE(0x25, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x04);
    //act
    BNE(0x25, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BPL_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x04);
    //act
    BPL(0x23, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x08);
    //act
    BPL(0x23, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BRA_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x04);
    //act
    BRA(0x21, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);
}

TEST(InstructionsTests, BSR_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x04);
    //act
    BSR(0x20, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);
    EXPECT_TRUE(state->readMemory(reg->SP()) == 0x02);
}

TEST(InstructionsTests, BVC_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x04);
    //act
    BVC(0x27, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x02);
    //act
    BVC(0x27, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, BVS_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x01, 0x05);
    reg->PC(0x01);
    reg->CC(0x02);
    //act
    BVS(0x26, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x07);

    reg->PC(0x01);
    reg->CC(0x04);
    //act
    BVS(0x26, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x02);
}

TEST(InstructionsTests, CLR_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->A(0xF1);
    reg->CC(0x02);
    //act
    CLR(0x05, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x04);
}

TEST(InstructionsTests, CMPA_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0xF1);
    reg->A(0xF1);
    reg->CC(0x00);
    //act
    CMPA(0x97, state);
    //assert
    EXPECT_TRUE(reg->A() == 0xF1);
    EXPECT_TRUE(reg->CC() == 0x04);

    state->writeMemory(reg->PC(), 0x02);
    reg->A(0x09);
    reg->CC(0x02);
    //act
    CMPA(0x97, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x09);
    EXPECT_TRUE(reg->CC() == 0x00);
}

TEST(InstructionsTests, CMPX_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0xF1);
    reg->X(0xF1);
    reg->CC(0x00);
    //act
    CMPX(0x97, state);
    //assert
    EXPECT_TRUE(reg->X() == 0xF1);
    EXPECT_TRUE(reg->CC() == 0x04);

    state->writeMemory(reg->PC(), 0x02);
    reg->X(0x09);
    reg->CC(0x00);
    //act
    CMPX(0x97, state);
    //assert
    EXPECT_TRUE(reg->X() == 0x09);
    EXPECT_TRUE(reg->CC() == 0x00);
}

TEST(InstructionsTests, CMPY_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0xF1);
    reg->Y(0xF1);
    reg->CC(0x00);
    //act
    CMPY(0x97, state);
    //assert
    EXPECT_TRUE(reg->Y() == 0xF1);
    EXPECT_TRUE(reg->CC() == 0x04);

    state->writeMemory(reg->PC(), 0x00);
    reg->Y(0x09);
    reg->CC(0x02);
    //act
    CMPY(0x97, state);
    //assert
    EXPECT_TRUE(reg->Y() == 0x09);
    EXPECT_TRUE(reg->CC() == 0x00);
}

TEST(InstructionsTests, CMPSP_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0xF1);
    reg->SP(0xF1);
    reg->CC(0x00);
    //act
    CMPSP(0x97, state);
    //assert
    EXPECT_TRUE(reg->SP() == 0xF1);
    EXPECT_TRUE(reg->CC() == 0x04);

    state->writeMemory(reg->PC(), 0x02);
    reg->SP(0x09);
    reg->CC(0x02);
    //act
    CMPSP(0x97, state);
    //assert
    EXPECT_TRUE(reg->SP() == 0x09);
    EXPECT_TRUE(reg->CC() == 0x00);
}

TEST(InstructionsTests, COM_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->A(0x7F);
    reg->CC(0x00);

    //act
    COM(0x0A, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x80);
    EXPECT_TRUE(reg->CC() == 0x08);

    reg->A(0xFF);
    reg->CC(0x03);
    //act
    COM(0x0A, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x05);
}

TEST(InstructionsTests, DEC_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->A(0x00);
    reg->CC(0x00);

    //act
    DEC(0x08, state);
    //assert
    EXPECT_TRUE(reg->A() == 0xFF);
    EXPECT_TRUE(reg->CC() == 0x08);

    reg->A(0x80);
    reg->CC(0x05);
    //act
    DEC(0x08, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x7F);
    EXPECT_TRUE(reg->CC() == 0x03);

    reg->A(0x01);
    reg->CC(0x03);
    //act
    DEC(0x08, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x05);
}

TEST(InstructionsTests, EOR_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0xFF);
    reg->A(0x00);
    reg->CC(0x02);

    //act
    EOR(0x9B, state);
    //assert
    EXPECT_TRUE(reg->A() == 0xFF);
    EXPECT_TRUE(reg->CC() == 0x08);

    state->writeMemory(reg->PC(), 0x00);
    reg->A(0x00);
    reg->CC(0x03);
    //act
    EOR(0x9B, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x05);
}

TEST(InstructionsTests, EXG_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->A(0x04);
    reg->CC(0x03);

    //act
    EXG(0x9F, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x03);
    EXPECT_TRUE(reg->CC() == 0x04);

    reg->X(0x04);
    reg->Y(0x03);

    //act
    EXG(0xAF, state);
    //assert
    EXPECT_TRUE(reg->X() == 0x03);
    EXPECT_TRUE(reg->Y() == 0x04);

    reg->X(0x04);
    reg->SP(0x33);

    //act
    EXG(0xBF, state);
    //assert
    EXPECT_TRUE(reg->X() == 0x33);
    EXPECT_TRUE(reg->SP() == 0x04);

    reg->Y(0x14);
    reg->SP(0x33);

    //act
    EXG(0xCF, state);
    //assert
    EXPECT_TRUE(reg->Y() == 0x33);
    EXPECT_TRUE(reg->SP() == 0x14);
}

TEST(InstructionsTests, INC_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->A(0x7F);
    reg->CC(0x00);

    //act
    INC(0x07, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x80);
    EXPECT_TRUE(reg->CC() == 0x0A);

    reg->A(0xFF);
    reg->CC(0x03);
    //act
    INC(0x07, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x05);

    reg->A(0x01);
    reg->CC(0x02);
    //act
    INC(0x07, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x02);
    EXPECT_TRUE(reg->CC() == 0x00);
}

TEST(InstructionsTests, JMP_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0x55);

    //act
    JMP(0x33, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x55);
}

TEST(InstructionsTests, JSR_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->PC(0x44);
    state->writeMemory(reg->PC(), 0x55);
    state->writeMemory(0x45, 0x78);

    //act
    JSR(0x34, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x55);
    EXPECT_TRUE(state->readMemory(0x45) == 0x78);
}

TEST(InstructionsTests, LDA_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0xF5);
    reg->CC(0x03);

    //act
    LDA(0xF0, state);
    //assert
    EXPECT_TRUE(reg->A() == 0xF5);
    EXPECT_TRUE(reg->CC() == 0x09);

    state->writeMemory(reg->PC(), 0x00);
    reg->CC(0x03);

    //act
    LDA(0xF0, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x05);
}

TEST(InstructionsTests, LDX_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0xF5);
    reg->CC(0x03);

    //act
    LDX(0x90, state);
    //assert
    EXPECT_TRUE(reg->X() == 0xF5);
    EXPECT_TRUE(reg->CC() == 0x09);

    state->writeMemory(reg->PC(), 0x00);
    reg->CC(0x03);

    //act
    LDX(0x90, state);
    //assert
    EXPECT_TRUE(reg->X() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x05);
}

TEST(InstructionsTests, LDY_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0xF5);
    reg->CC(0x03);

    //act
    LDY(0x91, state);
    //assert
    EXPECT_TRUE(reg->Y() == 0xF5);
    EXPECT_TRUE(reg->CC() == 0x09);

    state->writeMemory(reg->PC(), 0x00);
    reg->CC(0x03);

    //act
    LDY(0x91, state);
    //assert
    EXPECT_TRUE(reg->Y() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x05);
}

TEST(InstructionsTests, LDSP_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0xF5);
    reg->CC(0x03);

    //act
    LDSP(0x90, state);
    //assert
    EXPECT_TRUE(reg->SP() == 0xF5);
    EXPECT_TRUE(reg->CC() == 0x09);

    state->writeMemory(reg->PC(), 0x00);
    reg->CC(0x03);

    //act
    LDSP(0x90, state);
    //assert
    EXPECT_TRUE(reg->SP() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x05);
}

TEST(InstructionsTests, LEAX_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0x05);
    reg->X(0x02);

    //act
    LEAX(0xCC, state);
    //assert
    EXPECT_TRUE(reg->X() == 0x07);

    state->writeMemory(reg->PC(), 0x05);
    reg->SP(0x02);

    //act
    LEAX(0xDC, state);
    //assert
    EXPECT_TRUE(reg->X() == 0x07);
}

TEST(InstructionsTests, LEAY_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0x05);
    reg->Y(0x02);

    //act
    LEAY(0xCD, state);
    //assert
    EXPECT_TRUE(reg->Y() == 0x07);

    state->writeMemory(reg->PC(), 0x05);
    reg->SP(0x02);

    //act
    LEAY(0xDD, state);
    //assert
    EXPECT_TRUE(reg->Y() == 0x07);
}

TEST(InstructionsTests, LEASP_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0x05);
    reg->SP(0x02);

    //act
    LEASP(0xBE, state);
    //assert
    EXPECT_TRUE(reg->SP() == 0x07);

    state->writeMemory(reg->PC(), 0x06);
    reg->X(0x02);

    //act
    LEASP(0xCE, state);
    //assert
    EXPECT_TRUE(reg->SP() == 0x08);

    state->writeMemory(reg->PC(), 0x07);
    reg->Y(0x02);

    //act
    LEASP(0xDE, state);
    //assert
    EXPECT_TRUE(reg->SP() == 0x09);
}

TEST(InstructionsTests, LSL_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->A(0x80);
    reg->CC(0x00);
    //act
    LSL(0x0B, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x07);
}

TEST(InstructionsTests, LSR_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->A(0x81);
    reg->CC(0x00);
    //act
    LSR(0x0C, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x40);
    EXPECT_TRUE(reg->CC() == 0x01);
}

TEST(InstructionsTests, NEG_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->A(0x01);
    reg->CC(0x00);
    //act
    NEG(0x06, state);
    //assert
    EXPECT_TRUE(reg->A() == 0xFF);
    EXPECT_TRUE(reg->CC() == 0x09);
}

TEST(InstructionsTests, ORA_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0x87);
    reg->A(0x71);
    reg->CC(0x01);
    //act
    ORA(0x9A, state);
    //assert
    EXPECT_TRUE(reg->A() == 0xF7);
    EXPECT_TRUE(reg->CC() == 0x09);

    state->writeMemory(reg->PC(), 0x00);
    reg->A(0x00);
    reg->CC(0x03);
    //act
    ORA(0x9A, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x05);
}

TEST(InstructionsTests, ORCC_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->PC(), 0x05);
    reg->CC(0x01);
    //act
    ORCC(0x02, state);
    //assert
    EXPECT_TRUE(reg->CC() == 0x05);

    state->writeMemory(reg->PC(), 0x08);
    reg->CC(0x03);
    //act
    ORCC(0x02, state);
    //assert
    EXPECT_TRUE(reg->CC() == 0x0B);
}

TEST(InstructionsTests, PSH_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(reg->SP(), 0x05);
    state->writeMemory(0x04, 0x55);
    reg->A(0x01);
    //act
    PSH(0x10, state);
    //assert
    EXPECT_TRUE(state->readMemory(reg->SP()) == 0x01);

    state->writeMemory(reg->SP(), 0x05);
    state->writeMemory(0x04, 0x55);
    reg->X(0x01);
    //act
    PSH(0x11, state);
    //assert
    EXPECT_TRUE(state->readMemory(reg->SP()) == 0x01);

    state->writeMemory(reg->SP(), 0x05);
    state->writeMemory(0x04, 0x55);
    reg->Y(0x01);
    //act
    PSH(0x12, state);
    //assert
    EXPECT_TRUE(state->readMemory(reg->SP()) == 0x01);

    state->writeMemory(reg->SP(), 0x05);
    state->writeMemory(0x04, 0x55);
    reg->CC(0x01);
    //act
    PSH(0x13, state);
    //assert
    EXPECT_TRUE(state->readMemory(reg->SP()) == 0x01);
}

TEST(InstructionsTests, PUL_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->SP(0x44);
    state->writeMemory(reg->SP(), 0x05);
    reg->A(0x01);
    //act
    PUL(0x14, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x05);
    EXPECT_TRUE(reg->SP() == 0x45);

    reg->SP(0x44);
    state->writeMemory(reg->SP(), 0x05);
    reg->X(0x01);
    //act
    PUL(0x15, state);
    //assert
    EXPECT_TRUE(reg->X() == 0x05);
    EXPECT_TRUE(reg->SP() == 0x45);

    reg->SP(0x44);
    state->writeMemory(reg->SP(), 0x05);
    reg->Y(0x01);
    //act
    PUL(0x16, state);
    //assert
    EXPECT_TRUE(reg->Y() == 0x05);
    EXPECT_TRUE(reg->SP() == 0x45);

    reg->SP(0x44);
    state->writeMemory(reg->SP(), 0x05);
    reg->CC(0x01);
    //act
    PUL(0x17, state);
    //assert
    EXPECT_TRUE(reg->CC() == 0x05);
    EXPECT_TRUE(reg->SP() == 0x45);
}

TEST(InstructionsTests, ROL_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->A(0xFF);
    //act
    ROL(0x0D, state);
    //assert
    EXPECT_TRUE(reg->A() == 0xFF);
    EXPECT_TRUE(reg->CC() == 0x09);

    reg->A(0x00);
    //act
    ROL(0x0D, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x04);

    reg->A(0x80);
    //act
    ROL(0x0D, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x01);
    EXPECT_TRUE(reg->CC() == 0x03);
}

TEST(InstructionsTests, ROR_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->CC(0x00);
    reg->A(0xFF);
    //act
    ROR(0x0D, state);
    //assert
    EXPECT_TRUE(reg->A() == 0xFF);
    EXPECT_TRUE(reg->CC() == 0x01);

    reg->CC(0x00);
    reg->A(0x00);
    //act
    ROR(0x0D, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x00);
    EXPECT_TRUE(reg->CC() == 0x04);

    reg->CC(0x01);
    reg->A(0x01);
    //act
    ROR(0x0D, state);
    //assert
    EXPECT_TRUE(reg->A() == 0x80);
    EXPECT_TRUE(reg->CC() == 0x09);
}

TEST(InstructionsTests, RTS_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->SP(0x09);
    state->writeMemory(reg->SP(), 0x44);
    //act
    RTS(0x43, state);
    //assert
    EXPECT_TRUE(reg->PC() == 0x44);
    EXPECT_TRUE(reg->SP() == 0x0A);
}

TEST(InstructionsTests, RTI_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->SP(0x09);
    state->writeMemory(reg->SP(), 0x44);
    state->writeMemory(reg->SP()+1, 0x45);
    state->writeMemory(reg->SP()+2, 0x46);
    state->writeMemory(reg->SP()+3, 0x47);
    state->writeMemory(reg->SP()+4, 0x48);
    //act
    RTI(0x44, state);
    //assert
    EXPECT_TRUE(reg->CC() == 0x44);
    EXPECT_TRUE(reg->A() == 0x45);
    EXPECT_TRUE(reg->X() == 0x46);
    EXPECT_TRUE(reg->Y() == 0x47);
    EXPECT_TRUE(reg->PC() == 0x48);
    EXPECT_TRUE(reg->SP() == 0x0E);
}

#endif // INSTRUCTIONSTESTS_H
