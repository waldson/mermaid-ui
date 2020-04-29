#include "Driver.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        return -1;
    }

    mermaid::parser::Driver driver;
    int result = driver.parse(argv[1]);
    if (result == 0) {
        std::cout << "Class: " << driver.className << std::endl;
        std::cout << "Namespace: " << driver.ns << std::endl;
    }

    return result;
}
