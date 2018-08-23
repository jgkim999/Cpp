///////////////////////////////////////////////////////////////////////////////
// Copyright FLINT Incorporated 2016.
// All Rights Reserved.
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <type_traits>

namespace color1 {

    enum class Color : unsigned
    {
        kNone = 0,
        kRed = 1 << 0, //! 1
        kGreen = 1 << 1, //! 2
        kBlue = 1 << 2, //! 4
        kWhite = kRed | kGreen | kBlue, //! 7
    };

    Color operator & (Color lhs, Color rhs)
    {
        return static_cast<Color>(
            static_cast<std::underlying_type<Color>::type>(lhs) &
            static_cast<std::underlying_type<Color>::type>(rhs));
    }

    Color operator | (Color lhs, Color rhs)
    {
        return static_cast<Color>(
            static_cast<std::underlying_type<Color>::type>(lhs) |
            static_cast<std::underlying_type<Color>::type>(rhs));
    }

    Color operator ^ (Color lhs, Color rhs)
    {
        return static_cast<Color>(
            static_cast<std::underlying_type<Color>::type>(lhs) ^
            static_cast<std::underlying_type<Color>::type>(rhs));
    }

    Color operator ~ (Color rhs)
    {
        return static_cast<Color>(
            ~static_cast<std::underlying_type<Color>::type>(rhs));
    }

    Color& operator |= (Color& lhs, Color rhs)
    {
        lhs = static_cast<Color> (
            static_cast<std::underlying_type<Color>::type>(lhs) |
            static_cast<std::underlying_type<Color>::type>(rhs));
        return lhs;
    }

    Color& operator &= (Color& lhs, Color rhs)
    {
        lhs = static_cast<Color> (
            static_cast<std::underlying_type<Color>::type>(lhs) &
            static_cast<std::underlying_type<Color>::type>(rhs));
        return lhs;
    }

    Color& operator ^= (Color &lhs, Color rhs)
    {
        lhs = static_cast<Color> (
            static_cast<std::underlying_type<Color>::type>(lhs) ^
            static_cast<std::underlying_type<Color>::type>(rhs));
        return lhs;
    }
}

template<typename T>
struct EnableBitMaskOperators
{
    static const bool enable = false;
};

#define ENABLE_BITMASK_OPERATORS(x)  \
template<>                           \
struct EnableBitMaskOperators<x>     \
{                                    \
    static const bool enable = true; \
};

template<typename T>
typename std::enable_if<EnableBitMaskOperators<T>::enable, T>::type operator | (T lhs, T rhs)
{
    using underlying = typename std::underlying_type<T>::type;
    return static_cast<T> (
        static_cast<underlying>(lhs) |
        static_cast<underlying>(rhs));
}

template<typename T>
typename std::enable_if<EnableBitMaskOperators<T>::enable, T>::type operator & (T lhs, T rhs)
{
    using underlying = typename std::underlying_type<T>::type;
    return static_cast<T> (
        static_cast<underlying>(lhs) &
        static_cast<underlying>(rhs));
}

namespace color2 {

    enum class Color : unsigned
    {
        kNone = 0,
        kRed = 1 << 0, //! 1
        kGreen = 1 << 1, //! 2
        kBlue = 1 << 2, //! 4
        kWhite = kRed | kGreen | kBlue, //! 7
    };
    ENABLE_BITMASK_OPERATORS(Color);
}