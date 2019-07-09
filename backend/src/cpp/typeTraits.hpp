#ifndef TYPE_TRAITS
#define TYPE_TRAITS


namespace TypeTraits {
template<typename T>
inline constexpr bool isPrimitive() { return false; }
template<>
inline constexpr bool isPrimitive<bool>() { return true; }
template<>
inline constexpr bool isPrimitive<signed char>() { return true; }
template<>
inline constexpr bool isPrimitive<signed short>() { return true; }
template<>
inline constexpr bool isPrimitive<signed int>() { return true; }
template<>
inline constexpr bool isPrimitive<signed long>() { return true; }
template<>
inline constexpr bool isPrimitive<signed long long>() { return true; }
template<>
inline constexpr bool isPrimitive<unsigned char>() { return true; }
template<>
inline constexpr bool isPrimitive<unsigned short>() { return true; }
template<>
inline constexpr bool isPrimitive<unsigned int>() { return true; }
template<>
inline constexpr bool isPrimitive<unsigned long>() { return true; }
template<>
inline constexpr bool isPrimitive<unsigned long long>() { return true; }


template<typename T>
inline constexpr bool isUnsigned() { return false; }
template<>
inline constexpr bool isUnsigned<unsigned char>() { return true; }
template<>
inline constexpr bool isUnsigned<unsigned short>() { return true; }
template<>
inline constexpr bool isUnsigned<unsigned int>() { return true; }
template<>
inline constexpr bool isUnsigned<unsigned long>() { return true; }
template<>
inline constexpr bool isUnsigned<unsigned long long>() { return true; }


template<typename T>
inline constexpr bool isSigned() { return false; }
template<>
inline constexpr bool isSigned<signed char>() { return true; }
template<>
inline constexpr bool isSigned<signed short>() { return true; }
template<>
inline constexpr bool isSigned<signed int>() { return true; }
template<>
inline constexpr bool isSigned<signed long>() { return true; }
template<>
inline constexpr bool isSigned<signed long long>() { return true; }


inline unsigned char toUnsigned(unsigned char n) { return n; }
inline unsigned short toUnsigned(unsigned short n) { return n; }
inline unsigned int toUnsigned(unsigned int n) { return n; }
inline unsigned long toUnsigned(unsigned long n) { return n; }
inline unsigned long long toUnsigned(unsigned long long n) { return n; }
inline unsigned char toUnsigned(signed char n) { return n; }
inline unsigned short toUnsigned(signed short n) { return n; }
inline unsigned int toUnsigned(signed int n) { return n; }
inline unsigned long toUnsigned(signed long n) { return n; }
inline unsigned long long toUnsigned(signed long long n) { return n; }


inline signed char toSigned(unsigned char n) { return n; }
inline signed short toSigned(unsigned short n) { return n; }
inline signed int toSigned(unsigned int n) { return n; }
inline signed long toSigned(unsigned long n) { return n; }
inline signed long long toSigned(unsigned long long n) { return n; }
inline signed char toSigned(signed char n) { return n; }
inline signed short toSigned(signed short n) { return n; }
inline signed int toSigned(signed int n) { return n; }
inline signed long toSigned(signed long n) { return n; }
inline signed long long toSigned(signed long long n) { return n; }
};


#endif /* TYPE_TRAITS */
