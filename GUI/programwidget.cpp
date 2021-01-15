#include "programwidget.h"
#include "ui_programwidget.h"

ProgramWidget::ProgramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramWidget),
    m_programModel()
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_programModel);
}

ProgramWidget::~ProgramWidget()
{
    delete ui;
}

void ProgramWidget::updateProgram(FlispProgram &program)
{
    m_programModel.updateProgram(program);
}
