include(GoogleTest)

file(GLOB CG_TEST_SOURCES ./*.cpp)
foreach (cg_test_source ${CG_TEST_SOURCES})
    cmake_path(GET cg_test_source STEM cg_test_name)
    add_executable(${cg_test_name} ${cg_test_source})
    target_link_libraries(${cg_test_name} GTest::gtest_main ll)
    gtest_discover_tests(${cg_test_name})
endforeach ()