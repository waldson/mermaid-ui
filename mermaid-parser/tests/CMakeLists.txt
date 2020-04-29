CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(mermaid-parser-tests)

SET(CMAKE_CXX_STANDARD 20)
ADD_LIBRARY(Catch INTERFACE)
TARGET_INCLUDE_DIRECTORIES(Catch INTERFACE include)

ADD_EXECUTABLE(mermaid-parser-tests 
    src/main.cpp
    src/LexerTest.cpp
)

TARGET_LINK_LIBRARIES(mermaid-parser-tests PUBLIC Catch MermaidParser)

add_test(NAME MermaidParserTests COMMAND mermaid-parser-tests)
