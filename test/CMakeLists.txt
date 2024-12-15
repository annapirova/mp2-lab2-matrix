find_package(Threads REQUIRED)

add_executable(TestMain test_main.cpp)
add_executable(TestTMatrix test_tmatrix.cpp)
add_executable(TestTVector test_tvector.cpp)

target_link_libraries(TestMain PRIVATE gtest_main Threads::Threads)
target_link_libraries(TestTMatrix PRIVATE gtest_main Threads::Threads)
target_link_libraries(TestTVector PRIVATE gtest_main Threads::Threads)

enable_testing()
add_test(NAME TestMain COMMAND TestMain)
add_test(NAME TestTMatrix COMMAND TestTMatrix)
add_test(NAME TestTVector COMMAND TestTVector)
