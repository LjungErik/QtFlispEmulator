#ifndef PROGRAMCOMMAND_H
#define PROGRAMCOMMAND_H

#include <string>
#include <iterator>
#include "model.h"

class ProgramCommand
{
public:
    ProgramCommand(uint8_t *address);
    ProgramCommand(uint8_t *address, MemoryState mem);

    uint8_t getRawAddress() const;

    std::string getAddress() const;
    std::string getByteRepresentation() const;
    std::string getCommandRepresentation() const;

private:
    uint8_t m_address;
    uint8_t m_opcode;
    uint8_t m_byte;
    uint8_t m_method;

    bool hasDataByte() const;
};

#endif // PROGRAMCOMMAND_H
