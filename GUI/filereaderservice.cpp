#include "filereaderservice.h"
#include "parser/memfilereader.h"

#include <QFile>
#include <QTextStream>
#include <string>
#include <vector>

FileReaderService::FileReaderService(QObject *parent) :
    QObject(parent),
    m_mem_reader()
{

}

FlispProgram FileReaderService::parseProgram(QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        /* Add better handling of not being able to open file */
        return FlispProgram{};
    }

    std::vector<std::string> lines;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        lines.push_back(line.toStdString());
    }

    return m_mem_reader.parse(lines);
}
