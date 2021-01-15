#ifndef L_MODEL_H
#define L_MODEL_H

#include <cstdint>
#include <array>

#define MEMORY_SIZE 256

typedef std::array<uint8_t, MEMORY_SIZE> MemoryState;

typedef struct {
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint8_t SP;
    uint8_t PC;
    uint8_t CC;
} FlispRegistries;

typedef struct {
    MemoryState mem;
    FlispRegistries reg;
} FlispProgram;

#endif // L_MODEL_H
