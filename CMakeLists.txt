CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

# -----------------------------------------------------------------------------
# Set up the project.

project(celeroErrorHandlingBenchmark)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE)

# https://cmake.org/pipermail/cmake/2008-March/020347.html
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug CACHE STRING
       "Choose the type of build, options are: Debug Release"
       FORCE )
endif()

set(CMAKE_CXX_STANDARD 20)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_compile_options(/wd4251) # w4251 - 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
    add_compile_options(/MP)
    add_compile_options(/D_SCL_SECURE_NO_WARNINGS)
    add_compile_options(/permissive-)
    add_compile_options(/DBOOST_USE_WINAPI_VERSION=BOOST_WINAPI_VERSION_WIN7)

elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    add_compile_options(-Wall)
    add_compile_options(-fPIC)

elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
        add_compile_options(-Xclang -std=c++23)
        add_compile_options(-Wno-c++98-compat)
        add_compile_options(-Wno-c++98-compat-pedantic)
        add_compile_options(-Wno-reserved-id-macro)
    else()
        add_compile_options(-Wall)
        add_compile_options(-fPIC)
    endif()

elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
    add_compile_options(-Wall)
    add_compile_options(-fPIC)
endif()

set(CMAKE_DEBUG_POSTFIX          "-d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX        "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX "-rd" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX     "" CACHE STRING "add a postfix, usually empty on windows")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(src)
add_subdirectory(src)
