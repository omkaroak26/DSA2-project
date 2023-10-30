cmake_minimum_required(VERSION 3.00)
project(DSA2project C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_FLAGS} -lm")
include_directories(HEADER_FILES)
file(GLOB MAIN 
	"SOURCE_FILES/*.c"
	"HEADER_FILES/*.h"
	)
	add_executable(ImageManipulator ${MAIN})
