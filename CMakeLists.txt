cmake_minimum_required(VERSION 3.19)
project(fromString)
set(CMAKE_CXX_STANDARD 20)

set(${PROJECT_NAME}_INCLUDE_DIR impl)

if (googletest_DIR)
    if (NOT EXISTS "${googletest_DIR}")
        message(WARNING "googletest_DIR not exists")
    else ()
        add_subdirectory(${googletest_DIR} gtestBuild)
        add_executable(${PROJECT_NAME}_tests tests.cpp)
        target_link_libraries(${PROJECT_NAME}_tests PUBLIC
                gtest_main)
        target_include_directories(${PROJECT_NAME}_tests PUBLIC
                impl)
        set_target_properties(${PROJECT_NAME}_tests PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    endif ()
endif ()