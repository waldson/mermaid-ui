#ifndef MERMAID_LOCATION_H
#define MERMAID_LOCATION_H

#include <string>

namespace mermaid::parser {

class Location
{

  public:
    Location(const std::string& filename);
    void step();
    void lines();
    void lines(unsigned amount);
    unsigned getLine();
    unsigned getPosition();
    unsigned getColumn();
    std::string getFile();

  private:
    std::string file;
    unsigned line;
    unsigned column;
    unsigned pos;
};
} // namespace mermaid::parser
#endif
