#ifndef PROGRAMSTATE_H
#define PROGRAMSTATE_H

#include <cstdint>
#include <vector>
#include "programcommand.h"

class ProgramState
{
public:
    ProgramState();
    ProgramState(FlispProgram& program);

    int size() const;
    ProgramCommand at(int index) const;
    bool isActiveInstruction(uint8_t index) const;

private:
    std::vector<ProgramCommand> m_commands;
    uint8_t m_pc;
};

#endif // PROGRAMSTATE_H
