#ifndef MONITORSERVICE_H
#define MONITORSERVICE_H

#include "QThread"
#include "processor/cpu.h"
#include "model.h"

#include <chrono>
#include <thread>

class MonitorService: public QThread, public ExternalService
{
    Q_OBJECT
public:
    MonitorService();
    ~MonitorService();

    void run() override;
    void signalUpdate() override;

public slots:
    void loadProgram(FlispProgram prog);
    void stopExecution();
    void startExecution();
    void reset();

private:
    bool m_run;
    CPU m_cpu;
    std::chrono::microseconds m_speed;
signals:
    void stateUpdate(FlispProgram prog);
};

#endif // MONITORSERVICE_H
