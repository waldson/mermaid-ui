CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(mermaid-rpg)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

FIND_PACKAGE(SDL2 REQUIRED)


INCLUDE_DIRECTORIES(mermaid-rpg ${SDL2_INCLUDE_DIRS} mermaid-gui/include src/)
INCLUDE_DIRECTORIES(mermaid-gui ${SDL2_INCLUDE_DIRS} mermaid-gui/include)

SET(LIBS ${SDL2_LIBRARIES})

ADD_LIBRARY(mermaid-gui STATIC 
    mermaid-gui/src/SdlContext.cpp
    mermaid-gui/src/SdlWindow.cpp
    mermaid-gui/src/SdlRenderer.cpp
    mermaid-gui/src/Application.cpp
    mermaid-gui/src/components/View.cpp
    mermaid-gui/src/components/View.cpp
)
TARGET_LINK_LIBRARIES(mermaid-gui ${LIBS})

ADD_EXECUTABLE(mermaid-rpg 
    src/main.cpp
)
TARGET_LINK_LIBRARIES(mermaid-rpg ${LIBS} mermaid-gui)
