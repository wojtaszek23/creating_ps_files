cmake_minimum_required(VERSION 3.5.1)
project(make_template)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

LINK_DIRECTORIES(
    "/usr/lib/arm-linux-gnueabihf"
)

include_directories(../../libs/inc)
file(GLOB SOURCES "../../libs/src/*.cpp")
find_package( Boost REQUIRED COMPONENTS program_options regex )
if(Boost_FOUND)
	include_directories( ${Boost_INCLUDE_DIRS} )
	add_executable(make_template ${SOURCES} make_template.cpp)
endif()
