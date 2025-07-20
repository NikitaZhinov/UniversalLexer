cmake_minimum_required(VERSION 3.30)

project(UniversalLexer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

if (WIN32)
	if (CMAKE_BUILD_TYPE STREQUAL Release)
		add_compile_options(/O2)
	endif()
else()
	add_compile_options(-Wall -Wextra)
	if (CMAKE_BUILD_TYPE STREQUAL Release)
		add_compile_options(-O3)
	endif()
endif()

add_library(${PROJECT_NAME} STATIC "include/lexer/lexer.h" "src/lexer.cpp" "include/lexer/token.h" "src/token.cpp")

find_package(Doxygen REQUIRED)
if(DOXYGEN_FOUND)
	message("Doxygen build started")
	add_custom_target(UniversalLexerDoxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM)
	message("Doxygen build finished")
else()
    message("Doxygen need to be installed to generate the doxygen documentation")
endif()

include(CTest)
enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME}Tests "test/test.cpp" "test/lexer-test.cpp")
target_link_libraries(${PROJECT_NAME}Tests PRIVATE GTest::gtest GTest::gtest_main
                                                   GTest::gmock GTest::gmock_main)
target_link_libraries(${PROJECT_NAME}Tests PRIVATE ${PROJECT_NAME})

add_test(NAME AllTestsIn${PROJECT_NAME} COMMAND ${PROJECT_NAME}Tests)
