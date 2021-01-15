#ifndef PROGRAMTABLEMODEL_H
#define PROGRAMTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <string>

#include "processor/programstate.h"

class ProgramTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ProgramTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void updateProgram(FlispProgram &program);

private:
    ProgramState m_state;
};

#endif // PROGRAMTABLEMODEL_H
