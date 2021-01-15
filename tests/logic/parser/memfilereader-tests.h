#ifndef MEMFILEREADER_TESTS_H
#define MEMFILEREADER_TESTS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>

#include "parser/memfilereader.h"

using namespace testing;

TEST(ParserTests, MemFileReader)
{
    std::vector<std::string> v;
    v.push_back(" # ClearAllMemory");
    v.push_back(" # ClearAllRegisters");
    v.push_back(" #setMemory  20=A2 ");
    v.push_back(" #setMemory  21=1F ");
    v.push_back(" #setMemory  22=35 ");
    v.push_back(" #setMemory  23=E0 ");
    v.push_back(" #setMemory  FF=20 ");

    MemFileReader fr;
    FlispProgram prog = fr.parse(v);
    EXPECT_TRUE(prog.mem[0x20] == 0xA2);
    EXPECT_TRUE(prog.mem[0x21] == 0x1F);
    EXPECT_TRUE(prog.mem[0x22] == 0x35);
    EXPECT_TRUE(prog.mem[0x23] == 0xE0);
    EXPECT_TRUE(prog.mem[0xFF] == 0x20);
    EXPECT_TRUE(prog.reg.A == 0x00);
    EXPECT_TRUE(prog.reg.X == 0x00);
    EXPECT_TRUE(prog.reg.Y == 0x00);
    EXPECT_TRUE(prog.reg.SP == 0x00);
    EXPECT_TRUE(prog.reg.PC == 0x00);
    EXPECT_TRUE(prog.reg.CC == 0x00);
}

#endif // MEMFILEREADER_TESTS_H
