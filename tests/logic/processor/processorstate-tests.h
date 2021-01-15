#ifndef PROCESSORSTATETESTS_H
#define PROCESSORSTATETESTS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "processor/processorstate.h"

TEST(ProcessorState_Tests, readNextPC_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    reg->PC(0x45);
    state->writeMemory(0x45, 0x90);

    uint8_t result = state->readNextPC();

    EXPECT_TRUE(result == 0x90);
    EXPECT_TRUE(reg->PC() == 0x46);
}

TEST(ProcessorState_Tests, add_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();

    uint8_t flags = 0;
    uint8_t result = state->add(0xFF, 0x01, 0x00, flags);

    EXPECT_TRUE(result == 0x00);
    EXPECT_TRUE(flags == 0x05);

    flags = 0x00;
    result = state->add(0x70, 0x70, 0x00, flags);

    EXPECT_TRUE(result == 0xE0);
    EXPECT_TRUE(flags == 0x0A);
}

TEST(ProcessorState_Tests, logicalAnd_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();

    uint8_t flags = 0;
    uint8_t result = state->logicalAnd(0xFE, 0x01, flags);

    EXPECT_TRUE(result == 0x00);
    EXPECT_TRUE(flags == 0x04);

    flags = 0x00;
    result = state->logicalAnd(0x80, 0x80, flags);

    EXPECT_TRUE(result == 0x80);
    EXPECT_TRUE(flags == 0x08);
}

TEST(ProcessorState_Tests, leftLogicalShift_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();

    uint8_t flags = 0;
    uint8_t result = state->leftLogicalShift(0xF0, flags);

    EXPECT_TRUE(result == 0xE0);
    EXPECT_TRUE(flags == 0x09);

    flags = 0x00;
    result = state->leftLogicalShift(0x00, flags);

    EXPECT_TRUE(result == 0x00);
    EXPECT_TRUE(flags == 0x04);
}

TEST(ProcessorState_Tests, rightLogicalShift_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();

    uint8_t flags = 0;
    uint8_t result = state->rightLogicalShift(0x01, flags);

    EXPECT_TRUE(result == 0x00);
    EXPECT_TRUE(flags == 0x05);

    flags = 0;
    result = state->rightLogicalShift(0x80, flags);

    EXPECT_TRUE(result == 0xC0);
    EXPECT_TRUE(flags == 0x08);
}

TEST(ProcessorState_Tests, sub_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();

    uint8_t flags = 0;
    uint8_t result = state->sub(0x01, 0x01, 0x00, flags);

    EXPECT_TRUE(result == 0x00);
    EXPECT_TRUE(flags == 0x04);

    flags = 0;
    result = state->sub(0x03, 0x04, 0x00, flags);

    EXPECT_TRUE(result == 0xFF);
    EXPECT_TRUE(flags == 0x09);

    flags = 0;
    result = state->sub(0x80, 0x01, 0x00, flags);

    EXPECT_TRUE(result == 0x7F);
    EXPECT_TRUE(flags == 0x02);

    flags = 0;
    result = state->sub(0x70, 0x00, 0x01, flags);

    EXPECT_TRUE(result == 0x6F);
    EXPECT_TRUE(flags == 0x00);
}

TEST(ProcessorState_Tests, complement_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();

    uint8_t flags = 0x00;
    uint8_t result = state->complement(0x01, flags);

    EXPECT_TRUE(result == 0xFE);
    EXPECT_TRUE(flags == 0x08);

    flags = 0x00;
    result = state->complement(0xFF, flags);

    EXPECT_TRUE(result == 0x00);
    EXPECT_TRUE(flags == 0x04);

    flags = 0x01;
    result = state->complement(0x80, flags);

    EXPECT_TRUE(result == 0x7F);
    EXPECT_TRUE(flags == 0x00);
}

TEST(ProcessorState_Tests, logicalXOR_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();

    uint8_t flags = 0x00;
    uint8_t result = state->logicalXOR(0x01, 0x80, flags);

    EXPECT_TRUE(result == 0x81);
    EXPECT_TRUE(flags == 0x08);

    flags = 0x00;
    result = state->logicalXOR(0xFF, 0xFF, flags);

    EXPECT_TRUE(result == 0x00);
    EXPECT_TRUE(flags == 0x04);

    flags = 0x01;
    result = state->logicalXOR(0x70, 0x60, flags);

    EXPECT_TRUE(result == 0x10);
    EXPECT_TRUE(flags == 0x00);
}

TEST(ProcessorState_Tests, logicalOR_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();

    uint8_t flags = 0x00;
    uint8_t result = state->logicalOR(0x80, 0x82, flags);

    EXPECT_TRUE(result == 0x82);
    EXPECT_TRUE(flags == 0x08);

    flags = 0x00;
    result = state->logicalOR(0x00, 0x00, flags);

    EXPECT_TRUE(result == 0x00);
    EXPECT_TRUE(flags == 0x04);

    flags = 0x01;
    result = state->logicalOR(0x70, 0x60, flags);

    EXPECT_TRUE(result == 0x70);
    EXPECT_TRUE(flags == 0x00);
}

TEST(ProcessorState_Tests, negate_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();

    uint8_t flags = 0x00;
    uint8_t result = state->negate(0x01, flags);

    EXPECT_TRUE(result == 0xFF);
    EXPECT_TRUE(flags == 0x09);

    flags = 0x00;
    result = state->negate(0x00, flags);

    EXPECT_TRUE(result == 0x00);
    EXPECT_TRUE(flags == 0x04);
}

TEST(ProcessorState_Tests, readFlags_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();

    uint8_t flags = 0x00;
    uint8_t result = state->readFlags(0x00);

    EXPECT_TRUE(result == 0x04);

    flags = 0x00;
    result = state->readFlags(0xFF);

    EXPECT_TRUE(result == 0x08);
}

TEST(ProcessorState_Tests, readAndWriteMemory_Test) {
    //arrange
    ProcessorState* state = new ProcessorState();
    Registers* reg = state->getRegisters();
    state->writeMemory(0x66, 0x60);

    uint8_t result = state->readMemory(0x66);

    EXPECT_TRUE(result == 0x60);
}

#endif // PROCESSORSTATETESTS_H
