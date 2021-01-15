#ifndef FILEREADERSERVICE_H
#define FILEREADERSERVICE_H

#include <QObject>
#include <QString>
#include "model.h"
#include "parser/memfilereader.h"

class FileReaderService : public QObject
{
    Q_OBJECT
public:
    explicit FileReaderService(QObject *parent = nullptr);

    FlispProgram parseProgram(QString &filename);

private:
    MemFileReader m_mem_reader;

};

#endif // FILEREADERSERVICE_H
