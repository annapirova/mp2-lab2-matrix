#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}
TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}
TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}
TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}
TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}
TEST(TVector, copied_vector_is_equal_to_source_one)
{   const int size = 2;
	TVector<int> v1(size);
	v1[1] = 100;
	TVector<int> v2(v1);

	EXPECT_EQ(v1, v2);
}
TEST(TVector, copied_vector_has_its_own_memory)
{
	const int size = 2;
	TVector<int> v1(size);
	v1[1] = 100;
	TVector<int> v2(v1);

	EXPECT_NE(&(v1), &(v2));
}
TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}
TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}
TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}
TEST(TVector, throws_when_set_element_with_negative_index)
{	TVector<int> v(2);
	ASSERT_ANY_THROW(v[-3]);
}
TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(2);
	ASSERT_ANY_THROW(v[7]);
}
TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> v(13);
	ASSERT_NO_THROW(v = v);
}
TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> v1(5);
	TVector<int> v2(5);
	for (int i = 0; i < v2.GetSize(); i++)
		v2[i] = i;
	EXPECT_EQ(v2, v1 = v2);
}
TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> v1(13);
	TVector<int> v2(666);
	v2 = v1;
	EXPECT_EQ(13, v2.GetSize());
}
TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> v1(5);
	TVector<int> v2(10);
	for (int i = 0; i < v2.GetSize(); i++)
		v2[i] = i;
	EXPECT_EQ(v2, v1 = v2);;
}
TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> v1(3);
	TVector<int> v2;
	v1[0] = 2;
	v2 = v1;
	EXPECT_EQ(1, v1==v2);
}
TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> v1(3);
	v1[0] = 2;
	EXPECT_EQ(1, v1 == v1);
}
TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> v1(3);
	TVector<int> v2;
	EXPECT_EQ(1, v1 != v2);
}
TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v1(5);
	TVector<int> v2(5);
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i + 55;
		v2[i] = i;
	}
	EXPECT_EQ(v1, v2 + 55);
}
TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v1(5);
	TVector<int> v2(5);
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i;
		v2[i] = i + 55;
	}
	EXPECT_EQ(v1, v2 - 55);
}
TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v1(5);
	TVector<int> v2(5);
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i * 55;
		v2[i] = i;
	}
	EXPECT_EQ(v1, v2 * 55);
}
TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> v1(5);
	TVector<int> v2(5);
	TVector<int> c(5);
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i * 5;
		v2[i] = i - 5;
		c[i] = (i * 5) + (i - 5);
	}
	EXPECT_EQ(c, v1 + v2);
}
TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> v1(5);
	TVector<int> v2(6);
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i * 5;
		v2[i] = i - 5;
	}
	ASSERT_ANY_THROW(v1 + v2);
}
TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> v1(5);
	TVector<int> v2(5);
	TVector<int> c(5);
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i * 5;
		v2[i] = i - 5;
		c[i] = (i * 5) - (i - 5);
	}
	EXPECT_EQ(c, v1 - v2);
}
TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> v1(2);
	TVector<int> v2(3);
	v2[0] = 2;
	ASSERT_ANY_THROW(v1 - v2);
}
TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> v1(5);
	TVector<int> v2(5);
	int c = 0;
	for (int i = 0; i < v1.GetSize(); i++)
	{
		v1[i] = i * 5;
		v2[i] = i - 5;
		c += (i * 5) * (i - 5);
	}
	EXPECT_EQ(c, v1 * v2);
}
TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v1(2);
	TVector<int> v2(3);
	v2[0] = 2;
	ASSERT_ANY_THROW(v1 * v2);
}

