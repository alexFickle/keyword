#pragma once

#include "keyword/Argument.hpp"
#include "keyword/Name.hpp"
#include "keyword/Names.hpp"
#include "keyword/details/Contains.hpp"
#include "keyword/details/Unique.hpp"

#include <tuple>


namespace keyword
{


/// @brief Type used to parse keyword arguments.
template <typename Names, typename... Ts> class Arguments
{
	static_assert(
	    IsNames_v<Names>,
	    "The first argument to keyword::Arguments must be a keyword::Names.");

	static_assert(
	    AreArguments_v<Ts...>,
	    "All except for the first argument to keyword::Arguments must be a "
	    "keyword::Argument.");

	static_assert(
	    details::Unique_v<Ts...>,
	    "The same keyword argument was used more than once.");

	static_assert(
	    Names::AreArgumentsHandled_v<Ts...>,
	    "Unhandled keyword argument(s).");

public:
	Arguments(Names, Ts... values)
	    : _values(values...)
	{}

	template <typename TagType, typename ValueType>
	constexpr bool Contains(Name<TagType, ValueType>) const noexcept
	{
		return details::Contains_v<Argument<TagType, ValueType>, Ts...>;
	}

	template <typename TagType, typename ValueType>
	ValueType Value(Name<TagType, ValueType>) const
	{
		static_assert(
		    details::Contains_v<Argument<TagType, ValueType>, Ts...>,
		    "Attempted to get the value of a not given keyword argument.  This "
		    "should be prevented by using keyword::Arguments::Get(name) only "
		    "in a "
		    "constexpr if block based on the value of "
		    "keyword::Arguments::Has(name).");
		return std::get<Argument<TagType, ValueType>>(_values).value;
	}

	template <typename TagType, typename ValueType>
	ValueType ValueOr(Name<TagType, ValueType> name, ValueType default_) const
	{
		if constexpr(details::Contains_v<Argument<TagType, ValueType>, Ts...>)
		{
			return Value(name);
		}
		else
		{
			return default_;
		}
	}

private:
	std::tuple<Ts...> _values;
};


} // namespace keyword
