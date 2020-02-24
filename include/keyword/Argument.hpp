#pragma once

#include <type_traits>


namespace keyword
{


/// @brief The result of an assignment to a cli::Name.
template <typename TagType, typename ValueType> class Argument
{
public:
	using tag_type = TagType;
	using value_type = ValueType;

	Argument(value_type value_)
	    : value(value_)
	{}

	value_type value;
};


template <typename T> struct IsArgument : std::false_type
{};

template <typename TagType, typename ValueType>
struct IsArgument<Argument<TagType, ValueType>> : std::true_type
{};


/// @brief Type trait for detecting if a type is a keyword argument.
template <typename T> constexpr bool IsArgument_v = IsArgument<T>::value;

/// @brief Type trait for detecting if a parmeter pack are all keyword
/// arguments.
template <typename... Ts>
constexpr bool AreArguments_v = (... && IsArgument_v<Ts>);


} // namespace keyword
