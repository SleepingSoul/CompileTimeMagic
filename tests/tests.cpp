#include <ctime>
#include <cstdlib>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <string_view>
#include <unordered_map>
#include <numeric>
#include <algorithm>

#include <gtest/gtest.h>

#include <extra_algorithm.h>
#include <string_utils.h>

#include "test_containers.h"

class ESTDTest : public ::testing::Test
{
public:
    static void SetUpTestCase()
    {
        std::srand(std::time(0));
    }
};

TEST_F(ESTDTest, Test_Contains_SeqContainer)
{
    std::vector vec = {1, 2, 3, 4, 5};

    const auto existingElement = vec.at(rand() % vec.size());

    ASSERT_TRUE(estd::contains(vec, existingElement));
}

TEST_F(ESTDTest, Test_Contains_MapContainer)
{
    std::unordered_map<int, std::string_view> map;

    map.emplace(0, "hello");
    map.emplace(1, "world");
    map.emplace(2, "hello there");

    const auto existingKey = map.find(rand() % map.size())->first;

    ASSERT_TRUE(estd::contains(map, existingKey));

    MapWithExtraInfo<std::string_view, double> testMap;

    estd::contains(testMap, std::string_view{});

    ASSERT_EQ(testMap.countCallsOf("cfind"), 1);
}

TEST_F(ESTDTest, Test_Contains_If_Seq_Container)
{
    const std::array<std::vector<unsigned>, 5> arr = {
        std::vector<unsigned>{1, 2, 3, 4, 5},
        std::vector<unsigned>{2, 3, 4, 5, 6},
        std::vector<unsigned>{3, 4, 5, 6, 7},
        std::vector<unsigned>{4, 5, 6, 7, 8},
        std::vector<unsigned>{99, 99, 99, 99, 99}
    };

    ASSERT_TRUE(estd::contains_if(arr, [](const auto& vec)
    {
        return std::accumulate(vec.cbegin(), vec.cend(), 0u) > 100u;
    }));
}

TEST_F(ESTDTest, Test_Find_Seq_Container)
{
    const std::list<std::string_view> lst = {
        "sample text",
        "sample text",
        "hello world",
        "GOTCHA"
    };

    const auto [found, it] = estd::find(lst, "GOTCHA");

    ASSERT_TRUE(found);
    ASSERT_EQ(*it, "GOTCHA");
}

TEST_F(ESTDTest, Test_Find_MapContainer)
{
    MapWithExtraInfo<float, std::string_view> mp;

    mp.emplace(3.14f, "pi");
    mp.emplace(2.71f, "e");

    const auto [found, it] = estd::find(mp, 3.14f);

    ASSERT_TRUE(found);
    ASSERT_EQ(it->second, "pi");
}

TEST_F(ESTDTest, Test_Find_If_Seq_Container)
{
    const std::list<double> lst = {
        1.5, 1.6, 1.7, 1.8, 1.9, 2.
    };

    const auto [found, it] = estd::find_if(lst, [](double value)
    {
        return value > 2.1;
    });

    ASSERT_FALSE(found);
    ASSERT_EQ(it, lst.cend());
}

TEST_F(ESTDTest, Test_All)
{
    const std::vector<std::string_view> vec = { "he", "ll", "ow", "wo", "rl", "d!" };

    ASSERT_TRUE(estd::all(vec, [](const auto& str) { return str.size() == 2; }));
    ASSERT_FALSE(estd::all(vec, [](const auto& str) { return str == "hello world!"; }));
}

TEST_F(ESTDTest, Test_Are_Unique)
{
    const std::vector vec({ 1, 2, 3, 3, 4, 4, 5, 6 });
    const std::list lst({ 1, 2, 3, 4, 5, 6 });

    ASSERT_FALSE(estd::are_unique(vec));
    ASSERT_TRUE(estd::are_unique(lst));
}

TEST_F(ESTDTest, Test_Append)
{
    std::vector baseVec = { 1, 2, 3 };
    const std::list lst = { 4, 5 };

    estd::append(baseVec, lst);

    ASSERT_EQ(baseVec, std::vector({ 1, 2, 3, 4, 5 }));
}

const auto isEven = [](auto number)
{
    static_assert(std::is_integral_v<decltype(number)>);
    return number % static_cast<decltype(number)>(2) == 0;
};

TEST_F(ESTDTest, Test_Append_If)
{
    std::list lst = { 2, 4 };
    const std::vector vec = { 5, 6, 7, 8, 9, 10 };

    estd::append_if(lst, vec, [](auto number)
    {
        return isEven(number);
    });

    ASSERT_EQ(lst, std::list({2, 4, 6, 8, 10}));
}

TEST_F(ESTDTest, Test_Remove_If)
{
    std::vector vec = { 1, 2, 3, 4, 5 };

    estd::remove_if(vec, isEven);

    ASSERT_EQ(vec, std::vector({ 1, 3, 5 }));
}

TEST_F(ESTDTest, Test_Filter)
{
    const std::list lst = { 1, 2, 3, 4, 5 };

    const auto onlyEven = estd::filter(lst, isEven);

    ASSERT_EQ(onlyEven, std::list({ 2, 4 }));
}

TEST_F(ESTDTest, Test_Format)
{
    const char* const fmt = "Hello %s %d!";

    const auto result = estd::format(fmt, "World", 255);

    ASSERT_TRUE(result == "Hello World 255!");
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
