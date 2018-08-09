#ifndef EXTERNPOLYMORPH_H
#define EXTERNPOLYMORTH_H

#include <iostream>
#include <map>
#include <memory>

///=============================================================================
/// Interface which defines a list of pure abstract methods which are used when
/// iterating over elements of the heterogenious container.
///=============================================================================
struct IObject
{
    ///=============================================================================
    /// @brief Gets code (declaration).
    ///
    /// @return const int - code.
    ///=============================================================================
    virtual const int getCode() const noexcept = 0;
};

///=============================================================================
/// Wrapper which stores concrete objects of type T.
///=============================================================================
template <typename T>
class ConcreteObject : public IObject
{
public:
    ///=============================================================================
    /// @brief Constructor.
    ///
    /// @param const T* object - arbitrary object of type T.
    ///=============================================================================
    ConcreteObject(const T* object)
        : m_object(object)
    {}

    ///=============================================================================
    /// @brief Gets code (declaration).
    ///
    /// @return const int - code.
    ///=============================================================================
    const int getCode() const noexcept override
    {
        return m_object->getCode();
    }

private:
    const T* m_object;
};

///=============================================================================
/// Sample class Foo.
///=============================================================================
class Foo
{
public:
    ///=============================================================================
    /// @brief Constructor.
    ///
    /// @param const int code - code.
    ///=============================================================================
    Foo(const int code)
        : m_code(code)
    {}

    ///=============================================================================
    /// @brief Gets code (declaration).
    ///
    /// @return const int - code.
    ///=============================================================================
    const int getCode() const noexcept { return m_code; }

private:
    int m_code;
};

///=============================================================================
/// Sample class Bar.
///=============================================================================
class Bar
{
public:
    ///=============================================================================
    /// @brief Constructor.
    ///
    /// @param const int code - code.
    ///=============================================================================
    Bar(const int code)
        : m_code(code)
    {}

    ///=============================================================================
    /// @brief Gets code (declaration).
    ///
    /// @return const int - code.
    ///=============================================================================
    const int getCode() const noexcept { return m_code; }

private:
    int m_code;
};

///=============================================================================
/// Sample class Baz.
///=============================================================================
class Baz
{
public:
    ///=============================================================================
    /// @brief Constructor.
    ///
    /// @param const int code - code.
    ///=============================================================================
    Baz(const int code)
        : m_code(code)
    {}

    ///=============================================================================
    /// @brief Gets code (declaration).
    ///
    /// @return const int - code.
    ///=============================================================================
    const int getCode() const noexcept { return m_code; }

private:
    int m_code;
};

///=============================================================================
/// CollectionHolder holds the collection of heterogenious objects.
///=============================================================================
class CollectionHolder
{
public:
    ///=============================================================================
    /// @brief Clears the collection of heterogeneous objects.
    ///=============================================================================
    ~CollectionHolder() { m_objects.clear(); }

    ///=============================================================================
    /// @brief Adds new object in the map.
    ///
    /// @param const int objectId - key to find spe
    /// @param const int code - useful peace of data stored in the object.
    ///
    /// @return void.
    ///=============================================================================
    template <typename T>
    void addElement(const int objectId,
                    const int code)
    {
        m_objects[objectId] = std::unique_ptr<IObject>(
            new ConcreteObject<T>(new T(code))
        );
    }

    ///=============================================================================
    /// @brief Prints codes to the console.
    ///
    /// @return void.
    ///=============================================================================
    void printCodes()
    {
        for (const auto& code : m_objects)
        {
            std::cout << code.second->getCode() << std::endl;
        }
    }

private:
    // The collection of heterogeneous objects
    std::map<int, std::unique_ptr<IObject>> m_objects;
};

///=============================================================================
/// @brief Example.
///=============================================================================
void show()
{
    CollectionHolder ch;
    ch.addElement<Bar>(1, 1234);
    ch.addElement<Baz>(2, 7777);
    ch.addElement<Foo>(3, 8373);
    ch.printCodes(); // 1234, 7777, 8373
}

#endif // EXTERNPOLYMORPH_H
