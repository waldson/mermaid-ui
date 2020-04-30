CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(mermaid-parser)

SET(CMAKE_CXX_STANDARD 20)
# SET(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Boost_USE_STATIC_LIBS        ON)  
set(Boost_USE_DEBUG_LIBS         OFF)
set(Boost_USE_RELEASE_LIBS       ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
FIND_PACKAGE(Boost REQUIRED) #algorithm header-only library

INCLUDE_DIRECTORIES(
    include/
    ${Boost_INCLUDE_DIRS}
)

ADD_LIBRARY(MermaidParser STATIC 
    # base
    src/mermaid/parser/Error.cpp
    src/mermaid/parser/Lexer.cpp
    src/mermaid/parser/Location.cpp
    src/mermaid/parser/Parser.cpp
    src/mermaid/parser/CodeGenerator.cpp
)

ADD_EXECUTABLE(
    mm 
    src/main.cpp
)

TARGET_LINK_LIBRARIES(mm MermaidParser)
ENABLE_TESTING()
ADD_SUBDIRECTORY(tests)
