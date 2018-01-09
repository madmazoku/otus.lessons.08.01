#pragma once

/*! \file
    ip_print implementation
*/

#include <iostream>
#include <type_traits>

//! \brief check if type T has 'begin()' method
template<typename T>
struct has_begin {

    template<typename U>
    static std::true_type test(decltype(std::declval<U>().begin())*);

    template<typename U>
    static std::false_type test(...);

    static constexpr bool value = std::is_same< decltype(test<T>(nullptr)), std::true_type>::value;
};

//! \brief check if type T has 'end()' method
template<typename T>
struct has_end {

    template<typename U>
    static std::true_type test(decltype(std::declval<U>().end())*);

    template<typename U>
    static std::false_type test(...);

    static constexpr bool value = std::is_same< decltype(test<T>(nullptr)), std::true_type>::value;
};

//! \brief check if type T is tuple
/// @{
template<typename T>
struct is_tuple : std::false_type {};

/// @private
template<typename... Ts>
struct is_tuple<std::tuple<Ts...> > : std::true_type {};
/// @}

//! \brief check if tuple T has all elements of the same type
/// @{
template< typename T >
struct is_tuple_same;

/// @private
template< typename U, typename T, typename... Ts >
struct is_tuple_same<std::tuple<U, T, Ts...>> {
    static constexpr bool value = std::is_same<U, T>::value && is_tuple_same<std::tuple<T, Ts...>>::value;
};

/// @private
template< typename U, typename T >
struct is_tuple_same<std::tuple<U, T>> {
    static constexpr bool value = std::is_same<U, T>::value;
};

/// @private
template< typename U >
struct is_tuple_same<std::tuple<U>> {
    static constexpr bool value = true;
};
/// @}

//! \brief check if tuple T has all elements of the integral type
/// @{
template< typename T >
struct is_tuple_integral;

/// @private
template< typename T, typename... Ts >
struct is_tuple_integral<std::tuple<T, Ts...>> {
    static constexpr bool value = std::is_integral<T>::value && is_tuple_integral<std::tuple<Ts...>>::value ;
};

/// @private
template< typename T >
struct is_tuple_integral<std::tuple<T>> {
    static constexpr bool value = std::is_integral<T>::value;
};
/// @}

//! \brief print tuple helpers
/// @{
/// @private
template<typename T, size_t N, size_t S>
struct print_tuple {
    static void print(std::ostream &os, T t)
    {
        os << +std::get<N>(t) << '.';
        print_tuple<T, N+1, S>::print(os, t);
    }
};

/// @private
template<typename T, size_t N>
struct print_tuple<T, N, N> {
    static void print(std::ostream &os, T t)
    {
        os << +(std::get<N>(t));
    }
};
/// @}

//! \brief ip print helper
/// @{
//! helper ip print from integral type
/// @private
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type _ip_print(T t, std::ostream &os)
{
    for(size_t n = sizeof(T); n > 0; --n) {
        os << ((t >> ((n-1)<<3)) & 0xff);
        if(n - 1 > 0)
            os << '.';
    }
}

template<typename _T>
using remove_all_extents_t = typename std::remove_all_extents<_T>::type;

//! helper ip print from array of integral type
/// @private
template<typename T>
typename std::enable_if<std::is_array<T>::value && std::is_integral< remove_all_extents_t<T> >::value >::type _ip_print(const T &t, std::ostream &os)
{
    for(size_t n = 0; n < std::extent<T>::value; ++n) {
        if(n > 0)
            os << '.';
        os << +(t[n]);
    }
}

template<typename _T>
using remove_reference_t = typename std::remove_reference<_T>::type;

//! helper ip print from container of integral type
/// @private
template<typename T>
typename std::enable_if<has_begin<T>::value && has_end<T>::value && std::is_integral<remove_reference_t<decltype(*(std::declval<T>().begin()))>>::value>::type _ip_print(const T &t, std::ostream &os)
{
    for(auto i = t.begin(); i != t.end(); ++i) {
        if(i != t.begin())
            os << '.';
        os << +(*i);
    }
}

//! helper ip print from tuple of the same integral type
/// @private
template<typename T>
typename std::enable_if<is_tuple<T>::value && is_tuple_integral<T>::value && is_tuple_same<T>::value>::type _ip_print(const T &t, std::ostream &os)
{
    print_tuple<T, 0, std::tuple_size<T>::value - 1>::print(os, t);
}
/// @}

//!ip print from varuous types
template<typename T>
std::ostream& ip_print(const T &t, std::ostream &os)
{
    _ip_print<T>(t, os);
    return os;
}
