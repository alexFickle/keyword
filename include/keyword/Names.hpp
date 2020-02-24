#pragma once

#include "keyword/Name.hpp"
#include "keyword/details/Contains.hpp"
#include "keyword/details/Unique.hpp"

#include <type_traits>


namespace keyword
{


/// @brief A collection of keyword::Name.
template <typename... Ts> class Names
{
	static_assert(
	    AreNames_v<Ts...>,
	    "The inputs to keyword::Names must all be a keyword::Name");

	static_assert(
	    details::Unique_v<Ts...>,
	    "Duplicated keyword::Name given to keyword::Names.");

public:
	constexpr Names(Ts...) noexcept
	{}

	/// @brief Tests if all passed in keyword::Arguments have a corresponding
	/// keyword::Name in this keyword::Names.
	template <typename... Arguments>
	static constexpr bool AreArgumentsHandled_v =
	    (...
	     && keyword::details::Contains_v<
	            keyword::Name<
	                typename Arguments::tag_type,
	                typename Arguments::value_type>,
	            Ts...>);
};


template <typename T> struct IsNames : std::false_type
{};

template <typename... Ts> struct IsNames<Names<Ts...>> : std::true_type
{};


/// @brief Type trait to detect a keyword::Names.
template <typename T> constexpr bool IsNames_v = IsNames<T>::value;


} // namespace keyword
