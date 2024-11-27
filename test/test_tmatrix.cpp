#include "utmatrix.h" 

#include <gtest.h> 

// Функция для создания матрицы заданного размера
TDynamicMatrix<int> createMatrix(size_t size) {
    return TDynamicMatrix<int>(size);
}

// Функция для заполнения матрицы значениями по заданным индексам
void fillMatrix(TDynamicMatrix<int>& m, const std::vector<std::pair<size_t, size_t>>& indices, int value) {
    for (const auto& index : indices) {
        m[index.first][index.second] = value; // Устанавливаем значение в указанные индексы
    }
}

// Тест на создание матрицы с положительной длиной
TEST(TDynamicMatrix, can_create_matrix_with_positive_length) {
    ASSERT_NO_THROW(createMatrix(5)); // Проверяем, что создание матрицы не вызывает исключений
}

// Тест на попытку создания слишком большой матрицы
TEST(TDynamicMatrix, cant_create_too_large_matrix) {
    ASSERT_ANY_THROW(createMatrix(MAX_MATRIX_SIZE + 1)); // Проверяем, что выбрасывается исключение
}

// Тест на попытку создания матрицы с отрицательной длиной
TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) {
    ASSERT_ANY_THROW(createMatrix(-5)); // Проверяем, что выбрасывается исключение
}

// Тест на создание копии матрицы
TEST(TDynamicMatrix, can_create_copied_matrix) {
    TDynamicMatrix<int> m = createMatrix(5);
    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m)); // Проверяем, что создание копии не вызывает исключений
}

// Тест на равенство исходной матрицы и ее копии
TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) {
    TDynamicMatrix<int> m1 = createMatrix(5);
    fillMatrix(m1, { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4} }, 0); // Заполняем значения
    TDynamicMatrix<int> m2(m1); // Создаем копию
    EXPECT_EQ(m1, m2); // Проверяем, что матрицы равны
}

// Тест на то, что копия матрицы имеет собственную память
TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) {
    TDynamicMatrix<int> m1 = createMatrix(5);
    fillMatrix(m1, { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4} }, 0);
    TDynamicMatrix<int> m2(m1);
    m2[2][3] = 23; // Изменяем значение в копии
    EXPECT_TRUE(!(m1 == m2)); // Проверяем, что матрицы теперь не равны
}

// Тест на получение размера матрицы
TEST(TDynamicMatrix, can_get_size) {
    TDynamicMatrix<int> m = createMatrix(5);
    EXPECT_EQ(5, m.size()); // Проверяем, что размер матрицы равен 5
}

// Тест на установку и получение элемента матрицы
TEST(TDynamicMatrix, can_set_and_get_element) {
    TDynamicMatrix<int> m = createMatrix(3);
    m[1][2] = 12; // Устанавливаем значение
    EXPECT_EQ(m[1][2], 12); // Проверяем, что значение получено корректно
}

// Тест на попытку доступа к элементу с отрицательным индексом
TEST(TDynamicMatrix, throws_when_set_element_with_negative_index) {
    TDynamicMatrix<int> m = createMatrix(5);
    ASSERT_ANY_THROW(m[-1]); // Проверяем, что выбрасывается исключение
}

// Тест на попытку доступа к элементу с слишком большим индексом
TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index) {
    TDynamicMatrix<int> m = createMatrix(5);
    ASSERT_ANY_THROW(m[5]); // Проверяем, что выбрасывается исключение
}

// Тест на присваивание матрицы самой себе
TEST(TDynamicMatrix, can_assign_matrix_to_itself) {
    TDynamicMatrix<int> m = createMatrix(5);
    ASSERT_NO_THROW(m = m); // Проверяем, что присваивание не вызывает исключений
}

// Тест на присваивание матриц одинакового размера
TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) {
    size_t size = 5;
    TDynamicMatrix<int> m1(size), m2(size);
    m1[1][1] = 1; // Устанавливаем значение в первой матрице
    m2 = m1; // Присваиваем
    EXPECT_EQ(m2, m1); // Проверяем, что матрицы равны
}

// Тест на изменение размера матрицы при присваивании
TEST(TDynamicMatrix, assign_operator_change_matrix_size) {
    size_t size1 = 5, size2 = 10;
    TDynamicMatrix<int> m1(size1), m2(size2);
    m1 = m2; // Присваиваем
    EXPECT_EQ(m1.size(), size2); // Проверяем, что размер изменился
}

// Тест на присваивание матриц разного размера
TEST(TDynamicMatrix, can_assign_matrices_of_different_size) {
    size_t size1 = 5, size2 = 10;
    TDynamicMatrix<int> m1(size1), m2(size2);
    m2[3][3] = 3; // Устанавливаем значение в второй матрице
    m1 = m2; // Присваиваем
    EXPECT_EQ(m1, m2); // Проверяем, что матрицы равны
}

// Тест на сравнение равных матриц
TEST(TDynamicMatrix, compare_equal_matrices_return_true) {
    size_t size = 5;
    TDynamicMatrix<int> m1(size), m2(size);
    m2[3][3] = 3; // Устанавливаем значение в одной матрице
    m1[3][3] = 3; // Устанавливаем такое же значение в другой
    EXPECT_EQ(m1, m2); // Проверяем, что матрицы равны
}

// Тест на сравнение матрицы с самой собой
TEST(TDynamicMatrix, compare_matrix_with_itself_return_true) {
    TDynamicMatrix<int> m = createMatrix(5);
    EXPECT_TRUE(m == m); // Проверяем, что матрица равна самой себе
}

// Тест на неравенство матриц разного размера
TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal) {
    size_t size1 = 5, size2 = 10;
    TDynamicMatrix<int> m1(size1), m2(size2);
    EXPECT_FALSE(m1 == m2); // Проверяем, что матрицы не равны
}

// Тест на сложение матриц одинакового размера
TEST(TDynamicMatrix, can_add_matrices_with_equal_size) {
    size_t size = 3;
    TDynamicMatrix<int> m1(size), m2(size), exp(size); // Создаем матрицы
    m1[2][2] = 7;
    m2[2][2] = 8; 
    exp[2][2] = 15; 
    EXPECT_EQ(m1 + m2, exp);
}

// Тест на сложение матриц разного размера
TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size) {
    TDynamicMatrix<int> m1(5), m2(10);
    ASSERT_ANY_THROW(m1 + m2);
}

// Тест на вычитание матриц одинакового размера
TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) {
    size_t size = 3;
    TDynamicMatrix<int> m1(size), m2(size), exp(size);
    m1[2][2] = 7; 
    m2[2][2] = 8; 
    exp[2][2] = -1; 
    EXPECT_EQ(m1 - m2, exp); 
}


TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size) {
    TDynamicMatrix<int> m1(5), m2(10);
    ASSERT_ANY_THROW(m1 - m2); 
}
