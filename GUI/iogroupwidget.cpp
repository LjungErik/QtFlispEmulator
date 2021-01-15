#include "iogroupwidget.h"
#include "ui_iogroupwidget.h"

IOGroupWidget::IOGroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IOGroupWidget)
{
    ui->setupUi(this);
}

IOGroupWidget::~IOGroupWidget()
{
    delete ui;
}
