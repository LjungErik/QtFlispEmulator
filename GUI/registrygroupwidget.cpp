#include "registrygroupwidget.h"
#include "ui_registrygroupwidget.h"
#include <bitset>

RegistryGroupWidget::RegistryGroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistryGroupWidget)
{
    ui->setupUi(this);
}

RegistryGroupWidget::~RegistryGroupWidget()
{
    delete ui;
}

void RegistryGroupWidget::updateRegistries(FlispRegistries registries)
{
    QString aBin = QString("%1").arg(registries.A, 8, 2, QChar('0'));
    QString aHex = QString("%1").arg(registries.A, 2, 16, QChar('0')).toUpper();
    ui->a_bin_registry->setText(aBin);
    ui->a_hex_registry->setText(aHex);

    QString xBin = QString("%1").arg(registries.X, 8, 2, QChar('0'));
    QString xHex = QString("%1").arg(registries.X, 2, 16, QChar('0')).toUpper();
    ui->x_bin_registry->setText(xBin);
    ui->x_hex_registry->setText(xHex);

    QString yBin = QString("%1").arg(registries.Y, 8, 2, QChar('0'));
    QString yHex = QString("%1").arg(registries.Y, 2, 16, QChar('0')).toUpper();
    ui->y_bin_registry->setText(yBin);
    ui->y_hex_registry->setText(yHex);

    QString spBin = QString("%1").arg(registries.SP, 8, 2, QChar('0'));
    QString spHex = QString("%1").arg(registries.SP, 2, 16, QChar('0')).toUpper();
    ui->sp_bin_registry->setText(spBin);
    ui->sp_hex_registry->setText(spHex);

    QString pcBin = QString("%1").arg(registries.PC, 8, 2, QChar('0'));
    QString pcHex = QString("%1").arg(registries.PC, 2, 16, QChar('0')).toUpper();
    ui->pc_bin_registry->setText(pcBin);
    ui->pc_hex_registry->setText(pcHex);

    QString ccBin = QString("%1").arg(registries.CC, 8, 2, QChar('0'));
    QString ccHex = QString("%1").arg(registries.CC, 2, 16, QChar('0')).toUpper();
    ui->cc_bin_registry->setText(ccBin);
    ui->cc_hex_registry->setText(ccHex);
}
