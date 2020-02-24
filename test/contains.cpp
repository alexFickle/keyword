#include "keyword/details/Contains.hpp"

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


TEST(contains, same)
{
	ASSERT_FALSE(keyword::details::Contains_v<T1>);
	ASSERT_TRUE((keyword::details::Contains_v<T1, T1>));
	ASSERT_TRUE((keyword::details::Contains_v<T1, T1, T1>));
}

TEST(contains, counting)
{
	ASSERT_FALSE((keyword::details::Contains_v<T1, T2>));
	ASSERT_FALSE((keyword::details::Contains_v<T1, T2, T3>));
	ASSERT_FALSE((keyword::details::Contains_v<T1, T2, T3, T4>));
	ASSERT_FALSE((keyword::details::Contains_v<T1, T2, T3, T4, T5>));
}

TEST(contains, yes)
{
	ASSERT_TRUE((keyword::details::Contains_v<T1, T1, T2, T3, T4, T5>));
	ASSERT_TRUE((keyword::details::Contains_v<T2, T1, T2, T3, T4, T5>));
	ASSERT_TRUE((keyword::details::Contains_v<T3, T1, T2, T3, T4, T5>));
	ASSERT_TRUE((keyword::details::Contains_v<T4, T1, T2, T3, T4, T5>));
	ASSERT_TRUE((keyword::details::Contains_v<T5, T1, T2, T3, T4, T5>));
}


} // namespace
