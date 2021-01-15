#ifndef L_IO_H
#define L_IO_H

#include <cstdint>
#include <map>
#include "queue.h"
#include "registers.h"

#define FB_PORT 0xFB
#define FC_PORT 0xFC

class Memory;

class IOPort {
public:
    IOPort(): m_value(0) {}

    uint8_t getValue() { return m_value; }
    void setValue(uint8_t value) { m_value = value; }

    void activate() { m_active=true; }
    void deactivate() { m_active = false; }
    bool isActive() { return m_active; }
private:
    bool m_active;
    uint8_t m_value;
};

class MemoryMappedIO {
public:
    virtual bool isIOPort(uint8_t port) { return false; }
    virtual uint8_t readPort(uint8_t port) { return 0; }
    virtual bool writeOutput(uint8_t port, uint8_t value) { return false; }
};

class IO: public MemoryMappedIO
{
public:
    IO();

    bool isIOPort(uint8_t port);
    uint8_t readPort(uint8_t port);
    bool writeOutput(uint8_t port, uint8_t value);
    bool updateInput(uint8_t port, uint8_t value);

    bool registerOutput(uint8_t port);
    bool unregisterOutput(uint8_t port);

    bool registerInput(uint8_t port, uint8_t value);
    bool unregisterInput(uint8_t port);
private:
    std::map<uint8_t, IOPort> m_outputs;
    std::map<uint8_t, IOPort> m_inputs;
};

#endif // L_IO_H
