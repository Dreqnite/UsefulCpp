#ifndef MEYERSSINGLETON_H
#define MEYERSSINGLETON_H

#include <iostream>

///=============================================================================
/// Meyer's C++11 implementation of Singleton antipatter.
///=============================================================================
class Singleton
{
public:
    ///=============================================================================
    /// @brief Gets class instance.
    ///
    /// @return Singleton& instance - class instance.
    ///=============================================================================
    static Singleton& getInstance()
    {
        static Singleton instance;
        return instance;
    }

    ///=============================================================================
    /// @brief Prints "Hello world!" in the console.
    ///
    /// @return void.
    ///=============================================================================
    void print()
    {
        std::cout << "Hello world!" << std::endl;
    }

private:
    // Generates default ctor/dtor
    Singleton() = default;
    ~Singleton() = default;

    // Forbids copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Forbids move-semantics
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

///=============================================================================
/// @brief Example.
///=============================================================================
void show()
{
    Singleton::getInstance().print();

    // auto s1 = Singleton::getInstance(); // Error (copy ctr was deleted)

    // auto& -> T&
    auto& s2 = Singleton::getInstance();
    s2.print();

    // auto&& -> T&
    auto&& s3 = Singleton::getInstance();
    s3.print();
}

#endif // MEYERSSINGLETON_H

