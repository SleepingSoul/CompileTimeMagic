cmake_minimum_required (VERSION 2.6)

set(PROJECT_NAME extra_std)

project(${PROJECT_NAME} CXX)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wpedantic)
endif()

set(INCLUDE_DIR include)
set(PRIVATE_INCLUDE_DIR ${INCLUDE_DIR}/private)
set(COMPILE_TIME_TESTS_DIR tests)

file(GLOB SRC_FILES
    ${INCLUDE_DIR}/*.h
    ${PRIVATE_INCLUDE_DIR}/*.h
    ${COMPILE_TIME_TESTS_DIR}/*.cpp
)

include_directories(${INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SRC_FILES})

set(CXX_STANDARD_REQUIRED true)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
