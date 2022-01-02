cmake_minimum_required(VERSION 2.8)

project(ImacGL)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)


include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} glimac/include third-party/include rendering/include)
include_directories(game/include)

set(FREETYPE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/freetype-2.11.1)
link_directories(${FREETYPE_DIRECTORY})
include_directories(${FREETYPE_DIRECTORY})
find_library(freetype-2.11.1 freetype-2.11.1 ${FREETYPE_DIRECTORY})

set(ALL_LIBRARIES glimac rendering game ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${FREETYPE_LIBRARIES})

add_subdirectory(glimac)
add_subdirectory(rendering)
add_subdirectory(game)



file(GLOB PROJ_DIRECTORIES "BUBBLE_RUN")

foreach(TP ${PROJ_DIRECTORIES})
    add_subdirectory(${TP})
endforeach()