#include "keyword.hpp"

#include "gtest/gtest.h"


namespace
{


struct Data
{
	std::string first;
	std::string second;
	std::string third;
};


namespace kw
{


struct second_tag
{};
struct third_tag
{};


keyword::Name<second_tag, std::string> second;
keyword::Name<third_tag, std::string> third;


} // namespace kw


template <typename... Kwargs> Data MakeData(std::string first, Kwargs... values)
{
	Data data{first};
	keyword::Names names{kw::second, kw::third};
	keyword::Arguments kwargs{names, values...};
	if constexpr(kwargs.Has(kw::second))
	{
		data.second = kwargs.Get(kw::second);
	}
	if constexpr(kwargs.Has(kw::third))
	{
		data.third = kwargs.Get(kw::third);
	}
	return data;
}


TEST(example, test)
{
	using namespace kw;
	Data data;
	data = MakeData("1", second = "2", third = "3");
	ASSERT_EQ(data.first, "1");
	ASSERT_EQ(data.second, "2");
	ASSERT_EQ(data.third, "3");

	data = MakeData("foo", third = "bar");
	ASSERT_EQ(data.first, "foo");
	ASSERT_TRUE(data.second.empty());
	ASSERT_EQ(data.third, "bar");
}


} // namespace