#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      m[i][j] = i + j;
    }
  }
  TDynamicMatrix<int> mc(m);
  EXPECT_EQ(mc, m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 1;
  TDynamicMatrix<int> mc(m);
  mc[0][0] = 2;

  EXPECT_NE(m[0][0], mc[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(5);
  EXPECT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(7);
  m[2][4] = 3;
  EXPECT_EQ(3, m[2][4]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(7);
  ASSERT_ANY_THROW(m[-1][0] = 3);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(7);
  ASSERT_ANY_THROW(m[8][0] = 3);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 1;
  ASSERT_NO_THROW(m = m);
  EXPECT_EQ(1, m[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(3), m2(3);
  m1[0][0] = 1;
  ASSERT_NO_THROW(m2 = m1);
  EXPECT_EQ(1, m2[0][0]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(3), m2(5);
  m1 = m2;
  EXPECT_EQ(m1.size(), 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m1(3), m2(5);
  m1[0][0] = 1;
  ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(3), m2(3);
  m1[0][0] = m2[0][0] = 1;
  EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      m[i][j] = i + j;
    }
  }
  EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(3), m2(4);
  EXPECT_FALSE(m1 == m2);
}


TEST(TDynamicMatrix, can_add_matrices_with_equal_size) {
    TDynamicMatrix<int> m1(3), m2(3);


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m1[i][j] = i + j;
        }
    }


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m2[i][j] = i * j;
        }
    }

 
    TDynamicMatrix<int> expected(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            expected[i][j] = m1[i][j] + m2[i][j];
        }
    }


    TDynamicMatrix<int> result;
    ASSERT_NO_THROW(result = m1 + m2);

   
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(result[i][j], expected[i][j]) << "uncorrect by indexs [" << i << "][" << j << "]";
        }
    }
}
TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(3), m2(4);
  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(3), m2(3);


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m1[i][j] = i + j;
        }
    }


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m2[i][j] = i * j;
        }
    }


    TDynamicMatrix<int> expected(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            expected[i][j] = m1[i][j] - m2[i][j];
        }
    }


    TDynamicMatrix<int> result;
    ASSERT_NO_THROW(result = m1 - m2);


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(result[i][j], expected[i][j]) << "uncorrect by indexs [" << i << "][" << j << "]";
        }
    }
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m1(3), m2(4);
  ASSERT_ANY_THROW(m1 - m2);
}
TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size) {
    TDynamicMatrix<int> A(2), B(2);
    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 3; A[1][1] = 4;

    
    B[0][0] = 5; B[0][1] = 6;
    B[1][0] = 7; B[1][1] = 8;

    
    TDynamicMatrix<int> expected(2);
    expected[0][0] = 19;  expected[0][1] = 22;  // 1*5 + 2*7=19, 1*6 + 2*8=22
    expected[1][0] = 43;  expected[1][1] = 50;  // 3*5 + 4*7=43, 3*6 + 4*8=50

    TDynamicMatrix<int> result ;
    ASSERT_NO_THROW(result = A * B);
    for (size_t i = 0; i < result.size(); ++i) {
        for (size_t j = 0; j < result.size(); ++j) {
            EXPECT_EQ(result[i][j], expected[i][j])<<"uncorrect by index ["<<i<<"]["<<j<<"]";
        }
    }
}
TEST(TDynamicMatrix, cant_multiply_matrices_with_different_sizes) {
    TDynamicMatrix<int> A(2),B(3);
    ASSERT_ANY_THROW(A * B);
}