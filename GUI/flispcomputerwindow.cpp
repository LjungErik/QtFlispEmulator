#include "flispcomputerwindow.h"
#include "ui_flispcomputerwindow.h"
#include "registrygroupwidget.h"

#include <QTimer>
#include <QFontDatabase>
#include <QFileDialog>
#include <QPushButton>
#include<QDebug>

#include<vector>

FlispComputerWindow::FlispComputerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FlispComputerWindow)
{
    QFontDatabase::addApplicationFont(":/fonts/digital-7-mono.ttf");

    m_filereader = new FileReaderService();
    /* Setup logic thread for executing */
    m_monitor = new MonitorService();
    connect(m_monitor, &MonitorService::stateUpdate, this, &FlispComputerWindow::stateUpdate);
    connect(this, &FlispComputerWindow::startExecution, m_monitor, &MonitorService::startExecution);
    connect(this, &FlispComputerWindow::stopExecution, m_monitor, &MonitorService::stopExecution);
    connect(this, &FlispComputerWindow::resetExecution, m_monitor, &MonitorService::reset);
    connect(this, &FlispComputerWindow::loadProgram, m_monitor, &MonitorService::loadProgram);
    connect(m_monitor, &QThread::finished, m_monitor, &QObject::deleteLater);
    m_monitor->start();

    ui->setupUi(this);
    connect(ui->startBtn, SIGNAL (clicked(bool)), this, SLOT (toggleExecution(bool)));
    connect(ui->resetBtn, &QPushButton::clicked, this, &FlispComputerWindow::resetClicked);
    connect(ui->actionLoad, &QAction::triggered, this, &FlispComputerWindow::loadClicked);
}

FlispComputerWindow::~FlispComputerWindow()
{
    delete ui;
}

void FlispComputerWindow::stateUpdate(FlispProgram prog)
{
    qInfo() << "stateUpdate occurred!!";
    ui->memoryGroup->updateMemory(prog.mem);
    ui->registryGroup->updateRegistries(prog.reg);
    ui->programGroup->updateProgram(prog);
}

void FlispComputerWindow::toggleExecution(bool start)
{
    if (start) {
        emit startExecution();
        qInfo() << "start Execution!";
        ui->startBtn->setText("Stop");
    }
    else {
        emit stopExecution();
        qInfo() << "stop Execution!";
        ui->startBtn->setText("Start");
    }
}

void FlispComputerWindow::resetClicked()
{
    qInfo() << "Reset clicked";
    /* TODO: Implement logic for reset logic */
    emit resetExecution();
}

void FlispComputerWindow::loadClicked()
{
    qInfo() << "Load clicked!";
    emit stopExecution();
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    tr("Control design (*.fmem);;S-records (*.s19);;FLISP control design (*.fcs)"));
    FlispProgram prog = m_filereader->parseProgram(filename);
    ui->memoryGroup->updateMemory(prog.mem);
    ui->registryGroup->updateRegistries(prog.reg);
    ui->programGroup->updateProgram(prog);
    emit loadProgram(prog);
}

void FlispComputerWindow::terminate()
{
    /* TODO: Implement logic for terminating */
}
