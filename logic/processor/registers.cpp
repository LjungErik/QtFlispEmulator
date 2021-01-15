#include "registers.h"

Registers::Registers()
{
    clear();
}

void Registers::copy(Registers* registers)
{
    if (registers == nullptr) {
        clear();
        return;
    }

    m_A = registers->A();
    m_X = registers->X();
    m_Y = registers->Y();
    m_SP = registers->SP();
    m_PC = registers->PC();
    m_CC = registers->CC();
}

void Registers::clear() {
    m_A = 0;
    m_X = 0;
    m_Y = 0;
    m_SP = 0;
    m_PC = 0;
    m_CC = 0;
}