#include "programcommand.h"
#include <iomanip>
#include <sstream>

#define INVALID             0x00
#define INHERENT            0x01
#define IMMEDIATE           0x02
#define ABSOLUTE            0x03
#define RELATIVE            0x04
#define INDEX_N_SP          0x05
#define INDEX_N_X           0x06
#define INDEX_A_X           0x07
#define INDEX_X_PLUS        0x08
#define INDEX_X_MINUS       0x09
#define INDEX_PLUS_X        0x0A
#define INDEX_MINUS_X       0x0B
#define INDEX_N_Y           0x0C
#define INDEX_A_Y           0x0D
#define INDEX_Y_PLUS        0x0E
#define INDEX_Y_MINUS       0x0F
#define INDEX_PLUS_Y        0x10
#define INDEX_MINUS_Y       0x11

const uint8_t instructionMethods[256] = {
    INHERENT, IMMEDIATE, IMMEDIATE, INVALID, INVALID, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT,
    INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT, INHERENT,
    RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE, RELATIVE,
    ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE,
    INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INHERENT, INHERENT, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP,
    INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X,
    INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X, INDEX_A_X,
    INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y,
    INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y, INDEX_A_Y,
    IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, IMMEDIATE, INHERENT,
    ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, INHERENT,
    INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INDEX_N_SP, INHERENT,
    INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_X, INDEX_N_Y, INHERENT,
    INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_Y, INDEX_N_SP, INDEX_N_SP, INDEX_N_Y, INVALID,
    INVALID, ABSOLUTE, INDEX_N_SP, INDEX_N_X, INDEX_A_X, INDEX_X_PLUS, INDEX_X_MINUS, INDEX_PLUS_X, INDEX_MINUS_X, INDEX_N_Y, INDEX_A_Y, INDEX_Y_PLUS, INDEX_Y_MINUS, INDEX_PLUS_Y, INDEX_MINUS_Y, INVALID,
    IMMEDIATE, ABSOLUTE, INDEX_N_SP, INDEX_N_X, INDEX_A_X, INDEX_X_PLUS, INDEX_X_MINUS, INDEX_PLUS_X, INDEX_MINUS_X, INDEX_N_Y, INDEX_A_Y, INDEX_Y_PLUS, INDEX_Y_MINUS, INDEX_PLUS_Y, INDEX_MINUS_Y, INVALID
};

const char* commandName[256] = {
    "NOP", "ANDCC", "ORCC", NULL,   NULL,   "CLRA", "NEGA", "INCA", "DECA",     "TSTA",     "COMA",    "LSLA",    "LSRA",    "ROLA",    "RORA",    "ASRA",
    "PSHA", "PSHX", "PSHY", "PSHC", "PULA", "PULX", "PULY", "PULC", "TFR A,CC", "TFR CC,A", "TFR X,Y", "TFR Y,X", "TFR X,S", "TFR S,X", "TFR Y,S", "TFR S,Y",
    "BSR",  "BRA",  "BMI",  "BPL",  "BEQ",  "BNE",  "BVS",  "BVC",  "BCS",      "BCC",      "BHI",     "BLS",     "BGT",     "BGE",     "BLE",     "BLT",
    "STX",  "STY",  "STSP", "JMP",  "JSR",  "CLR",  "NEG",  "INC",  "DEC",      "TST",      "COM",     "LSL",     "LSR",     "ROL",     "ROR",     "ASR",
    "STX",  "STY",  "STSP", "RTS",  "RTI",  "CLR",  "NEG",  "INC",  "DEC",      "TST",      "COM",     "LSL",     "LSR",     "ROL",     "ROR",     "ASR",
    "STX",  "STY",  "STSP", "JMP",  "JSR",  "CLR",  "NEG",  "INC",  "DEC",      "TST",      "COM",     "LSL",     "LSR",     "ROL",     "ROR",     "ASR",
    "STX",  "STY",  "STSP", "JMP",  "JSR",  "CLR",  "NEG",  "INC",  "DEC",      "TST",      "COM",     "LSL",     "LSR",     "ROL",     "ROR",     "ASR",
    "STX",  "STY",  "STSP", "JMP",  "JSR",  "CLR",  "NEG",  "INC",  "DEC",      "TST",      "COM",     "LSL",     "LSR",     "ROL",     "ROR",     "ASR",
    "STX",  "STY",  "STSP", "JMP",  "JSR",  "CLR",  "NEG",  "INC",  "DEC",      "TST",      "COM",     "LSL",     "LSR",     "ROL",     "ROR",     "ASR",
    "LTX",  "LDY",  "LDSP", "SBCA", "SUBA", "ADCA", "ADDA", "CMPA", "BITA",     "ANDA",     "ORA",     "EORA",    "CMPX",    "CMPY",    "CMPSP",   "EXG A,CC",
    "LTX",  "LDY",  "LDSP", "SBCA", "SUBA", "ADCA", "ADDA", "CMPA", "BITA",     "ANDA",     "ORA",     "EORA",    "CMPX",    "CMPY",    "CMPSP",   "EXG X,Y",
    "LTX",  "LDY",  "LDSP", "SBCA", "SUBA", "ADCA", "ADDA", "CMPA", "BITA",     "ANDA",     "ORA",     "EORA",    "CMPX",    "CMPY",    "LEASP",   "EXG X,SP",
    "LTX",  "LDY",  "LDSP", "SBCA", "SUBA", "ADCA", "ADDA", "CMPA", "BITA",     "ANDA",     "ORA",     "EORA",    "LEAX",    "LEAY",    "LEASP",   "EXG Y,SP",
    "LTX",  "LDY",  "LDSP", "SBCA", "SUBA", "ADCA", "ADDA", "CMPA", "BITA",     "ANDA",     "ORA",     "EORA",    "LEAX",    "LEAY",    "LEASP",   NULL,
     NULL,  "STA",  "STA",  "STA",  "STA",  "STA",  "STA",  "STA",  "STA",      "STA",      "STA",     "STA",     "STA",     "STA",     "STA",     NULL,
    "LDA",  "LDA",  "LDA",  "LDA",  "LDA",  "LDA",  "LDA",  "LDA",  "LDA",      "LDA",      "LDA",     "LDA",     "LDA",     "LDA",     "LDA",     NULL
};

std::string to_hex(uint8_t val)
{
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2) << std::hex << int(val);
    return stream.str();
}

ProgramCommand::ProgramCommand(uint8_t *address):
    m_address((*address)),
    m_opcode(0x00),
    m_byte(0x00),
    m_method(INHERENT)
{
}

ProgramCommand::ProgramCommand(uint8_t *address, MemoryState mem):
    ProgramCommand(address)
{
    m_opcode = mem[(*address)];
    m_method = instructionMethods[m_opcode];
    if (hasDataByte())
    {
        (*address)+=1;
        m_byte = mem[(*address)];
    }
}

uint8_t ProgramCommand::getRawAddress() const
{
    return m_address;
}

std::string ProgramCommand::getAddress() const
{
    return to_hex(m_address);
}

std::string ProgramCommand::getByteRepresentation() const
{
    std::stringstream stream;
    stream << to_hex(m_opcode);
    if (hasDataByte())
    {
        stream << " " << to_hex(m_byte);
    }

    return stream.str();
}

std::string ProgramCommand::getCommandRepresentation() const
{
    std::stringstream stream;
    auto name = commandName[m_opcode];
    switch(m_method)
    {
    case INVALID:
        stream << "INVALID";
        break;
    case IMMEDIATE:
        stream << name << "  #$" << to_hex(m_byte);
        break;
    case ABSOLUTE:
        stream << name << "  $" << to_hex(m_byte);
        break;
    case RELATIVE: {
        uint8_t offset = ((m_address+0x2) + m_byte) & 0xFF;
        stream << name << "  $" << to_hex(offset);
        break;
    }
    case INDEX_N_SP:
        stream << name << "  $" << to_hex(m_byte) <<",SP";
        break;
    case INDEX_N_X:
        stream << name << "  $" << to_hex(m_byte) << ",X";
        break;
    case INDEX_N_Y:
        stream << name << "  $" << to_hex(m_byte) << ",Y";
        break;
    case INDEX_A_X:
        stream << name << "  A,X";
        break;
    case INDEX_A_Y:
        stream << name << "  A,Y";
        break;
    case INDEX_X_PLUS:
        stream << name << "  ,X+";
        break;
    case INDEX_Y_PLUS:
        stream << name << "  ,Y+";
        break;
    case INDEX_X_MINUS:
        stream << name << "  ,X-";
        break;
    case INDEX_Y_MINUS:
        stream << name << "  ,Y-";
        break;
    case INDEX_PLUS_X:
        stream << name << "  ,+X";
        break;
    case INDEX_PLUS_Y:
        stream << name << "  ,+Y";
        break;
    case INDEX_MINUS_X:
        stream << name << "  ,-X";
        break;
    case INDEX_MINUS_Y:
        stream << name << "  ,-Y";
        break;
    case INHERENT:
        stream << name;
    }

    return stream.str();
}

bool ProgramCommand::hasDataByte() const
{
    switch(this->m_method)
    {
    case IMMEDIATE:
    case ABSOLUTE:
    case RELATIVE:
    case INDEX_N_SP:
    case INDEX_N_X:
    case INDEX_N_Y:
        return true;
    default:
        return false;
    }
}
