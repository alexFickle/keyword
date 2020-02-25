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
	Data data{first, "bad"};
	keyword::Names names{kw::second, kw::third};
	keyword::Arguments kwargs{names, values...};
	data.second = kwargs.GetOrDefault(kw::second, {});
	if constexpr(kwargs.Contains(kw::third))
	{
		data.third = kwargs.Get(kw::third);
	}
	return data;
}


TEST(example, none)
{
	using namespace kw;
	Data data = MakeData("1");
	ASSERT_EQ(data.first, "1");
	ASSERT_TRUE(data.second.empty());
	ASSERT_TRUE(data.third.empty());
}

TEST(example, second)
{
	using namespace kw;
	Data data = MakeData("1", second = "2");
	ASSERT_EQ(data.first, "1");
	ASSERT_EQ(data.second, "2");
	ASSERT_TRUE(data.third.empty());
}

TEST(example, third)
{
	using namespace kw;
	Data data = MakeData("1", third = "3");
	ASSERT_EQ(data.first, "1");
	ASSERT_TRUE(data.second.empty());
	ASSERT_EQ(data.third, "3");
}

TEST(example, both)
{
	using namespace kw;
	Data data = MakeData("1", second = "2", third = "3");
	ASSERT_EQ(data.first, "1");
	ASSERT_EQ(data.second, "2");
	ASSERT_EQ(data.third, "3");
}

TEST(example, backwards)
{
	using namespace kw;
	Data data = MakeData("1", third = "3", second = "2");
	ASSERT_EQ(data.first, "1");
	ASSERT_EQ(data.second, "2");
	ASSERT_EQ(data.third, "3");
}


} // namespace