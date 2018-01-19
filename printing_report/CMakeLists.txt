cmake_minimum_required(VERSION 3.5.1)
project(printing_report)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

LINK_DIRECTORIES(
    "/usr/lib/arm-linux-gnueabihf"
)

include_directories(../libs/inc)
file(GLOB SOURCES "../libs/src/*.cpp")
find_package( Boost REQUIRED COMPONENTS program_options regex )
if(Boost_FOUND)
	include_directories( ${Boost_INCLUDE_DIRS} )
	add_executable(printing_report ${SOURCES} printing_report.cpp)
endif()
