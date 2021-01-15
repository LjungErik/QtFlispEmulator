#ifndef L_CPU_H
#define L_CPU_H

#include "processorstate.h"
#include <chrono>

class ExternalService {
public:
    virtual void signalUpdate() {}
};

class CPU: public ProcessorState
{
public:
    CPU(ExternalService* service);
    ~CPU();
    void loadMemory(MemoryState mem);
    void loadRegistry(Registers *registers);
    void executeNext();
    void reset();

    ReadOnlyMemory* getReadOnlyMemory() {return &m_memory;}
    ReadOnlyRegisters* getReadOnlyRegisters() {return &m_registers;}
private:
    bool         m_reset;
    IO           m_io;
    ExternalService* m_external;
};

#endif // L_CPU_H
