#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(5);
	v1[1] = 1;
	v1[3] = 3; 
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(5);
	v1[2] = 2;
	TDynamicVector<int> v2(v1);
	v2[2] = 22;
	EXPECT_FALSE(v1[2] == v2[2]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(4);
  ASSERT_ANY_THROW(v[-4]);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(4);
  ASSERT_ANY_THROW(v[4]);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(5);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	size_t size = 5;
	TDynamicVector<int> v1(size), v2(size);
	v1[3] = 3;
	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	size_t size1 = 5, size2 = 10;
	TDynamicVector<int> v1(size1), v2(size2);
	v1 = v2;
	EXPECT_EQ(v1.size(), size2);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	size_t size1 = 5, size2 = 10;
	TDynamicVector<int> v1(size1), v2(size2);
	v2[5] = 5;
	v1 = v2;
	EXPECT_EQ(v1[5], 5);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	size_t size = 5;
	TDynamicVector<int> v1(size), v2(size);
	v1[3] = 10;
	v2[3] = 10;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	size_t size = 5;
	TDynamicVector<int> v(size);
	v[3] = 3;
	EXPECT_EQ(v, v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	size_t size1 = 5, size2 = 10;
	TDynamicVector<int> v1(size1), v2(size2);
	EXPECT_NE(v1, v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	size_t size = 3;
	TDynamicVector<int> v1(size), v2(size);
	v1[0] = 1; 
	v1[1] = 2; 
	v1[2] = 3; 
	// 1 2 3
	v2[0] = 6;
	v2[1] = 7;
	v2[2] = 8;
	// 6 7 8
	EXPECT_EQ(v1 + 5, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	size_t size = 3;
	TDynamicVector<int> v1(size), v2(size);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	// 1 2 3
	v2[0] = -4;
	v2[1] = -3;
	v2[2] = -2; 
	// -4 -3 -2
	EXPECT_EQ(v1 - 5, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	size_t size = 3;
	TDynamicVector<int> v1(size), v2(size);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	// 1 2 3
	v2[0] = 3;
	v2[1] = 6;
	v2[2] = 9;
	// 3 6 9
	EXPECT_EQ(v1 * 3, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	size_t size = 3;
	TDynamicVector<int> v1(size), v2(size), exp_v(size);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	// 1 2 3
	v2[0] = 7;
	v2[2] = 5;
	// 7 0 5
	exp_v[0] = 8;
	exp_v[1] = 2;
	exp_v[2] = 8;
	// 8 5 8
	EXPECT_EQ(v1 + v2, exp_v);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	size_t size1 = 2, size2 = 3;
	TDynamicVector<int> v1(size1), v2(size2);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	size_t size = 3;
	TDynamicVector<int> v1(size), v2(size), exp_v(size);
	v1[1] = 1;
	v1[2] = 2;
	// 0 1 3
	v2[0] = 5;
	v2[2] = 6;
	// 5 0 6
	exp_v[0] = -5;
	exp_v[1] = 1;
	exp_v[2] = -4;
	// -5 1 -4
	EXPECT_EQ(v1 - v2, exp_v);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	size_t size1 = 2, size2 = 3;
	TDynamicVector<int> v1(size1), v2(size2);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	size_t size = 3;
	TDynamicVector<int> v1(size), v2(size);
	v1[1] = 1;
	v1[2] = 2;
	// 0 1 2
	v2[0] = 5;
	v2[2] = 6;
	// 5 0 6
	int tmp = 12;
	EXPECT_EQ(v1 * v2, tmp);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	size_t size1 = 2, size2 = 3;
	TDynamicVector<int> v1(size1), v2(size2);
	ASSERT_ANY_THROW(v1 * v2);
}
