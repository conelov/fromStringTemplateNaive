//
// Created by dym on 29.04.2021.
//

#ifndef FROMSTRING_FROMSTRING_HPP
#define FROMSTRING_FROMSTRING_HPP
#include <algorithm>

struct ExceptionDescriptor
{
  const std::errc er;
  const std::string_view what;
};

template<typename T>
  requires std::is_same_v<T, std::decay_t<T>> && std::is_integral_v<T> && (!std::is_same_v<T,bool>)
constexpr std::pair<ExceptionDescriptor, T> fromString_noexcept(auto &&chars) noexcept
{
  std::basic_string_view sv(std::forward<decltype(chars)>(chars));
  using Char= typename decltype(sv)::value_type;
  constexpr auto symbolPlus= Char('+'), symbolMinus= Char('-');
  constexpr std::pair<ExceptionDescriptor, T> ErrM_notNum{ { std::errc::invalid_argument, "string not contain a number " }, {} },
      ErrM_overflow{ { std::errc::result_out_of_range, "overflow" }, {} };

  if (sv.empty())
    return { { std::errc::invalid_argument, "empty string" }, {} };

  sv.remove_prefix(sv.find_first_not_of(Char(' ')));

  /// check sign
  bool negateFlag= false;
  switch (sv.front()) {
  case symbolMinus: negateFlag= true; [[fallthrough]];
  case symbolPlus:
    sv.remove_prefix(1);
    /// optimal if
    if (sv.empty() || !std::isdigit(sv.front()))
      return ErrM_notNum;
  }

  T retVal{};
  for (auto it= sv.cbegin(); it != sv.cend() && !std::isspace(*it); ++it) {
    if(!std::isdigit(*it))
      return ErrM_notNum;

    auto const numPart= *it - Char('0');

    if (retVal > std::numeric_limits<T>::max() / 10)
      return ErrM_overflow;
    retVal*= 10;

    if (numPart > 0 && retVal > std::numeric_limits<T>::max() - numPart)
      return ErrM_overflow;
    retVal+= numPart;
  }

  if (negateFlag && std::is_unsigned_v<T>)
    return { { std::errc::result_out_of_range, "underflow" }, {} };
  return { {}, negateFlag ? -retVal : retVal };
}

template<typename T>
constexpr T fromString(auto &&sv)
{
  switch (std::pair<ExceptionDescriptor, T> const retP= fromString_noexcept<T>(std::forward<decltype(sv)>(sv)); retP.first.er) {
  case std::errc{}: return retP.second;
  case std::errc::invalid_argument: throw std::invalid_argument(retP.first.what.data());
  case std::errc::result_out_of_range: throw std::out_of_range(retP.first.what.data());
  default: throw std::invalid_argument("default statement");
  }
}

#endif // FROMSTRING_FROMSTRING_HPP

/// Use const whenever possible. ⒸScott Meyers