#include <string>
#include <vector>
#include <compile_time_magic.h>

namespace ctm
{

CTM_HAS_TYPEDEF(some_type)
CTM_HAS_METHOD(some_method)

}

class TestClass
{
public:
    using some_type = void;
    void some_method(double) const;
};

int main()
{
    using namespace ctm;

    using vec = std::vector<int>;
    using str = std::string;

    static_assert(has_some_type_v<TestClass>);
    static_assert(has_method_some_method_v<TestClass, double>);

    static_assert(has_method_begin_v<vec>);
    static_assert(has_method_cend_v<str>);
    static_assert(has_method_size_v<std::vector<int>>);

    static_assert(!has_method_cbegin_v<int>);

    static_assert(is_container_v<vec> && !is_container_v<TestClass>);
}
