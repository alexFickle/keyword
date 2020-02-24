#include "keyword/details/Unique.hpp"

#include "gtest/gtest.h"


namespace
{


struct T1
{};
struct T2
{};
struct T3
{};
struct T4
{};
struct T5
{};


TEST(unique, empty)
{
	ASSERT_TRUE(keyword::details::Unique_v<>);
}

TEST(unique, single)
{
	ASSERT_TRUE(keyword::details::Unique_v<T1>);
	ASSERT_TRUE(keyword::details::Unique_v<int>);
}

TEST(unique, counting)
{
	ASSERT_TRUE((keyword::details::Unique_v<T1, T2>));
	ASSERT_TRUE((keyword::details::Unique_v<T1, T2, T3>));
	ASSERT_TRUE((keyword::details::Unique_v<T1, T2, T3, T4>));
	ASSERT_TRUE((keyword::details::Unique_v<T1, T2, T3, T4, T5>));
}

TEST(unique, repeated)
{
	ASSERT_FALSE((keyword::details::Unique_v<T1, T1>));
	ASSERT_FALSE((keyword::details::Unique_v<T1, T1, T1>));
	ASSERT_FALSE((keyword::details::Unique_v<T1, T1, T1, T1>));
	ASSERT_FALSE((keyword::details::Unique_v<T1, T1, T1, T1, T1>));
}

TEST(unique, adjacent)
{
	ASSERT_FALSE((keyword::details::Unique_v<T1, T1, T2, T3, T4, T5>));
	ASSERT_FALSE((keyword::details::Unique_v<T1, T2, T2, T3, T4, T5>));
	ASSERT_FALSE((keyword::details::Unique_v<T1, T2, T3, T3, T4, T5>));
	ASSERT_FALSE((keyword::details::Unique_v<T1, T2, T3, T4, T4, T5>));
	ASSERT_FALSE((keyword::details::Unique_v<T1, T2, T3, T4, T5, T5>));
}

TEST(unique, nonadjacent)
{
	ASSERT_FALSE((keyword::details::Unique_v<T1, T2, T1>));
	ASSERT_FALSE((keyword::details::Unique_v<T1, T2, T1, T3>));

	ASSERT_FALSE((keyword::details::Unique_v<T1, T2, T3, T2>));
	ASSERT_FALSE((keyword::details::Unique_v<T1, T2, T3, T2, T4>));

	ASSERT_FALSE((keyword::details::Unique_v<T1, T2, T3, T4, T2>));
	ASSERT_FALSE((keyword::details::Unique_v<T1, T2, T3, T4, T2, T5>));
}


} // namespace
