#include "monitorservice.h"
#include <chrono>

#include<QDebug>
#include <QAbstractEventDispatcher>

using namespace std;

#define MAX_RUNNING_SPEED_MS 1000

MonitorService::MonitorService():
    m_run(false),
    m_cpu(this),
    m_speed(MAX_RUNNING_SPEED_MS)
{
}

MonitorService::~MonitorService()
{
}

void MonitorService::run()
{
    while(!isInterruptionRequested())
    {
        auto start = chrono::high_resolution_clock::now();
        if (m_run)
        {
            m_cpu.executeNext();
        }

        eventDispatcher()->processEvents(QEventLoop::AllEvents);

        auto stop = chrono::high_resolution_clock::now();
        auto exec_time = chrono::duration_cast<chrono::microseconds>(stop-start);

        //auto wait_time = (m_speed - exec_time);
        msleep(100);
    }
}

void MonitorService::loadProgram(FlispProgram prog) {
    qInfo() << "Loading memory";

    Registers registers;
    registers.A(prog.reg.A);
    registers.X(prog.reg.X);
    registers.Y(prog.reg.Y);
    registers.SP(prog.reg.SP);
    registers.PC(prog.reg.PC);
    registers.CC(prog.reg.CC);

    m_cpu.loadMemory(prog.mem);
    m_cpu.loadRegistry(&registers);
}

void MonitorService::stopExecution()
{
    qInfo() << "inside monitorservice: " << "stop execution";
    m_run = false;
}

void MonitorService::startExecution()
{
    qInfo() << "inside monitorservice: " << "start execution";
    m_run = true;
}

void MonitorService::reset()
{
    qInfo() << "reset cpu execution";
    m_cpu.reset();
}

void MonitorService::signalUpdate()
{
    FlispProgram prog;
    ReadOnlyMemory *ro_mem = m_cpu.getReadOnlyMemory();
    prog.mem = ro_mem->exportMemory();

    ReadOnlyRegisters * ro_reg = m_cpu.getReadOnlyRegisters();

    FlispRegistries reg;
    prog.reg.A = ro_reg->A();
    prog.reg.X = ro_reg->X();
    prog.reg.Y = ro_reg->Y();
    prog.reg.SP = ro_reg->SP();
    prog.reg.PC = ro_reg->PC();
    prog.reg.CC = ro_reg->CC();

    emit stateUpdate(prog);
}

