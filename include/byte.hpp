#pragma once

#include "type_traits.hpp"

#define IG_MAY_ALIAS __attribute__((__may_alias__))

namespace ig {

enum class IG_MAY_ALIAS byte : unsigned char {};

template<class IntegerType, class = enable_if_t<is_integral_v<IntegerType>>>
inline constexpr byte to_byte(IntegerType value) noexcept { return static_cast<byte>(value); }

template <class IntegerType = underlying_type_t<byte>, class = enable_if_t<is_integral_v<IntegerType>>>
inline constexpr IntegerType to_integer(byte b) noexcept { return static_cast<IntegerType>(b); }

inline constexpr unsigned char to_uchar(byte b) noexcept { return to_integer<unsigned char>(b); }

inline constexpr unsigned char to_uchar(int i) noexcept { return static_cast<unsigned char>(i); }

template <class IntegerType, enable_if_t<is_integral_v<IntegerType>>>
inline constexpr byte& operator>>=(byte& b, IntegerType shift) noexcept
{
    return b = to_byte(to_uchar(b) >> shift);
}

template <class IntegerType, enable_if_t<is_integral_v<IntegerType>>>
inline constexpr byte& operator<<=(byte& b, IntegerType shift) noexcept
{
    return b = to_byte(to_uchar(b) << shift);
}

template <class IntegerType, enable_if_t<is_integral_v<IntegerType>>>
inline constexpr byte operator>>(byte b, IntegerType shift) noexcept
{
    return to_byte(to_uchar(b) >> shift);
}

template <class IntegerType, enable_if_t<is_integral_v<IntegerType>>>
inline constexpr byte operator<<(byte b, IntegerType shift) noexcept
{
    return to_byte(to_uchar(b) << shift);
}

inline constexpr byte& operator|=(byte& l, byte r) noexcept
{
    return l = to_byte(to_uchar(l) | to_uchar(r));
}

inline constexpr byte& operator&=(byte& l, byte r) noexcept
{
    return l = to_byte(to_uchar(l) & to_uchar(r));
}

inline constexpr byte& operator^=(byte& l, byte r) noexcept
{
    return l = to_byte(to_uchar(l) ^ to_uchar(r));
}

inline constexpr byte operator|(byte l, byte r) noexcept
{
    return to_byte(to_uchar(l) | to_uchar(r));
}

inline constexpr byte operator&(byte l, byte r) noexcept
{
    return to_byte(to_uchar(l) & to_uchar(r));
}

inline constexpr byte operator^(byte l, byte r) noexcept
{
    return to_byte(to_uchar(l) ^ to_uchar(r));
}

inline constexpr byte operator~(byte b) noexcept { return to_byte(~to_uchar(b)); }
} //IG END


