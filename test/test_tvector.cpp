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
    TDynamicVector<int> v(5);
    for (int i = 0; i < 5; i++) {
       v[i] = i;
    }
    TDynamicVector<int> vc(v);
    EXPECT_EQ(vc, v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(3);
    v[0] = 1;
    TDynamicVector<int> vc(v);
    vc[0] = 2;

    EXPECT_NE(v[0], vc[0]);
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
    TDynamicVector<int> v(7);
    ASSERT_ANY_THROW(v[-1] = 3);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(7);
    ASSERT_ANY_THROW(v[8] = 3);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(3);
    v[0] = 1;
    ASSERT_NO_THROW(v= v);
    EXPECT_EQ(1, v[0]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v1(3),v2(3);
    v1[0] = 1;
    ASSERT_NO_THROW(v2 = v1);
    EXPECT_EQ(1, v2[0]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v1(3), v2(5);
    v1 = v2;
    EXPECT_EQ(v1.size(), 5);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v1(3), v2(5);
    v1[0] = 1;
    ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v1(3), v2(3);
    v1[0] = v2[0] = 1;
    EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v1(3);
    v1[0] = 1;
    v1[1] = 2;
    v1[2] = 3;
    EXPECT_TRUE(v1 == v1);

}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v1(2), v2(6);
    EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int>v(5);
    int scalar=10;
    for (int i = 0; i < 5; i++) {
        v[i] = 0;
        v[i] = v[i] + scalar;
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(v[i], scalar) << "uncorrect by index [" << i << "]";
    }
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int>v(5);
    int scalar = 10;
    for (int i = 0; i < 5; i++) {
        v[i] = 10;
        v[i] = v[i] - scalar;
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(v[i], 0) << "uncorrect by index [" << i << "]";
    }
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int>v(5);
    int scalar = 0;
    for (int i = 0; i < 5; i++) {
        v[i] = 10;
        v[i] = v[i] * scalar;
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(v[i], 0) << "uncorrect by index [" << i << "]";
    }
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int>v1(5),v2(5);
    for (int i = 0; i < 5; i++) {
        v1[i] = 1;
    }
    v2 = v1;
    v2 = v2 + v1;
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(v2[i], 2) << "uncorrect by index [" << i << "]";
    }
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int>v1(2), v2(5);
    ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int>v1(5), v2(5);
    for (int i = 0; i < 5; i++) {
        v1[i] = 1;
    }
    v2 = v1;
    v2 = v2 - v1;
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(v2[i], 0);
    }
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int>v1(2), v2(5);
    ASSERT_ANY_THROW(v1 - v2);
}


TEST(TDynamicVector, can_multiply_vectors_with_equal_size) {
    TDynamicVector<int> v1(3), v2(3);

    
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    
    int expected = 1 * 4 + 2 * 5 + 3 * 6;
    EXPECT_EQ(v1*v2, expected);
}


TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size) {
    TDynamicVector<int> v1(3), v2(4); 
    ASSERT_ANY_THROW(v1*v2);
}
