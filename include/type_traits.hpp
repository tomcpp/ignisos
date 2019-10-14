#pragma once

#include <stdint.h>

namespace ig {
template <typename T, T V>
struct integral_constant {
    static constexpr T value = V;
    using value_type = T;
    using type = integral_constant<T, V>;

    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept  { return value; }
};

template <typename T, T V>
using integral_constant_t = typename integral_constant<T, V>::type;

template <typename T, T V>
static constexpr T integral_constant_v = integral_constant<T, V>();


using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <bool B>
using bool_constant = integral_constant<bool, B>;

using yes_type = char;
struct no_type { char padding[8]; };

struct unused {};

struct argument_sink {
    template <typename... Args>
    argument_sink(Args&&...) {}
};

template <bool Condition, class ConditionIsTrueType, class ConditionIsFalseType>
struct type_select { using type = ConditionIsTrueType; };

template <typename ConditionIsTrueType, class ConditionIsFalseType>
struct type_select<false, ConditionIsTrueType, ConditionIsFalseType> { using type = ConditionIsFalseType; };

template <bool Condition, class ConditionIsTrueType, class ConditionIsFalseType>
using type_select_t = typename type_select<Condition, ConditionIsTrueType, ConditionIsFalseType>::type;

template <typename T, typename = unused, typename = unused>
struct first_type_select { using type = T; };

template <typename T, typename = unused, typename = unused>
using first_type_select_t = typename first_type_select<T, unused, unused>::type;

template <bool B1, bool B2, bool B3 = false, bool B4 = false, bool B5 = false>
struct type_or;

template <bool B1, bool B2, bool B3, bool B4, bool B5>
struct type_or { static constexpr bool value = true; };

template <>
struct type_or<false, false, false, false, false> { static constexpr bool value = false; };
}

template <bool B1, bool B2, bool B3 = true, bool B4 = true, bool B5 = true>
struct type_and;

template <bool B1, bool B2, bool B3, bool B4, bool B5>
struct type_and { static constexpr bool value = false; };

template <>
struct type_and<true, true, true, true, true> {static constexpr  bool value = true; };

template <int B1, int B2>
struct type_equal { static constexpr bool value = (B1 == B2); };

template <int B1, int B2>
struct type_not_equal { static constexpr bool value = (B1 != B2); };

template <bool B>
struct type_not { static constexpr bool value = true; };

template <>
struct type_not<true> { static constexpr bool value = false; };



template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> { using type = T; };

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <bool B, typename T = void>
struct disable_if {};

template <typename T>
struct disable_if<false, T> { using type = T; };

template <bool B, typename T = void>
using disable_if_t = typename disable_if<B, T>::type;

template <bool B, typename T, typename F>
struct conditional { using type = T; };

template <typename T, typename F>
struct conditional<false, T, F> { using type = F; };

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

template <typename T>
struct underlying_type { using type = __underlying_type(T); };

template <typename T>
using underlying_type_t = typename underlying_type<T>::type;

template <typename T>
struct remove_const { using type = T; };

template <typename T>
struct remove_const<const T> { using type = T; };

template <typename T>
struct remove_const<const T[]> { using type = T[]; };

template <typename T, uint64_t N>
struct remove_const<const T[N]> { using type = T[N]; };

template <typename T>
using remove_const_t = typename remove_const<T>::type;

template <typename T>
struct remove_volatile { using type = T; };

template <typename T>
struct remove_volatile<volatile T> { using type = T; };

template <typename T>
struct remove_volatile<volatile T[]> { using type = T[]; };

template <typename T, uint64_t N>
struct remove_volatile<volatile T[N]> { using type = T[N]; };

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template <typename T>
struct remove_cv { using type = remove_volatile_t<remove_const_t<T>>; };

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

namespace impl {
template <typename T> struct is_integral_helper : public ig::false_type {};

template <> struct is_integral_helper<unsigned char> : public ig::true_type {};
template <> struct is_integral_helper<unsigned short> : public ig::true_type {};
template <> struct is_integral_helper<unsigned int> : public ig::true_type {};
template <> struct is_integral_helper<unsigned long> : public ig::true_type {};
template <> struct is_integral_helper<unsigned long long> : public ig::true_type {};

template <> struct is_integral_helper<signed char> : public ig::true_type {};
template <> struct is_integral_helper<signed short> : public ig::true_type {};
template <> struct is_integral_helper<signed int> : public ig::true_type {};
template <> struct is_integral_helper<signed long> : public ig::true_type {};
template <> struct is_integral_helper<signed long long> : public ig::true_type {};

template <> struct is_integral_helper<char> : public ig::true_type {};
template <> struct is_integral_helper<bool> : public ig::true_type {};
}

template <typename T>
struct is_integral : public impl::is_integral_helper<remove_cv_t<T>> {};

template <typename T>
static constexpr bool is_integral_v = is_integral<T>::value;
