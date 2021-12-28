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

TEST(TestMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> a(10);
	TMatrix<int> b = a;
	EXPECT_EQ(a, b);
}

TEST(TestMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> a(10);
	TMatrix<int> b = a;
	a[3][4] = 2;
	EXPECT_NE(a, b);
}

TEST(TestMatrix, can_get_size)
{
	TMatrix<int> v(5);
	EXPECT_EQ(5, v.GetSize());
}

TEST(TestMatrix, can_set_and_get_element)
{
	TMatrix<int> v(2);
	v[0][0] = 2;
	EXPECT_EQ(2, v[0][0]);
}

TEST(TestMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> a(5);
	ASSERT_ANY_THROW(a[-2][-2] = 2);
}

TEST(TestMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> a(5);
	ASSERT_ANY_THROW(a[7][9] = 2);
}

TEST(TestMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> a(5);
	TMatrix<int> b(5);
	b[0][0] = 2;
	a[0][0] = 2;
	a = a;
	EXPECT_EQ(a, b);
}

TEST(TestMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> a(5);
	TMatrix<int> b(5);
	a[1][1] = 2;
	b = a;
	EXPECT_EQ(a, b);
}

TEST(TestMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> a(3);
	TMatrix<int> b(7);
	a = b;
	EXPECT_EQ(a.GetSize(), 7);
}

TEST(TestMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> a(5);
	EXPECT_TRUE(a == a);
}

TEST(TestMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> a(4);
	TMatrix<int> b(5);
	EXPECT_TRUE(a != b);
}

TEST(TestMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> a(2);
	a[0][0] = 1; a[0][1] = 1; a[1][1] = 1;
	TMatrix<int> b(2);
	b[0][0] = 2; b[0][1] = 2; b[1][1] = 2;
	TMatrix<int> c(2);
	c[0][0] = 3; c[0][1] = 3; c[1][1] = 3;

	EXPECT_EQ(a + b, c);
}

TEST(TestMatrix, cant_add_matrices_with_not_equal_size)
{
	TVector<int> a(2);
	TVector<int> b(3);
	ASSERT_ANY_THROW(a = a + b;);
}


