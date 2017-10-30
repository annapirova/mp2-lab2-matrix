#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);
  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m(5);
	m[1][1] = 2;
	TMatrix<int> n(m);
	EXPECT_EQ(m, n);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m(5);
	m[1][1] = 12;
	TMatrix<int> n(m);
	n[1][1] = 14;
	EXPECT_NE(&m[0], &n[0]);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(5);
	EXPECT_EQ(5, m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
 	TMatrix<int> m(5);
	m[1][1] = 25;
	EXPECT_EQ(25, m[1][1]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
 	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[-1][-1]=2);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[8][1] = 7);
	ASSERT_ANY_THROW(m[2][6] = 3);

}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m(6);
	m[0][0] = 2;
	m[1][1] = 12;
	m=m;
	EXPECT_EQ(m, m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> m(2), n(2);
	m[0][0] = 2;
	m[1][1] = 7;
	n[0][0] = 12;
	n[1][1] = 4;
	m=n;
	EXPECT_EQ(m, n);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> m(2), n(8);
	m[1][1] = 54;
	m = n;
	EXPECT_EQ(8, m.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> m(2), n(8);
	m[0][0] = 2;
	m[1][1] = 54;
	n=m;
	EXPECT_EQ(m, n);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m(5), n(5);
	m[0][0] = 2;
	m[1][1] = 54;
	n[0][0] = 2;
	n[1][1] = 54;
	EXPECT_TRUE( m == n);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m(5);
	m[1][1] = 4;
	EXPECT_TRUE(m == m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m(5), n(8);
	m[1][1]=8;
	n[1][1]=8;
	EXPECT_TRUE(m!=n);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m(5), n(5);
	m[1][1] = -2;
	n[1][1] = 9;
	TMatrix<int> c(m + n);
	EXPECT_EQ(c[1][1], 7);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m(5), n(8);
	ASSERT_ANY_THROW(m + n);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m(5), n(5);
	m[1][1] = -2;
	n[1][1] = 9;
	TMatrix<int> c(m - n);
	EXPECT_EQ(c[1][1], -11);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m(5), n(8);
	ASSERT_ANY_THROW(m - n);
}

