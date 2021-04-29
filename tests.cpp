//
// Created by dym on 29.04.2021.
//
#include <fromString.hpp>
#include <gtest/gtest.h>

TEST(fromString, _1)
{
  ASSERT_EQ(fromString<int8_t>("1"), 1);
  ASSERT_EQ(fromString<int8_t>("-1"), -1);
  ASSERT_EQ(fromString<int8_t>("0"), 0);
  ASSERT_EQ(fromString<int8_t>("127"), 127);
  ASSERT_THROW(fromString<int8_t>("128"), std::out_of_range);
  ASSERT_EQ(fromString<int8_t>("-127"), -127); /// -128    INT8_MIN
  ASSERT_THROW(fromString<int8_t>("-129"), std::out_of_range);

  ASSERT_EQ(fromString<uint8_t>("1"), 1);
  ASSERT_EQ(fromString<uint8_t>("0"), 0);
  ASSERT_EQ(fromString<uint8_t>("255"), 255);
  ASSERT_THROW(fromString<uint8_t>("256"), std::out_of_range);
  ASSERT_THROW(fromString<uint8_t>("-1"), std::out_of_range);

  ASSERT_THROW(fromString<uint8_t>(""), std::invalid_argument);
  ASSERT_THROW(fromString<uint8_t>("+"), std::invalid_argument);
  ASSERT_THROW(fromString<uint8_t>("-"), std::invalid_argument);
  ASSERT_THROW(fromString<uint8_t>("abc"), std::invalid_argument);

  ASSERT_EQ(fromString<int8_t>("12abc"), 12);
  ASSERT_EQ(fromString<int8_t>("-12abc"), -12);
  ASSERT_EQ(fromString<int8_t>("   12abc"), 12);
  ASSERT_EQ(fromString<int8_t>("   -12abc"), -12);
  ASSERT_EQ(fromString<int8_t>("12   "), 12);
  ASSERT_EQ(fromString<int8_t>("-12   "), -12);
}