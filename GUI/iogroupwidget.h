#ifndef IOGROUPWIDGET_H
#define IOGROUPWIDGET_H

#include <QWidget>

namespace Ui {
class IOGroupWidget;
}

class IOGroupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IOGroupWidget(QWidget *parent = nullptr);
    ~IOGroupWidget();

private:
    Ui::IOGroupWidget *ui;
};

#endif // IOGROUPWIDGET_H
