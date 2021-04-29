//
// Created by dym on 29.04.2021.
//
#include <fromString.hpp>
#include <gtest/gtest.h>

TEST(fromString, _int8)
{
  using T= int8_t;
  ASSERT_EQ(fromString<T>("127"), 127);
  ASSERT_THROW(fromString<T>("128"), std::out_of_range);
  ASSERT_EQ(fromString<T>("-127"), -127); /// -128    INT8_MIN
  ASSERT_THROW(fromString<T>("-128"), std::out_of_range);
}
TEST(fromString, _int64)
{
  using T= int64_t;
  ASSERT_EQ(fromString<T>("9223372036854775807"), INT64_MAX);
  ASSERT_THROW(fromString<T>("9223372036854775808"), std::out_of_range);
  ASSERT_EQ(fromString<T>("-9223372036854775807"), std::numeric_limits<T>::min()+1);
  ASSERT_THROW(fromString<T>("-9223372036854775808"), std::out_of_range);
}
TEST(fromString, _uint8)
{
  ASSERT_EQ(fromString<uint8_t>("0"), 0);
  ASSERT_EQ(fromString<uint8_t>("255"), 255);
  ASSERT_THROW(fromString<uint8_t>("256"), std::out_of_range);
  ASSERT_THROW(fromString<uint8_t>("-1"), std::out_of_range);
}
TEST(fromString, notNumber)
{
  using T= uint8_t;
  ASSERT_THROW(fromString<T>(""), std::invalid_argument);
  ASSERT_THROW(fromString<T>("+"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("-"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("abc"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("+-"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("-+"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("1.2"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("1,2"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("10%"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("$12"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("1/2"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("12-"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("12+"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("(12)"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("1>2"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("12abc"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("-12abc"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("   12abc"), std::invalid_argument);
  ASSERT_THROW(fromString<T>("   -12abc"), std::invalid_argument);
}
TEST(fromString, possibleFromat)
{
  using T= int8_t;
  ASSERT_EQ(fromString<T>("1"), 1);
  ASSERT_EQ(fromString<T>("01"), 1);
  ASSERT_EQ(fromString<T>("-1"), -1);
  ASSERT_EQ(fromString<T>("0"), 0);
  ASSERT_EQ(fromString<T>("+12   "), 12);
  ASSERT_EQ(fromString<T>("   +12   "), 12);
  ASSERT_EQ(fromString<T>("12   "), 12);
  ASSERT_EQ(fromString<T>("-12   "), -12);
}