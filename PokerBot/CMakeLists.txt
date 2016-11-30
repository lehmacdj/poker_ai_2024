cmake_minimum_required(VERSION 3.6)
project(PokerBot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Card.cpp Card.h Range.cpp Range.h Hole.cpp Hole.h Board.cpp Board.h Hand.cpp Hand.h)
add_executable(PokerBot ${SOURCE_FILES})