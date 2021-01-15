#include "programstate.h"

#define MAX_PROGRAM_ADDRESS 0xFB

ProgramState::ProgramState() :
    m_commands(),
    m_pc(0x00)
{
    for (uint8_t i = 0; i < MAX_PROGRAM_ADDRESS; i++){
        m_commands.push_back(ProgramCommand(&i));
    }
}

ProgramState::ProgramState(FlispProgram& program):
    m_commands(),
    m_pc(program.reg.PC)
{
    for (uint8_t i = 0; i < MAX_PROGRAM_ADDRESS; i++) {
        m_commands.push_back(ProgramCommand(&i, program.mem));
    }
}

int ProgramState::size() const
{
    return m_commands.size();
}

ProgramCommand ProgramState::at(int index) const
{
    return m_commands[index];
}


bool ProgramState::isActiveInstruction(uint8_t index) const
{
    return m_pc == m_commands[index].getRawAddress();
}
