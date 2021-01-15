#include "programtablemodel.h"
#include "model.h"

#include <QColor>

#define BYTE_COLUMN     0
#define COMMAND_COLUMN  1

ProgramTableModel::ProgramTableModel():
    m_state()
{
}

int ProgramTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_state.size();
}

int ProgramTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

QVariant ProgramTableModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole: {
        auto command = m_state.at(index.row());
        if (index.column() == BYTE_COLUMN)
        {
            return QString(command.getByteRepresentation().c_str())
                    .toUpper();
        }
        else if (index.column() == COMMAND_COLUMN)
        {
            return QString(command.getCommandRepresentation().c_str())
                    .toUpper();
        }
    }
    case Qt::BackgroundRole: {
        if (m_state.isActiveInstruction(index.row()))
        {
            return QColor(82,82,82);
        }
    }
    }

    return QVariant();
}

QVariant ProgramTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        if (orientation == Qt::Vertical)
        {
            auto command = m_state.at(section);
            return QString(command.getAddress().c_str()).toUpper();
        }
    }


    return QVariant();
}

void ProgramTableModel::updateProgram(FlispProgram &program)
{
    beginResetModel();
    m_state = ProgramState(program);
    endResetModel();
}
