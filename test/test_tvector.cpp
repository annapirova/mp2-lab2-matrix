#include "../include/tmatrix.h"

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
  TDynamicVector<int> v(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 0;
  }
  v[4] = 7;
  TDynamicVector<int> vc(v);
  ASSERT_EQ(v,vc);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 0;
  }
  TDynamicVector<int> vc(v);
  v[5] = 3;
  ASSERT_NE(vc,v);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(6);
  ASSERT_ANY_THROW(v.at(-5));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(100000009);
  ASSERT_ANY_THROW(v.at(100000001));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
  }
  TDynamicVector<int> v2(v);
  v = v;
  EXPECT_EQ(v2,v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> v1(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
    v1[i] = 66;
  }
  TDynamicVector<int> vr(v);
  v1 = v;
  EXPECT_EQ(vr,v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> v1(11);
  TDynamicVector<int> vr(11);
  v = v1;
  EXPECT_EQ(vr.size(),v.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> v1(11);
  TDynamicVector<int> vr(11);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
  }
  for (int b = 0;b<11;b++)
  {
    v1[b] = 7;
    vr[b] = 7;
  }
  v = v1;
  EXPECT_EQ(vr,v);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> v1(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
    v1[i] = 5;
  }
  if (v1 == v)
  {
    SUCCEED();
  }
  else{ADD_FAILURE();}
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
  }
  if (v == v)
  {
    SUCCEED();
  }
  else{ADD_FAILURE();}
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> v1(10);
  if (v1 != v)
  {
    SUCCEED();
  }
  else{ADD_FAILURE();}
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> vr(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
    vr[i] = 7;
  }
  EXPECT_EQ(vr,v+2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> vr(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
    vr[i] = 3;
  }
  EXPECT_EQ(vr,v-2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> vr(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
    vr[i] = 10;
  }
  EXPECT_EQ(vr,v*2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> v1(7);
  TDynamicVector<int> vr(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
    v1[i] = 10;
    vr[i] = 15;
  }
  EXPECT_EQ(vr,v+v1);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> v1(10);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
  }
  for (int i = 0;i<10;i++)
  {
    v1[i] = 9;
  }
  ASSERT_ANY_THROW(v+v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> v1(7);
  TDynamicVector<int> vr(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 10;
    v1[i] = 9;
    vr[i] = 1;
  }
  EXPECT_EQ(vr,v-v1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> v1(10);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
  }
  for (int i = 0;i<10;i++)
  {
    v1[i] = 9;
  }
  ASSERT_ANY_THROW(v-v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> v1(7);
  for (int i = 0;i<7;i++)
  {
    v[i] = 10;
    v1[i] = 9;
  }
  EXPECT_EQ(630,v*v1);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(7);
  TDynamicVector<int> v1(10);
  for (int i = 0;i<7;i++)
  {
    v[i] = 5;
  }
  for (int i = 0;i<10;i++)
  {
    v1[i] = 9;
  }
  ASSERT_ANY_THROW(v*v1);
}

