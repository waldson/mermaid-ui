CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(mermaid-rpg-tests)

SET(CMAKE_CXX_STANDARD 20)
ADD_LIBRARY(Catch INTERFACE)
TARGET_INCLUDE_DIRECTORIES(Catch INTERFACE include)

ADD_EXECUTABLE(mermaid-rpg-tests 
    src/main.cpp
    src/WidgetTest.cpp
)
TARGET_LINK_LIBRARIES(mermaid-rpg-tests PUBLIC Catch MermaidGui)

add_test(NAME MermaidRPGTest COMMAND mermaid-rpg-tests)
