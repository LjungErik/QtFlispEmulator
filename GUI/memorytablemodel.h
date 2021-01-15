#ifndef MEMORYTABLEMODEL_H
#define MEMORYTABLEMODEL_H

#include "model.h"

#include <QAbstractTableModel>

class MemoryTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MemoryTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void updateMemory(MemoryState mem);

private:
    MemoryState m_memory;
};

#endif // MEMORYTABLEMODEL_H
