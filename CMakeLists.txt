# Author: Claudio Correa, 2021/05/15

# Ref.: https://cmake.org/examples
# To build, use these commands:
# mkdir build		# Create a build directory
# cd build && cmake ..	# Build from that directory so the build files are in one place
# cmake --build .	# Build the project

cmake_minimum_required(VERSION 3.14...3.18)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(rpg2
  VERSION
    1.0
  DESCRIPTION
    "Very basic project"
  LANGUAGES
    C CXX
)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_C_STANDARD 11)	# Requires C11 standard
set(CMAKE_BUILD_TYPE Release)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Bump up warning levels appropriately for clang & gcc and build in debug mode
if (${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra -Wunused")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -fno-omit-frame-pointer -march=native")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -DDBG")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")
endif()
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wunused")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c11 -march=native")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(myprjlib STATIC lib/dbconnect.c lib/mesa.c lib/section.c lib/ocupacao.c)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)


set(SOURCES src/principal.c lib/ficha.c include/ficha.h include/ocupacao.h lib/screens/mesasScreen.c lib/screens/screens.c lib/screens/secaoScreen.c)

# Dependences
# SQL
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSQLCLIENT REQUIRED mysqlclient)
link_directories(${LIBSQLCLIENT_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} myprjlib)

# Search OpenSSL
pkg_search_module(OPENSSL REQUIRED openssl)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIRS})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
else()
    # Error; with REQUIRED, pkg_search_module() will throw an error by it's own
endif()
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})

foreach(FLAG ${LIBSQLCLIENT_CFLAGS_OTHER})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG}")
endforeach()

if(LIBSQLCLIENT_FOUND)
    add_definitions(-DHAVE_SQL)
    include_directories(${LIBSQLCLIENT_INCLUDE_DIRS})
    add_library(sqlprjlib STATIC lib/helloSQL.c)
    target_link_libraries(sqlprjlib ${LIBSQLCLIENT_LIBRARIES})

    target_include_directories(${PROJECT_NAME} PUBLIC ${LIBSQLCLIENT_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} sqlprjlib)
endif()

# NCURSES
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARY})
if(Curses_FOUND)
    add_definitions(-DHAVE_CURSES)
endif()