CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(mermaid-rpg-resources)

SET(CMAKE_CXX_STANDARD 20)

file(DOWNLOAD "https://raw.githubusercontent.com/vector-of-bool/cmrc/master/CMakeRC.cmake"
                 "${CMAKE_BINARY_DIR}/CMakeRC.cmake")
include("${CMAKE_BINARY_DIR}/CMakeRC.cmake")

cmrc_add_resource_library(
  mermaid-rpg-resources

  NAMESPACE mermaid
  PREFIX resources
  ALIAS mermaid::rc

  ./fonts/Roboto-Regular.ttf
)
