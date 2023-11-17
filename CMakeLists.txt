cmake_minimum_required(VERSION 3.26)
project(codebase
        VERSION 0.1.0
        DESCRIPTION ""
        HOMEPAGE_URL "https://github.com/GzIrYsz/c-codebase"
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571 # v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB SRC_DIRS src/*)
foreach (src_dir ${SRC_DIRS})
    add_subdirectory(${src_dir})
endforeach ()

file(GLOB TEST_DIRS tests/*)
foreach (test_dir ${TEST_DIRS})
    add_subdirectory(${test_dir})
endforeach ()

file(GLOB EXAMPLE_DIRS examples/*)
foreach (example_dir ${EXAMPLE_DIRS})
    add_subdirectory(${example_dir})
endforeach ()