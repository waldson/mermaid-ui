#include "mermaid/parser/Location.h"

mermaid::parser::Location::Location(const std::string& file) : file(file), line(0), column(0), pos(0)
{
}

void mermaid::parser::Location::step()
{
    if (line == 0) {
        line++;
    }
    column++;
    pos++;
}

void mermaid::parser::Location::lines()
{
    line++;
    column = 0;
    pos++;
}

unsigned mermaid::parser::Location::getLine()
{
    return line;
}

unsigned mermaid::parser::Location::getPosition()
{
    return pos;
}

unsigned mermaid::parser::Location::getColumn()
{
    return column;
}
std::string mermaid::parser::Location::getFile()
{
    return file;
}
