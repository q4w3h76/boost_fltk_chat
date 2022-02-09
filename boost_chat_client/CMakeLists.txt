cmake_minimum_required(VERSION 3.16)
project(boost_chat_client)

set(CMAKE_CXX_STANDARD 17)
#include libraries
#boost
set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework thread)
include_directories (${Boost_INCLUDE_DIRS})
#pthread
find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
#fltk
set(FLTK_SKIP_FLUID true)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})

add_executable(boost_chat_client Client.cpp Client.hpp main_client.cpp Window.cpp Window.hpp)
#add_executable(boost_chat_client main.cpp)
target_link_libraries (boost_chat_client  ${Boost_LIBRARIES} Threads::Threads ${FLTK_BASE_LIBRARY} ${FLTK_PLATFORM_DEPENDENT_LIBS})
