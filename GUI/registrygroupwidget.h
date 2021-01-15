#ifndef REGISTRYGROUPWIDGET_H
#define REGISTRYGROUPWIDGET_H

#include <QWidget>
#include "model.h"

namespace Ui {
class RegistryGroupWidget;
}

class RegistryGroupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegistryGroupWidget(QWidget *parent = nullptr);
    ~RegistryGroupWidget();
    void updateRegistries(FlispRegistries registries);

private:
    Ui::RegistryGroupWidget *ui;
};

#endif // REGISTRYGROUPWIDGET_H
