#include "doctest.h"
#include "singleton.h"

#include <stdio.h>
#include <type_traits>
#include <unistd.h>

class MyClass {
public:
    MyClass() {}
    MyClass(const MyClass &) = delete;
    MyClass &operator=(const MyClass &) = delete;
};
TEST_SUITE("单例模板") {
    TEST_CASE("单例模板::返回一个单例") {
        auto &instance1 = Singleton<MyClass>::instance();
        auto &instance2 = Singleton<MyClass>::instance();
        CHECK(&instance1 == &instance2);
    }

    TEST_CASE("单例模板::禁止拷贝构造") {
        CHECK(std::is_copy_constructible<Singleton<MyClass>>::value == false);
        CHECK(std::is_copy_assignable<Singleton<MyClass>>::value == false);
    }
}