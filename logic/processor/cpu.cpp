#include "cpu.h"
#include "instructions.h"

#define RESET_VECTOR 0xFF

using namespace std;


CPU::CPU(ExternalService* external):
    ProcessorState(),
    m_reset(false),
    m_external(external),
    m_io()
{
    m_memory.setupMemoryMappedIO(&m_io);
}

CPU::~CPU()
{
    m_external = nullptr;
}

void CPU::loadMemory(MemoryState mem)
{
    m_reset = false;
    m_memory.copy(mem);
}

void CPU::loadRegistry(Registers *registers)
{
    m_reset = false;
    m_registers.copy(registers);
}

void CPU::executeNext()
{
    if (!m_reset) {
        reset();
    }
    else {
        uint8_t opcode = readNextPC();
        Instructions::execute(opcode, this);
        m_external->signalUpdate();
    }
}

void CPU::reset()
{
    uint8_t start_addr = m_memory.readMemory(RESET_VECTOR);
    m_registers.PC(start_addr);
    m_reset = true;
    m_external->signalUpdate();
}
