#ifndef SAFEBOOLCORE_H
#define SAFEBOOLCORE_H

///=============================================================================
/// C++11 implementation of SafeBool idiom. Starting with that standard, expli-
/// cit conversion operators is provided, solving the problem in a clean way.
/// Example:
/// SafeBoolCore a;
/// if (a) { syd::cout << "Will not be printed!" << std::endl; }
///=============================================================================
class SafeBoolCore
{
public:
    ///=============================================================================
    /// @brief Explicit bool operator, which helps to define a behavoir of implicit 
    ///        conversions.
    /// 
    /// @return boolean result of conversion.
    ///=============================================================================
    explicit operator bool() const noexcept { return false; }
};

#endif // SAFEBOOLCORE_H


