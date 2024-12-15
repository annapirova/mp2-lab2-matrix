# Создаем статическую библиотеку gtest
add_library(gtest STATIC gtest-all.cc)

# Проверяем, поддерживается ли pthread
find_package(Threads REQUIRED)

# Линкуем с pthread
target_link_libraries(gtest PRIVATE Threads::Threads)
