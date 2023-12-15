file(GLOB BASE_EXAMPLE_SOURCES ./*.cpp)

foreach (base_example_source ${BASE_EXAMPLE_SOURCES})
    cmake_path(GET base_example_source STEM base_example_name)
    add_executable(${base_example_name} ${base_example_source})
    target_link_libraries(${base_example_name} base)
endforeach ()