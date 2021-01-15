#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include <QWidget>
#include "memorytablemodel.h"

namespace Ui {
class MemoryWidget;
}

class MemoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryWidget(QWidget *parent = nullptr);
    ~MemoryWidget();
    void updateMemory(MemoryState mem);

private:
    Ui::MemoryWidget *ui;
    MemoryTableModel mem_model;
};

#endif // MEMORYWIDGET_H
