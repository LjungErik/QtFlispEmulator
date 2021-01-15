#ifndef L_MEMFILEREADER_H
#define L_MEMFILEREADER_H

#include "model.h"

#include <string>
#include <vector>

class MemFileReader
{
public:
    MemFileReader();
    FlispProgram parse(std::vector<std::string> lines);

private:
    bool isCommand(std::string &line);
    void apply(std::string &command, FlispProgram *prog);
};

#endif // L_MEMFILEREADER_H
