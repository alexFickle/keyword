#pragma once

#include "keyword/details/Contains.hpp"

#include <type_traits>


namespace keyword
{


namespace details
{


// true base case, only selected when sizeof...(Ts) is zero.
template <typename... Ts> struct Unique : std::true_type
{};

// generic case
template <typename First, typename... Ts>
struct Unique<First, Ts...>
    : std::bool_constant<!Contains_v<First, Ts...> && Unique<Ts...>::value>
{};


/// @brief Type trait for if there are any duplicates in a parameter pack.
template <typename... Ts> constexpr bool Unique_v = Unique<Ts...>::value;


} // namespace details


} // namespace keyword
