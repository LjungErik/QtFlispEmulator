#ifndef FLISPCOMPUTERWINDOW_H
#define FLISPCOMPUTERWINDOW_H

#include <QMainWindow>
#include "model.h"
#include "monitorservice.h"
#include "filereaderservice.h"

namespace Ui {
class FlispComputerWindow;
}

class FlispComputerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FlispComputerWindow(QWidget *parent = nullptr);
    ~FlispComputerWindow();

private:
    Ui::FlispComputerWindow *ui;
    MonitorService *m_monitor;
    FileReaderService *m_filereader;

private slots:
    void toggleExecution(bool start);
    void resetClicked();
    void loadClicked();
    void terminate();
    void stateUpdate(FlispProgram prog);
signals:
    void loadProgram(FlispProgram prog);
    void startExecution();
    void stopExecution();
    void resetExecution();
    void terminateExecution();
};

#endif // FLISPCOMPUTERWINDOW_H
