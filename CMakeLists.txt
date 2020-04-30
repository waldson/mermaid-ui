CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(mermaid-rpg)

SET(CMAKE_CXX_STANDARD 20)
# SET(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(
    CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH}
    ${mermaid-rpg_SOURCE_DIR}/cmake
)

FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_ttf REQUIRED)

INCLUDE_DIRECTORIES(mermaid-rpg 
    ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} 
    mermaid-gui/include 
    src
)

INCLUDE_DIRECTORIES(
    mermaid-gui 
    ${SDL2_INCLUDE_DIRS} 
    ${SDL_TTF_INCLUDE_DIRS} 
    mermaid-gui/include
)

SET(LIBS ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

ADD_LIBRARY(MermaidGui STATIC 
    # base
    mermaid-gui/src/mermaid/Application.cpp
    mermaid-gui/src/mermaid/Event.cpp
    mermaid-gui/src/mermaid/EventDispatcher.cpp
    mermaid-gui/src/mermaid/Font.cpp
    mermaid-gui/src/mermaid/SdlContext.cpp
    mermaid-gui/src/mermaid/SdlRenderer.cpp
    mermaid-gui/src/mermaid/SdlWindow.cpp

    # components
    mermaid-gui/src/mermaid/components/Button.cpp
    mermaid-gui/src/mermaid/components/Cursor.cpp
    mermaid-gui/src/mermaid/components/HBox.cpp
    mermaid-gui/src/mermaid/components/Label.cpp
    mermaid-gui/src/mermaid/components/TextInput.cpp
    mermaid-gui/src/mermaid/components/VBox.cpp
    mermaid-gui/src/mermaid/components/View.cpp
    mermaid-gui/src/mermaid/components/Widget.cpp
)
TARGET_LINK_LIBRARIES(MermaidGui ${LIBS})

ADD_EXECUTABLE(mermaid-rpg 
    src/main.cpp
)
TARGET_LINK_LIBRARIES(mermaid-rpg ${LIBS} MermaidGui)

ENABLE_TESTING()
ADD_SUBDIRECTORY(tests)
