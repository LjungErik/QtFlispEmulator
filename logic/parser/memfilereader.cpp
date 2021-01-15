#include "memfilereader.h"
#include <sstream>
#include <fstream>
#include <regex>
#include <stdlib.h>

using namespace std;

const regex clrMemRegex("ClearAllMemory", regex_constants::icase | regex_constants::ECMAScript);
const regex clrRegsRegex("ClearAllRegisters", regex_constants::icase | regex_constants::ECMAScript);
const regex setMemoryRegex("setMemory[ ]+[0-9a-fA-F]{2}[ ]*=[ ]*[0-9a-fA-F]{2}", regex_constants::icase | regex_constants::ECMAScript);
const regex setRegsiterRegex("setRegister[ ]+[0-9a-fA-F]{2}[ ]*=[ ]*[0-9a-fA-F]{2}", regex_constants::icase | regex_constants::ECMAScript);
const regex memRegex("[0-9a-fA-F]{2}[ ]*=[ ]*[0-9a-fA-F]{2}", regex_constants::icase | regex_constants::ECMAScript);
const regex registerRegex("[a-zA-Z]{1,2}[ ]*=[ ]*[0-9a-fA-F]{2}", regex_constants::icase | regex_constants::ECMAScript);

typedef struct {
  uint8_t address;
  uint8_t data;
} ParsedMemory;

typedef struct {
    string reg;
    uint8_t data;
} ParsedRegister;

void ltrim(string &s)
{
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
}

void rtrim(string &s)
{
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
}

void trim(string &s)
{
    ltrim(s);
    rtrim(s);
}

string upperCase(string &s)
{
    for (auto & c: s) c = toupper(c);
    return s;
}

uint8_t parseValue(string &s)
{
    unsigned int x;
    stringstream ss;
    ss << hex << s;
    ss >> x;
    return (uint8_t) (x & 0xFF);
}

ParsedMemory extractMemory(string line)
{
    stringstream ss(line);
    string segment;
    ParsedMemory mem;

    getline(ss, segment, '=');
    trim(segment);
    mem.address = parseValue(segment);

    getline(ss, segment, '=');
    trim(segment);
    mem.data = parseValue(segment);

    return mem;
}

ParsedRegister extractRegister(string line)
{
    stringstream ss(line);
    string segment;
    ParsedRegister reg;

    getline(ss, segment, '=');
    trim(segment);
    reg.reg = upperCase(segment);

    getline(ss, segment, '=');
    trim(segment);
    reg.data = parseValue(segment);

    return reg;
}

MemFileReader::MemFileReader()
{

}


FlispProgram MemFileReader::parse(vector<string> lines)
{
    FlispProgram prog;
    std::fill(prog.mem.begin(), prog.mem.end(), 0);
    prog.reg.A = 0;
    prog.reg.X = 0;
    prog.reg.Y = 0;
    prog.reg.SP = 0;
    prog.reg.PC = 0;
    prog.reg.CC = 0;

    string line;
    for (string line: lines)
    {
        if (isCommand(line)) {
            //parse command from file
            apply(line, &prog);
        }
    }

    return prog;
}

bool MemFileReader::isCommand(string &line)
{
    for(char& c : line)
    {
        if (c == '#')
        {
            return true;
        }

        if (c != ' ') {
            break;
        }
    }
    return false;
}

void MemFileReader::apply(string &command, FlispProgram *prog)
{
    if (regex_search(command, clrMemRegex))
    {
        /* Dont do anything, we assume that this in reality is useless */
    }
    else if (regex_search(command, clrRegsRegex))
    {
        /* Dont do anything here either, assume it is useless as well */
    }
    else if (regex_search(command, setMemoryRegex))
    {
        smatch m;

        if (regex_search(command,m,memRegex)) {
            ParsedMemory mem = extractMemory(m.str(0));
            prog->mem[mem.address] = mem.data;
        }

    }
    else if (regex_search(command, setRegsiterRegex))
    {
        smatch m;
        if (regex_search(command,m,registerRegex)) {
            ParsedRegister reg = extractRegister(m.str(0));
            if (reg.reg == "A")
            {
                prog->reg.A = reg.data;
            }
            else if (reg.reg == "X")
            {
                prog->reg.X = reg.data;
            }
            else if (reg.reg == "Y")
            {
                prog->reg.Y = reg.data;
            }
            else if (reg.reg == "SP")
            {
                prog->reg.SP = reg.data;
            }
            else if (reg.reg == "PC")
            {
                prog->reg.PC = reg.data;
            }
            else if (reg.reg == "CC")
            {
                prog->reg.CC = reg.data;
            }
        }
    }
}
