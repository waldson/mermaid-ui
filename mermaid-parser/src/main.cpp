#include "mermaid/parser/CodeGenerator.h"
#include "mermaid/parser/Error.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        return -1;
    }

    try {
        mermaid::parser::CodeGenerator gen;

        auto response = gen.generateHeader(argv[1]);

        std::cout << response << std::endl;

    } catch (mermaid::parser::Error& error) {
        std::cout << "Error: " << error.getLocation().getFile() << ':' << error.getLocation().getLine() << ":"
                  << error.getLocation().getColumn() << " " << error.getMessage() << std::endl;
        return -11;
    } catch (std::string& error) {
        std::cout << error << std::endl;
    }

    return 0;
}
