#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <iostream>
#include <string>

template <class T>
class Singleton {
protected:
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton() = default;
    ~Singleton() = default;

public:
    template <typename... Args>
    static T &instance(Args &&...args) {
        static T instance(std::forward<Args>(args)...);
        return instance;
    }
};
#endif // __SINGLETON_H__