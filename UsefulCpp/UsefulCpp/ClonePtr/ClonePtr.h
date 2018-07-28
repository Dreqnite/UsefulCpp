#ifndef CLONEPTR_H
#define CLONEPTR_H

#include <algorithm>

///=============================================================================
/// ClonePtr is a wrapper for a raw pointer which looks like a smart pointer
/// std::unique_ptr from the standard library. Using classes, we can add some
/// useful funcionality to operate with raw pointers and control their state as
/// we want to.
///
/// 
///=============================================================================
template <typename T>
class ClonePtr
{
public:
    //======================== Constructors/Destructors ============================

    ///=============================================================================
    /// @brief Default constructor. Creates an empty ClonePtr.
    ///=============================================================================
    ClonePtr()
        : m_ptr(nullptr)
    {}

    ///=============================================================================
    /// @brief Constructor. Takes over ownership of ptr.
    ///
    /// @param T* object - pointer to a writable heap-allocated object.
    ///=============================================================================
    explicit ClonePtr(T* object)
        : m_ptr(object)
    {}

    ///=============================================================================
    /// @brief Constructor. Takes over ownership of content of ptr and clears ptr.
    ///
    /// @param T** object - pointer to a pointer to a writable heap-allocated object.
    ///=============================================================================
    explicit ClonePtr(T** object)
        : m_ptr(*object)
    {
        // ptr will not point to a heap-allocated object
        *object = nullptr;
    }

    ///=============================================================================
    /// @brief Constructor. Since it's a read-only object, we forced to create a new
    ///        heap-allocated copy of that object.
    ///
    /// @param const T* object - pointer to a read-only heap-allocated object.
    ///=============================================================================
    explicit ClonePtr(const T* object)
        : m_ptr(object ? new T(*object) : nullptr)
    {}

    ///=============================================================================
    /// @brief Constructor.
    ///
    /// @param const T& object - read-only reaference to an object.
    ///=============================================================================
    explicit ClonePtr(const T& object)
        : m_ptr(&object ? new T(object) : nullptr)
    {}

    ///=============================================================================
    /// @brief Copy-constructor. Deep copy of ClonePtr means copying of raw pointer
    ///        too.
    ///
    /// @param ClonePtr& other - read-only reference to another ClonePtr instance.
    ///=============================================================================
    ClonePtr(const ClonePtr<T>& other)
        : m_ptr(other.get() ? new T(*(other.get())) : nullptr)
    {}

    ///=============================================================================
    /// @brief Move-constructor.
    ///
    /// @param ClonePtr&& other - rv-reference to another ClonePtr instance.
    ///=============================================================================
    ClonePtr(ClonePtr<T>&& other)
        : m_ptr(other.get())
    {}

    ///=============================================================================
    /// @brief Destructor.
    ///=============================================================================
    ~ClonePtr()
    {
        if (m_ptr)
        {
            delete m_ptr;
        }
    }
    
    //============================= Operator functions =============================

    ///=============================================================================
    /// @brief Assignment operator which clones pointer.
    ///
    /// @param const ClonePtr& other - another ClonePtr.
    ///
    /// @return reference to an insance of a cloned pointer.
    ///=============================================================================
    ClonePtr<T>& operator=(const ClonePtr<T>& other)
    {
        // Compares addresses of this instance and other instance
        // if addresses are the same, it means that we try to assign pointer to itself
        if (this != &other)
        {
            // Deletes old pointer
            delete m_ptr;

            // Assigns new value if other pointer is not empty, otherwise sets nullptr
            m_ptr = other.get() ? new T(*(other.get())) : nullptr;
        }
        return *this;
    }

    ///=============================================================================
    /// @brief Assignment operator for move-semantics.
    ///
    /// @param ClonePtr&& other - rv-reference to another ClonePtr instance.
    ///
    /// @return reference to an insance of a cloned pointer.
    ///=============================================================================
    ClonePtr<T>& operator=(ClonePtr<T>&& other)
    {
        // Swapping is one of the fastest ways to assign new value
        std::swap(m_ptr, other.get());
        return *this;
    }

    ///=============================================================================
    /// @brief
    ///=============================================================================
    ClonePtr<T>& operator=(std::nullptr_t)
    {
        clear();
        return *this;
    }

    ///=============================================================================
    /// @brief Derefence operator which gets constant reference to data of raw
    ///        pointer.
    ///
    /// @return constant reference to data of raw pointer.
    ///=============================================================================
    const T& operator*() const { return *m_ptr; }

    ///=============================================================================
    /// @brief Derefence operator which gets reference to data of raw pointer.
    ///
    /// @return reference to data of raw pointer.
    ///=============================================================================
    T& operator*() { return *m_ptr; }

    ///=============================================================================
    /// @brief Arrow operator which gets pointer to constant of type T.
    ///
    /// @return pointer to constant of type T.
    ///=============================================================================
    const T* operator->() const { return m_ptr; }

    ///=============================================================================
    /// @brief Arrow operator which gets pointer to data of type T.
    ///
    /// @return pointer to data of type T.
    ///=============================================================================
    T* operator->() { return m_ptr; }

    ///=============================================================================
    /// @brief Converts object to type bool. if container is empty it returns false, 
    ///        otherwise true.
    /// 
    /// @return boolean result of conversion.
    ///=============================================================================
    operator bool() const { return !empty(); }

    //============================= Additional methods =============================

    ///=============================================================================
    /// @brief Gets raw pointer of a ClonePtr.
    ///
    /// @return T* m_ptr - raw pointer.
    ///=============================================================================
    T* get() const { return m_ptr; }

    ///=============================================================================
    /// @brief Checks whether the ClonePtr is empty or not.
    ///
    /// @return const bool - boolean result of checking.
    ///=============================================================================
    const bool empty() const { return m_ptr == nullptr; }

    ///=============================================================================
    /// @brief Clears container, deleting its object.
    ///
    /// Note: this operation throws exception if contaier is empty.
    ///
    /// @return void.
    ///=============================================================================
    void clear() { delete m_ptr; }

private:
    T* m_ptr;
};

#endif // CLONEPTR_H