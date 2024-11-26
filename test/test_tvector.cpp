#include "utmatrix.h"

#include <gtest.h>

// Тест на создание вектора с положительной длиной
TEST(TDynamicVector, can_create_vector_with_positive_length) {
    TDynamicVector<int> v; // Объявление вектора
    ASSERT_NO_THROW(v = TDynamicVector<int>(7)); // Проверка, что создание вектора с длиной 7 не вызывает исключений
}

// Тест на попытку создания слишком большого вектора
TEST(TDynamicVector, cannot_create_excessively_large_vector) {
    ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 2)); // Проверка, что создание вектора больше максимального размера вызывает исключение
}

// Тест на создание вектора с отрицательной длиной
TEST(TDynamicVector, throws_exception_when_creating_vector_with_negative_length) {
    ASSERT_ANY_THROW(TDynamicVector<int> v(-3)); // Проверка, что создание вектора с отрицательной длиной вызывает исключение
}

// Тест на создание копии существующего вектора
TEST(TDynamicVector, can_create_a_copy_of_existing_vector) {
    TDynamicVector<int> original(12); // Создание оригинального вектора
    ASSERT_NO_THROW(TDynamicVector<int> copy(original)); // Проверка, что копирование вектора не вызывает исключений
}

// Тест на соответствие скопированного вектора исходному вектору
TEST(TDynamicVector, copied_vector_matches_source_vector) {
    TDynamicVector<int> original(6);
    original[2] = 5;
    original[4] = 15;
    TDynamicVector<int> copy(original); // Копирование вектора
    EXPECT_EQ(original, copy); // Проверка, что оригинальный и скопированный векторы равны
}

// Тест на то, что скопированный вектор имеет собственное пространство памяти
TEST(TDynamicVector, copied_vector_has_its_own_memory_space) {
    TDynamicVector<int> original(6);
    original[3] = 8;
    TDynamicVector<int> copy(original); // Копирование вектора
    copy[3] = 28;
    EXPECT_NE(original[3], copy[3]); // Проверка, что значения в оригинальном и скопированном векторах различны
}

// Тест на корректное получение размера вектора
TEST(TDynamicVector, can_retrieve_vector_size_correctly) {
    TDynamicVector<int> v(5);
    EXPECT_EQ(5, v.size()); // Проверка, что размер вектора равен 5
}

// Тест на установку и получение элемента вектора
TEST(TDynamicVector, can_set_and_get_vector_element_correctly) {
    TDynamicVector<int> v(5);
    v[1] = 9;
    EXPECT_EQ(9, v[1]); // Проверка, что элемент с индексом 1 равен 9
}

// Тест на попытку доступа к отрицательному индексу
TEST(TDynamicVector, throws_exception_on_accessing_negative_index) {
    TDynamicVector<int> v(5);
    ASSERT_ANY_THROW(v[-1]); // Проверка, что доступ к отрицательному индексу вызывает исключение
}

// Тест на попытку доступа к индексу вне границ
TEST(TDynamicVector, throws_exception_on_accessing_out_of_bounds_index) {
    TDynamicVector<int> v(5);
    ASSERT_ANY_THROW(v[5]); // Проверка, что доступ к индексу 5 (вне границ) вызывает исключение
}

// Тест на присвоение вектора самому себе без ошибок
TEST(TDynamicVector, can_assign_vector_to_itself_without_error) {
    TDynamicVector<int> v(6);
    ASSERT_NO_THROW(v = v); // Проверка, что присвоение самого себя не вызывает исключений
}

// Тест на то, что оператор присваивания обновляет размер вектора
TEST(TDynamicVector, assignment_operator_updates_vector_size) {
    size_t size1 = 6, size2 = 12;
    TDynamicVector<int> v1(size1), v2(size2);
    v1 = v2; // Присвоение вектора v2 в v1
    EXPECT_EQ(v1.size(), size2); // Проверка, что размер v1 теперь равен размеру v2
}

// Тест на успешное присвоение векторов разного размера
TEST(TDynamicVector, can_assign_vectors_of_different_sizes_successfully) {
    size_t size1 = 6, size2 = 12;
    TDynamicVector<int> v1(size1), v2(size2);
    v2[7] = 10;
    v1 = v2; // Присвоение вектора v2 в v1
    EXPECT_EQ(v1[7], 10); // Проверка, что элемент с индексом 7 в v1 равен 10
}

// Тест на идентичность содержимого равных векторов
TEST(TDynamicVector, equal_vectors_are_identical_in_content) {
    size_t size = 6;
    TDynamicVector<int> v1(size), v2(size);
    v1[4] = 20;
    v2[4] = 20;
    EXPECT_EQ(v1, v2); // Проверка, что равные векторы имеют одинаковое содержимое
}

// Тест на истинность сравнения идентичных векторов
TEST(TDynamicVector, identical_vector_comparison_is_true) {
    size_t size = 6;
    TDynamicVector<int> v(size);
    v[4] = 4;
    EXPECT_EQ(v, v); // Проверка, что вектор равен самому себе
}

// Тест на неравенство векторов разного размера
TEST(TDynamicVector, vectors_with_different_sizes_are_not_equal) {
    size_t size1 = 6, size2 = 12;
    TDynamicVector<int> v1(size1), v2(size2);
    EXPECT_NE(v1, v2); // Проверка, что векторы разного размера не равны
}

// Тест на сложение скаляра с элементами вектора
TEST(TDynamicVector, can_add_scalar_to_vector_elements_correctly) {
    size_t size = 4;
    TDynamicVector<int> v1(size), v2(size);
    v1[0] = 2;
    v1[1] = 3;
    v1[2] = 4;
    v2[0] = 7;
    v2[1] = 8;
    v2[2] = 9;
    EXPECT_EQ(v1 + 5, v2); // Проверка, что v1 + 5 равно v2
}

// Тест на вычитание скаляра из элементов вектора
TEST(TDynamicVector, can_subtract_scalar_from_vector_elements_correctly) {
    size_t size = 4;
    TDynamicVector<int> v1(size), v2(size);
    v1[0] = 6;
    v1[1] = 7;
    v1[2] = 8;
    v2[0] = 1;
    v2[1] = 2;
    v2[2] = 3;
    EXPECT_EQ(v1 - 5, v2); // Проверка, что v1 - 5 равно v2
}

// Тест на умножение элементов вектора на скаляр
TEST(TDynamicVector, can_multiply_vector_elements_by_scalar_correctly) {
    size_t size = 4;
    TDynamicVector<int> v1(size), v2(size);
    v1[0] = 2;
    v1[1] = 3;
    v1[2] = 4;
    v2[0] = 4;
    v2[1] = 6;
    v2[2] = 8;
    EXPECT_EQ(v1 * 2, v2); // Проверка, что v1 * 2 равно v2
}

// Тест на сложение векторов одинакового размера
TEST(TDynamicVector, can_add_vectors_of_same_size_correctly) {
    size_t size = 4;
    TDynamicVector<int> v1(size), v2(size), expected_v(size);
    v1[0] = 2;
    v1[1] = 3;
    v1[2] = 4;
    v2[0] = 6;
    v2[1] = 5;
    expected_v[0] = 8;
    expected_v[1] = 8;
    EXPECT_EQ(v1 + v2, expected_v); // Проверка, что сумма v1 и v2 равна expected_v
}

// Тест на невозможность сложения векторов разного размера
TEST(TDynamicVector, cannot_add_vectors_of_different_sizes) {
    size_t size1 = 3, size2 = 5;
    TDynamicVector<int> v1(size1), v2(size2);
    ASSERT_ANY_THROW(v1 + v2); // Проверка, что сложение векторов разного размера вызывает исключение
}

// Тест на вычитание векторов одинакового размера
TEST(TDynamicVector, can_subtract_vectors_of_same_size_correctly) {
    size_t size = 4;
    TDynamicVector<int> v1(size), v2(size), expected_v(size);
    v1[1] = 4;
    v1[2] = 5;
    v2[0] = 10;
    v2[2] = 8;
    expected_v[0] = -10;
    expected_v[1] = 4;
    expected_v[2] = -3;
    EXPECT_EQ(v1 - v2, expected_v); // Проверка, что разность v1 и v2 равна expected_v
}

// Тест на невозможность вычитания векторов разного размера
TEST(TDynamicVector, cannot_subtract_vectors_of_different_sizes) {
    size_t size1 = 3, size2 = 5;
    TDynamicVector<int> v1(size1), v2(size2);
    ASSERT_ANY_THROW(v1 - v2); // Проверка, что вычитание векторов разного размера вызывает исключение
}

// Тест на умножение векторов одинакового размера
TEST(TDynamicVector, can_multiply_vectors_of_same_size_correctly) {
    size_t size = 4;
    TDynamicVector<int> v1(size), v2(size);
    v1[1] = 2;
    v1[2] = 3;
    v2[0] = 4;
    v2[2] = 5;
    int expected_result = 15;
    EXPECT_EQ(v1 * v2, expected_result); // Проверка, что произведение v1 и v2 равно expected_result
}

// Тест на невозможность умножения векторов разного размера
TEST(TDynamicVector, cannot_multiply_vectors_of_different_sizes) {
    size_t size1 = 3, size2 = 5;
    TDynamicVector<int> v1(size1), v2(size2);
    ASSERT_ANY_THROW(v1 * v2); // Проверка, что умножение векторов разного размера вызывает исключение
}

