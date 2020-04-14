cmake_minimum_required (VERSION 3.1)

set(PROJECT_NAME extra_std)

project(${PROJECT_NAME} CXX)

if (MSVC)
    add_compile_options(/W4 /WX-)
else()
    add_compile_options(-Wall -Wpedantic)
endif()

set(INCLUDE_DIR include)
set(PRIVATE_INCLUDE_DIR ${INCLUDE_DIR}/private)
set(ESTD_TESTS_DIR tests)

set(EXTERNAL_DIR external)

set(GTEST_ROOT ${EXTERNAL_DIR}/gtest/googletest)
set(GTEST_INCLUDE ${GTEST_ROOT}/include)
set(GTEST_SRC ${GTEST_ROOT}/src)

set(GMOCK_ROOT ${EXTERNAL_DIR}/gtest/googlemock)
set(GMOCK_INCLUDE ${GMOCK_ROOT}/include)
set(GMOCK_SRC ${GMOCK_ROOT}/src)

file(GLOB SRC_FILES
    extra_std.h
    ${INCLUDE_DIR}/*.h
    ${PRIVATE_INCLUDE_DIR}/*.h
    ${ESTD_TESTS_DIR}/*.h
    ${ESTD_TESTS_DIR}/*.cpp
    ${GTEST_SRC}/gtest-all.cc
    ${GMOCK_SRC}/gmock-all.cc
)

include_directories(${INCLUDE_DIR} ${GTEST_INCLUDE} ${GTEST_ROOT} ${GMOCK_INCLUDE} ${GMOCK_ROOT})

add_executable(${PROJECT_NAME} ${SRC_FILES})

set(CXX_STANDARD_REQUIRED true)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
