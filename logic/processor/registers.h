#ifndef L_REGISTERS_H
#define L_REGISTERS_H

#include <cstdint>
#include <vector>

#define N_BIT 0x08
#define Z_BIT 0x04
#define V_BIT 0x02
#define C_BIT 0x01

class ReadOnlyRegisters
{
public:
    virtual uint8_t A() const {return 0;}
    virtual uint8_t X() const {return 0;}
    virtual uint8_t Y() const {return 0;}
    virtual uint8_t SP() const {return 0;}
    virtual uint8_t PC() const {return 0;}
    virtual uint8_t CC() const {return 0;}
};

class Registers : public ReadOnlyRegisters
{
public:
    Registers();
    ~Registers() {}

    void copy(Registers* registers);

    uint8_t A() const { return m_A; }
    void A(uint8_t value) { m_A = value; }

    uint8_t X() const { return m_X; }
    void X(uint8_t value) { m_X = value; }

    uint8_t Y() const { return m_Y; }
    void Y(uint8_t value) { m_Y = value; }

    uint8_t SP() const { return m_SP; }
    void SP(uint8_t value) { m_SP = value; }

    uint8_t PC() const { return m_PC; }
    void PC(uint8_t value) { m_PC = value; }

    uint8_t CC() const { return m_CC; }
    void CC(uint8_t value) { m_CC = value; }

    void clear();
private:
    uint8_t m_A;
    uint8_t m_X;
    uint8_t m_Y;
    uint8_t m_SP;
    uint8_t m_PC;
    uint8_t m_CC;
};

#endif // L_REGISTERS_H
