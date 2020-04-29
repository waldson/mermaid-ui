#include "mermaid/parser/Error.h"
#include "mermaid/parser/Parser.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        return -1;
    }

    try {
        mermaid::parser::Parser parser;

        parser.parse(std::string(argv[1]));
    } catch (mermaid::parser::Error& error) {
        std::cout << "Error: " << error.getMessage() << std::endl;
        return -11;
    }

    return 0;
}
