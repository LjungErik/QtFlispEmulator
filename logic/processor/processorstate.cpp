#include "processorstate.h"
#include <cstring>

bool same7thBit(uint8_t val1, uint8_t val2) 
{
    return (~(val1 ^ val2) & 0x80) != 0;
}

ProcessorState::ProcessorState():
    m_memory(),
    m_registers()
{
}

ProcessorState::~ProcessorState()
{
}

uint8_t ProcessorState::readNextPC()
{
    uint8_t pc = m_registers.PC();
    m_registers.PC(pc + 1);
    return m_memory.readMemory(pc);
}

uint8_t ProcessorState::add(uint8_t val1, uint8_t val2, uint8_t carry, uint8_t& flags)
{
    uint16_t sum = val1 + (val2 + carry);

    uint8_t N = (0x80 & sum) >> 4;
    uint8_t Z = 0x00;
    if ((sum & 0xFF) == 0)
    {
        Z = 0x04;
    }
    uint8_t V = 0;
    if (same7thBit(val1, val2) && !same7thBit(sum & 0xFF, val1))
    {
        V = 0x02;
    }
    uint8_t C = (sum & 0x100) >> 8;


    flags = N | Z | V | C;

    return sum & 0xFF;
}

uint8_t ProcessorState::logicalAnd(uint8_t val1, uint8_t val2, uint8_t& flags)
{
    uint8_t result = val1 & val2;

    uint8_t N = (0x80 & result) >> 4;
    uint8_t Z = 0x00;
    if ((result & 0xFF) == 0)
    {
        Z = 0x04;
    }

    flags = N | Z;

    return result;
}

uint8_t ProcessorState::leftLogicalShift(uint8_t val, uint8_t& flags)
{
    uint16_t result = val << 1;

    uint8_t N = (0x80 & result) >> 4;
    uint8_t Z = 0x00;
    if ((result & 0xFF) == 0)
    {
        Z = 0x04;
    }

    uint8_t V = 0x00;
    if ((result & 0x80) != (val & 0x80))
    {
        V = 0x02;
    }

    uint8_t C = (result & 0x100) >> 8;
    flags = N | Z | V | C;
    return result & 0xFF;
}

uint8_t ProcessorState::rightLogicalShift(uint8_t val, uint8_t& flags)
{
    uint16_t result = (val >> 1) | (val & 0x80);

    uint8_t N = (0x80 & result) >> 4;
    uint8_t Z = 0x00;
    if ((result & 0xFF) == 0) {
        Z = 0x04;
    }

    uint8_t C = (val & 0x01);
    flags = N | Z | C;
    return result & 0xFF;
}

uint8_t ProcessorState::leftRotateLogicalShift(uint8_t val, uint8_t&flags)
{
    uint8_t result = leftLogicalShift(val, flags);
    result = result | (flags & 0x01);
    flags &= 0xFB;
    if (result == 0) 
    {
        flags |= 0x04;
    }

    return result;
}

uint8_t ProcessorState::rightRotateLogicalShift(uint8_t val, uint8_t&flags)
{
    uint8_t result = rightLogicalShift(val, flags);
    result = result | ((flags & 0x01)<<7);
    flags &= 0xFB;
    if (result == 0) 
    {
        flags |= 0x04;
    }

    return result;
}

uint8_t ProcessorState::sub(uint8_t val1, uint8_t val2, uint8_t carry, uint8_t& flags)
{
    uint16_t result = val1 - val2 - carry;

    uint8_t N = (0x80 & result) >> 4;
    uint8_t Z = 0x00;
    if ((result & 0xFF) == 0) {
        Z = 0x04;
    }

    uint8_t V = 0;
    if (same7thBit(val1, (-val2)) && !same7thBit(result & 0xFF, val1))
    {
        V = 0x02;
    }
    uint8_t C = (result & 0x100) >> 8;

    flags = N | Z | V | C;

    return result & 0xFF;
}

uint8_t ProcessorState::complement(uint8_t val, uint8_t& flags) 
{
    uint16_t result = ~(val);

    uint8_t N = (0x80 & result) >> 4;
    uint8_t Z = 0x00;
    if ((result & 0xFF) == 0)
    {
        Z = 0x04;
    }

    flags = N | Z;

    return result & 0xFF;
}

uint8_t ProcessorState::logicalXOR(uint8_t val1, uint8_t val2, uint8_t& flags)
{
    uint8_t result = val1 ^ val2;

    uint8_t N = (0x80 & result) >> 4;
    uint8_t Z = 0x00;
    if ((result & 0xFF) == 0)
    {
        Z = 0x04;
    }

    flags = N | Z;

    return result & 0xFF;
}

uint8_t ProcessorState::logicalOR(uint8_t val1, uint8_t val2, uint8_t& flags)
{
    uint8_t result = val1 | val2;

    uint8_t N = (0x80 & result) >> 4;
    uint8_t Z = 0x00;
    if ((result & 0xFF) == 0)
    {
        Z = 0x04;
    }

    flags = N | Z;

    return result & 0xFF;
}

uint8_t ProcessorState::negate(uint8_t val, uint8_t& flags) 
{
    uint8_t result = -val;

    uint8_t N = (0x80 & result) >> 4;
    uint8_t Z = 0x00;
    if ((result & 0xFF) == 0)
    {
        Z = 0x04;
    }

    uint8_t V = 0x00;
    if ((result & 0x80) != 0 && ((-val) & 0x80) == 0)
    {
        V = 0x02;
    }

    uint8_t C = 0x00;
    if (val != 0)
    {
        C = 0x01;
    }

    flags = N | Z | V | C;
    return result;
}

uint8_t ProcessorState::readFlags(uint8_t val)
{
    uint8_t N = (0x80 & val) >> 4;
    uint8_t Z = 0x00;
    if ((val & 0xFF) == 0)
    {
        Z = 0x04;
    }

    return N | Z;
}

uint8_t ProcessorState::readMemory(uint8_t address)
{
    return m_memory.readMemory(address);
}

void ProcessorState::writeMemory(uint8_t address, uint8_t data)
{
    m_memory.writeMemory(address, data);
}