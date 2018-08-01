#ifndef STRING_H
#define STRING_H

#include <cstring> // for strlen(), memcpy(), memset() and etc...
#include <stdexcept>

///=============================================================================
/// Simple string implementation. No SSO for now. String does not contain null
/// terminator '\0'. But if data() or c_str() is being called, it will be appen-
/// ded.
///=============================================================================
template <typename CharT>
class String
{
public:
    ///=============================================================================
    /// @brief Default constructor. Creates an empty string object.
    ///=============================================================================
    String(const std::size_t size = 0)
        : m_size(size)
        , m_capacity(size)
        , m_data(new CharT[size])
    {}

    ///=============================================================================
    /// @brief Constructor. Plain character is passed.
    ///
    /// @param CharT c - character.
    ///=============================================================================
    explicit String(CharT c)
        : m_size(1)
        , m_capacity(2)
        , m_data(new CharT(c))
    {}

    ///=============================================================================
    /// @brief Constructor. C-String is passed.
    ///
    /// @param const CharT* data - c-style string.
    ///=============================================================================
    explicit String(const CharT* data) noexcept
        : m_size(strlen(data))
        , m_capacity(strlen(data))
        , m_data(data)
    {}

    ///=============================================================================
    /// @brief Copy-constructor.
    /// 
    /// @param const String<CharT>& str - read-only reference to another String.
    ///=============================================================================
    String(const String<CharT>& str)
        : m_size(str.length())
        , m_capacity(str.length() + 1)
        , m_data(new CharT(str.data()))
    {}

    ///=============================================================================
    /// @brief Move-constructor.
    ///
    /// @param String<CharT>&& str - rv-reference to another String.
    ///=============================================================================
    String(String<CharT>&& str) noexcept
        : m_size(str.length())
        , m_capacity(str.length())
        , m_data(std::move(str.data()))
    {}

    ///=============================================================================
    /// @brief Destructor. Deletes heap-allocated string.
    ///=============================================================================
    ~String()
    {
        if (data)
        {
            delete m_data;
        }
    }

    //======================== operators ================================

    ///=============================================================================
    ///=============================================================================
    String<CharT>& operator=(const String<CharT>& str)
    {
        m_capacity = str.length() + 1; // for '\0'
        
        // Memory reallocation with a new capacity value
        delete m_data;
        m_data = new CharT[m_capacity];

        // Assigning new data
        std::memcpy(m_data, str.c_str(), m_capacity - 1);

        return *this;
    }

    ///=============================================================================
    ///=============================================================================
    String<CharT>& operator+=(const String<CharT>& str)
    {   
        // Checks whether we have enough of remaining capacity or not
        if ((m_capacity - m_size) >= str.length())
        {


        }
        // нужно ли здесь делать +1?
        m_capacity += str.length() + 1;

        CharT* tmp = m_data;
        delete m_data;
        m_data = new CharT[m_capacity];

        // Copies old data
        std::memcpy(m_data, tmp, tmp.length());

        // Copies new data, starting from the end position of the old data
        std::memcpy(&*(m_data + tmp.length()), str.c_str(), str.length() + 1);

        return *this;
    }

    ///=============================================================================
    ///=============================================================================
    String<CharT>& operator+=(const CharT* cstr)
    {
        
    }

    ///=============================================================================
    ///=============================================================================
    String<CharT>& operator+=(const CharT c)
    {
        if (c == '\0')
        {
            *(m_data + m_size) = '\0';
        }
        else
        {

        }

    }

    ///=============================================================================
    ///=============================================================================
    CharT& operator[](const std::size_t index)
    {
        return *(m_data + index);
    }

    ///=============================================================================
    ///=============================================================================
    const CharT& operator[](const std::size_t index) const
    {
        return *(m_data + index);
    }

    //============================= Additional methods =============================

    ///=============================================================================
    /// @brief Gets content of 
    ///=============================================================================
    inline CharT& at(const std::size_t n) const
    {
        if (m_size >= n) { throw std::out_of_range; }
        return operator[](n);
    }

    ///=============================================================================
    /// @brief Checks whether the string is empty or not.
    ///
    /// @return true if string is empty, otherwise returns false.
    ///=============================================================================
    inline bool empty() const noexcept { return m_size == 0; }

    ///=============================================================================
    ///=============================================================================
    inline std::size_t size() const noexcept { return m_size; }

    ///=============================================================================
    ///=============================================================================
    inline std::size_t length() const noexcept { return m_size; }

    ///=============================================================================
    ///=============================================================================
    inline std::size_t capacity() const noexcept { return m_capacity; }

    ///=============================================================================
    /// @brief Equivalent of c_str().
    ///
    /// @return const CharT* m_data - c-string.
    ///=============================================================================
    inline const CharT* data() const noexcept { return c_str(); }

    ///=============================================================================
    /// @brief Returns c-string. Appends teminating null.
    ///
    /// @return const CharT* m_data - c-string.
    ///=============================================================================
    inline const CharT* c_str() const noexcept
    {
        *(m_data + m_size) = '\0';
        return m_data;
    }

    ///=============================================================================
    ///=============================================================================
    void reserve(std::size_t n)
    {
        if (m_capacity >= capacity) { return; }

        new CharT[capacity];
    }

private:
    std::size_t m_size;
    std::size_t m_capacity;
    CharT*      m_data;
};

template class String<char>;
template class String<wchar_t>;

using CString = String<char>;
using WString = String<wchar_t>;

//======================== Comparison operators ================================

///=============================================================================
///=============================================================================
template <typename CharT>
inline bool operator==(const String<CharT>& lhs, const String<CharT>& rhs)
{
    return strncmp(lhs.c_str(), rhs.c_str()) == 0;
}

///=============================================================================
///=============================================================================
template <typename CharT>
inline bool operator!=(const String<CharT>& lhs, const String<CharT>& rhs)
{
    return strncmp(lhs.c_str(), rhs.c_str()) != 0;
}

///=============================================================================
///=============================================================================
template <typename CharT>
inline bool operator<(const String<CharT>& lhs, const String<CharT>& rhs)
{
    return strncmp(lhs.c_str(), rhs.c_str()) < 0;
}

///=============================================================================
///=============================================================================
template <typename CharT>
inline bool operator>(const String<CharT>& lhs, const String<CharT>& rhs)
{
    return strncmp(lhs.c_str(), rhs.c_str()) < 0;
}

///=============================================================================
///=============================================================================
template <typename CharT>
inline bool operator<=(const String<CharT>& lhs, const String<CharT>& rhs)
{
    return strncmp(lhs.c_str(), rhs.c_str()) <= 0;
}

///=============================================================================
///=============================================================================
template <typename CharT>
inline bool operator>=(const String<CharT>& lhs, const String<CharT>& rhs)
{
    return strncmp(lhs.c_str(), rhs.c_str()) >= 0;
}

///=============================================================================
///=============================================================================
template <typename CharT>
inline String<CharT> operator+(const String<CharT>& lhs, const String<CharT>& rhs)
{
    lhs += rhs;
    return lhs;
}

#endif // STRING_H

