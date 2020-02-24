#pragma once

#include <type_traits>


namespace keyword
{


namespace details
{


// false base case, only selected for sizeof...(Ts) of zero
template <typename T, typename... Ts> struct Contains : std::false_type
{};

// true base case, only selected if the first type in the parameter pack matches
template <typename MatchType, typename... Ts>
struct Contains<MatchType, MatchType, Ts...> : std::true_type
{};

// generic case
template <typename T, typename First, typename... Ts>
struct Contains<T, First, Ts...> : Contains<T, Ts...>
{};


/// @brief Type trait for if a type is inside a paramter pack.
template <typename T, typename... Ts>
constexpr bool Contains_v = Contains<T, Ts...>::value;


} // namespace details


} // namespace keyword
