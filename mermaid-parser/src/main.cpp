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

        std::cout << "Class: " << parser.getClass() << std::endl;
        std::cout << "Namespace: " << parser.getNamespace() << std::endl;

        std::cout << "Variables:" << std::endl;
        for (auto& v : parser.getDataVariables()) {
            std::cout << v.name;
            if (v.defaultValue) {
                std::cout << "= " << v.defaultValue.value();
            }
            if (v.attributes.size() > 0) {
                std::cout << "<<<<<<Attributes::" << std::endl;
                for (auto& a: v.attributes) {
                    std::cout << a.first << "=" << a.second << std::endl;
                }


            }
            std::cout << ";" << std::endl;

        }

        std::cout << std::endl;
        std::cout << "Props:" << std::endl;
        for (auto& v : parser.getProps()) {
            std::cout << v.name;
            if (v.defaultValue) {
                std::cout << "= " << v.defaultValue.value();
            }
            std::cout << ";" << std::endl;
            if (v.attributes.size() > 0) {
                std::cout << "<<<<<<Attributes(" << v.attributes.size() << ")" << std::endl;
                for (auto& a: v.attributes) {
                    std::cout << a.first << "=" << a.second << std::endl;
                }
                std::cout << ">>>>>Attributes" << std::endl;


            }
        }


    } catch (mermaid::parser::Error& error) {
        std::cout << "Error: " 
            << error.getLocation().getFile() 
            << ':' << error.getLocation().getLine() << "." 
            << error.getLocation().getColumn() <<  " "
            << error.getMessage() << std::endl;
        return -11;
    }

    return 0;
}
