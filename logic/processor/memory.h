#ifndef L_MEMORY_H
#define L_MEMORY_H

#include <cstdint>
#include "io.h"
#include "model.h"

class ReadOnlyMemory {
public:
    virtual MemoryState exportMemory() { return MemoryState(); }
};

class Memory: public ReadOnlyMemory {
public:
    Memory();
    ~Memory();

    void copy(MemoryState mem);
    void setupMemoryMappedIO(MemoryMappedIO* io) {m_io = io;}

    uint8_t readMemory(uint8_t address) const;
    void writeMemory(uint8_t address, uint8_t data);

    MemoryState exportMemory();

private:
    MemoryState m_memory;
    MemoryMappedIO* m_io;
};

#endif // L_MEMORY_H
