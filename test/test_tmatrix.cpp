#include "../include/tmatrix.h"

#include "../gtest/gtest.h"

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
  TDynamicMatrix<int> m(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 0;
    }
  }
  TDynamicMatrix<int> mc(m);
  EXPECT_EQ(mc,m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 0;
    }
  }
  TDynamicMatrix<int> mc(m);
  mc[1][7] = 8;
  EXPECT_NE(mc,m);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(9);
  EXPECT_EQ(9, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 0;
    }
  }
  m[8][5] = 8999;
  EXPECT_EQ(8999,m[8][5]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(9);
  ASSERT_ANY_THROW(m[-1][5]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(9);
  ASSERT_ANY_THROW(m[111111][5]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 0;
    }
  }
  TDynamicMatrix<int> mr(m);
  m = m;
  EXPECT_EQ(mr,m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> m1(9);
  TDynamicMatrix<int> mr(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 0;
      m1[i][j] = 2;
      mr[i][j] = 2;
    }
  }
  m = m1;
  EXPECT_EQ(mr,m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> m1(11);
  m = m1;
  EXPECT_EQ(11,m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> m1(11);
  TDynamicMatrix<int> mr(11);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 0;
    }
  }
  for (int i = 0;i<11;i++)
  {
    for (int j = 0;j<11;j++)
    {
      m[i][j] = 0;
    }
  }
  m = m1;
  EXPECT_EQ(mr,m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> m1(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 0;
      m1[i][j] = 0;
    }
  }
  if (m1 == m)
  {SUCCEED();}
  else
  {ADD_FAILURE();}
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 0;
    }
  }
  if (m == m)
  {SUCCEED();}
  else
  {ADD_FAILURE();}
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> m1(11);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 0;
    }
  }
  for (int i = 0;i<11;i++)
  {
    for (int j = 0;j<11;j++)
    {
      m1[i][j] = 0;
    }
  }
  EXPECT_NE(m,m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> m1(9);
  TDynamicMatrix<int> mr(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 2;
      m1[i][j] = 99;
      mr[i][j] = 101;
    }
  }
  EXPECT_EQ(mr,m+m1);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> m1(11);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 2;
    }
  }
  for (int i = 0;i<11;i++)
  {
    for (int j = 0;j<11;j++)
    {
      m[i][j] = 5;
    }
  }
  ASSERT_ANY_THROW(m+m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> m1(9);
  TDynamicMatrix<int> mr(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 2;
      m1[i][j] = 99;
      mr[i][j] = 97;
    }
  }
  EXPECT_EQ(mr,m1 - m);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> m1(11);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 2;
    }
  }
  for (int i = 0;i<11;i++)
  {
    for (int j = 0;j<11;j++)
    {
      m[i][j] = 5;
    }
  }
  ASSERT_ANY_THROW(m-m1);
}
TEST(TDynamicMatrix, can_multiply_matrixes_with_scalars)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> mr(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 2;
      mr[i][j] = 18;
    }
  }
  EXPECT_EQ(mr,m*9);
}

TEST(TDynamicMatrix, can_multiply_matrixes_with_vectors_with_equal_sizes)
{
  TDynamicMatrix<int> m(9);
  TDynamicVector<int> v(9);
  TDynamicVector<int> vr(9);
  for (int i = 0;i<9;i++)
  {
    v[i] = 5;
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 2;
    }
  }
  for (int i = 0;i<9;i++)
  {
    vr[i] = (2*5) * 9;
  }
  EXPECT_EQ(vr,m*v);
}

TEST(TDynamicMatrix, cant_multiply_matrixes_with_vectors_with_different_sizes)
{
  TDynamicMatrix<int> m(9);
  TDynamicVector<int> v(11);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 2;
    }
  }
  for (int i = 0;i<11;i++)
  {
    v[i] = 3;
  }
  ASSERT_ANY_THROW(m*v);
}

TEST(TDynamicMatrix, can_multiply_matrixes_with_equal_sizes)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> m2(9);
  TDynamicMatrix<int> mr(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 2;
      m2[i][j] = 9;
    }
  }
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      mr[i][j] = (2*9)*9;
    }
  }
  EXPECT_EQ(mr,m*m2);
}
TEST(TDynamicMatrix, cant_multiply_matrixes_with_different_sizes)
{
  TDynamicMatrix<int> m(9);
  TDynamicMatrix<int> m2(9);
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m[i][j] = 2;
    }
  }
  for (int i = 0;i<9;i++)
  {
    for (int j = 0;j<9;j++)
    {
      m2[i][j] = 789;
    }
  }
  ASSERT_ANY_THROW(m*m2);
}