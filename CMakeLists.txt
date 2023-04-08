cmake_minimum_required(VERSION 3.18)
project(mermaid-rpg LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
# SET(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${mermaid-rpg_SOURCE_DIR}/cmake)


find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Cairo REQUIRED)

include_directories(mermaid-rpg ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS}
                    mermaid-gui/include src)

                include_directories(mermaid-gui ${SDL2_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${CAIRO_INCLUDE_DIRS}
                    mermaid-gui/include)

add_library(
  MermaidGui STATIC
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

  #graphics
  mermaid-gui/src/mermaid/graphics/SDL2DrawContext.cpp
  mermaid-gui/src/mermaid/graphics/functions.cpp
)


include(FetchContent)
FetchContent_Declare(
  w5n-rope
  GIT_REPOSITORY file:///home/waldson/projects/rope-cpp
  GIT_TAG origin/feature/invert-define)
FetchContent_MakeAvailable(w5n-rope)
set(LIBS ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${CAIRO_LIBRARIES}
         w5n-rope::w5n-rope)

target_link_libraries(MermaidGui PRIVATE ${LIBS} OpenGL::GL)

add_executable(mermaid-rpg src/main.cpp)
add_custom_target(
  copy_resources
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources
    ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_dependencies(mermaid-rpg copy_resources)
add_subdirectory(resources)

target_link_libraries(mermaid-rpg PRIVATE ${LIBS} MermaidGui)
target_link_libraries(mermaid-rpg PRIVATE mermaid-rpg-resources)

target_compile_options(mermaid-rpg PUBLIC -Wall -Wextra -Wempty-body -Wpedantic -Werror -Werror=maybe-uninitialized -Warray-bounds)

# ENABLE_TESTING() ADD_SUBDIRECTORY(tests)
