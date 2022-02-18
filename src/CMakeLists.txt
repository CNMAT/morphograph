cmake_minimum_required(VERSION 2.8.9)
project (morphograph)

SET(CMAKE_CXX_FLAGS "-Wall -g -O2 -std=c++17 -I . -Wno-return-type-c-linkage")

add_executable(morphograph morphograph.cpp Morphograph.h parser.h FFT.h features.h WavFile.h algorithms.h analysis.h svg.h utilities.h)
target_link_libraries (morphograph dl ${LIBS})

INSTALL(
    TARGETS morphograph)
