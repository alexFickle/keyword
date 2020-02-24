#pragma once

#include <type_traits>


namespace keyword
{


/// @brief Type for the name of keyword arguments.
/// @details This name is the left hand side of an assignment expression at the
/// function with keyword arguments call site.
template <typename TagType, typename ValueType> class Name
{
public:
	using tag_type = TagType;
	using value_type = ValueType;

	Argument<tag_type, value_type> operator=(value_type value) const
	{
		return Argument<TagType, ValueType>{value};
	}
};


template <typename T> struct IsName : std::false_type
{};

template <typename TagType, typename ValueType>
struct IsName<Name<TagType, ValueType>> : std::true_type
{};


/// @brief Type trait for detecting if a type is the name of a keyword argument.
template <typename T> constexpr bool IsName_v = IsName<T>::value;

/// @brief Type trait for detecting if a parmeter pack are all keyword
/// arguments.
template <typename... Ts> constexpr bool AreNames_v = (... && IsName_v<Ts>);


} // namespace keyword
