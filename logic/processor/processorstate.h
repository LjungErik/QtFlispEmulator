#ifndef L_PROCESSORSTATE_H
#define L_PROCESSORSTATE_H

#include "registers.h"
#include "memory.h"

class ProcessorState
{
public:
    ProcessorState();
    ~ProcessorState();

    uint8_t readNextPC();
    Registers* getRegisters() { return &m_registers; }

    uint8_t add(uint8_t val1, uint8_t val2, uint8_t carry, uint8_t& flags);
    uint8_t logicalAnd(uint8_t val1, uint8_t val2, uint8_t& flags);
    uint8_t leftLogicalShift(uint8_t val, uint8_t& flags);
    uint8_t rightLogicalShift(uint8_t val, uint8_t& flags);
    uint8_t leftRotateLogicalShift(uint8_t val, uint8_t& flags);
    uint8_t rightRotateLogicalShift(uint8_t val, uint8_t& flags);
    uint8_t sub(uint8_t val1, uint8_t val2, uint8_t carry, uint8_t& flags);
    uint8_t complement(uint8_t val, uint8_t& flags);
    uint8_t logicalXOR(uint8_t val1, uint8_t val2, uint8_t& flags);
    uint8_t logicalOR(uint8_t val1, uint8_t val2, uint8_t& flags);
    uint8_t negate(uint8_t val, uint8_t& flags);

    uint8_t readFlags(uint8_t val);

    uint8_t readMemory(uint8_t address);
    void writeMemory(uint8_t address, uint8_t data);

    virtual void exit() {}
protected:
    Registers m_registers;
    Memory    m_memory;
};



#endif // L_PROCESSORSTATE_H
