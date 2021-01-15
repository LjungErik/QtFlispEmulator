#include "memorywidget.h"
#include "ui_memorywidget.h"

MemoryWidget::MemoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemoryWidget),
    mem_model()
{
    ui->setupUi(this);
    ui->tableView->setModel(&mem_model);
}

MemoryWidget::~MemoryWidget()
{
    delete ui;
}

void MemoryWidget::updateMemory(MemoryState mem)
{
    mem_model.updateMemory(mem);
}
