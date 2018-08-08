#ifndef CRTP_H
#define CRTP_H

#include <iostream>

///=============================================================================
/// Base class template which accepts Derived class in the template parameter
/// and downcasts when calling derived class' functions.
///=============================================================================
template <typename T>
class Base
{
public:
    ///=============================================================================
    /// @brief test function which downcasts to the derived type T*, making it pos-
    ///        sible to call functions from child class.
    ///
    /// @return void.
    ///=============================================================================
    void call()
    {
        static_cast<T*>(this)->call();
    }
};

///=============================================================================
/// Derived class which takes instantiated template with itself (Derived) as a
/// template parameter, core part of CRTP.
///=============================================================================
class Derived : public Base<Derived>
{
public:
    ///=============================================================================
    /// @brief Test function which prints "Hello world" in a console.
    ///
    /// @return void.
    ///=============================================================================
    void call()
    {
        std::cout << "Hello world!" << std::endl;
    }
};

///=============================================================================
/// @brief Example.
///=============================================================================
void show()
{
    Base<Derived> base;
    base.call(); // Derived::call() is called

    Derived derived;
    derived.call(); // Derived::call() is called
}

#endif // CRTP_H

