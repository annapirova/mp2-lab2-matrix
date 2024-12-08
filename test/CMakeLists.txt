set(target ${MTRX_TESTS})

file(GLOB hdrs "*.h")
file(GLOB srcs "test_main.cpp test_tmatrix.cpp test_tvector.cpp")

add_executable (${target} "test_main.cpp" "test_tmatrix.cpp" "test_tvector.cpp")

target_link_libraries(${target} gtest)