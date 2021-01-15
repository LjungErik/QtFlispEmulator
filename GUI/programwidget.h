#ifndef PROGRAMWIDGET_H
#define PROGRAMWIDGET_H

#include <QWidget>

#include "programtablemodel.h"

namespace Ui {
class ProgramWidget;
}

class ProgramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramWidget(QWidget *parent = nullptr);
    ~ProgramWidget();
    void updateProgram(FlispProgram &program);

private:
    Ui::ProgramWidget *ui;
    ProgramTableModel m_programModel;
};

#endif // PROGRAMWIDGET_H
