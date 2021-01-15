#include "memorytablemodel.h"

MemoryTableModel::MemoryTableModel()
{
    std::fill(m_memory.begin(), m_memory.end(), 0);
}

int MemoryTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return 16;
}

int MemoryTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 16;
}

QVariant MemoryTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        uint8_t address = ((index.row() * 16) + index.column()) & 0xFF;
        return QString("%1").arg(m_memory[address], 2, 16, QLatin1Char('0'))
                .toUpper();
    }

    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    return QVariant();
}

QVariant MemoryTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            return QString("$%1").arg(section, 1, 16).toUpper();
        }
        else if (orientation == Qt::Vertical)
        {
            int vsec = section<<4;
            return QString("%1").arg(vsec, 2, 16, QLatin1Char('0')).toUpper();
        }
    }

    return QVariant();
}

void MemoryTableModel::updateMemory(MemoryState mem)
{
    m_memory = mem;
}
