#pragma once

#include <iostream>
#include <type_traits>

template<class T>
std::string pretty_type_name()
{
    std::stringstream ss;
    ss << '[' << sizeof(T) << "] " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
    return ss.str();
}

////////////////////////////////////////
// container
////////////////////////////////////////
template<typename T>
struct has_iterator {

    template<typename U>
    static std::true_type test(typename U::const_iterator*);

    template<typename U>
    static std::false_type test(...);

    static constexpr bool value = std::is_same< decltype(test<T>(nullptr)), std::true_type>::value;
};

template<typename T>
struct has_begin {

    template<typename U>
    static std::true_type test(decltype(std::declval<U>().begin())*);

    template<typename U>
    static std::false_type test(...);

    static constexpr bool value = std::is_same< decltype(test<T>(nullptr)), std::true_type>::value;
};

template<typename T>
struct has_end {

    template<typename U>
    static std::true_type test(decltype(std::declval<U>().begin())*);

    template<typename U>
    static std::false_type test(...);

    static constexpr bool value = std::is_same< decltype(test<T>(nullptr)), std::true_type>::value;
};
////////////////////////////////////////

////////////////////////////////////////
// tuple
////////////////////////////////////////
template<typename T>
struct is_tuple : std::false_type {};

template<typename... Ts>
struct is_tuple<std::tuple<Ts...> > : std::true_type {};

template< typename T >
struct is_tuple_integral;

template< typename T, typename... Ts >
struct is_tuple_integral<std::tuple<T, Ts...>> {
    static constexpr bool value = std::is_integral<T>::value && is_tuple_integral<std::tuple<Ts...>>::value ;
};

template< typename T >
struct is_tuple_integral<std::tuple<T>> {
    static constexpr bool value = std::is_integral<T>::value;
};

template<typename T, size_t N, size_t S>
struct print_tuple {
    static void print(std::ostream &os, T t)
    {
        os << +std::get<N>(t) << '.';
        print_tuple<T, N+1, S>::print(os, t);
    }
};

template<typename T, size_t N>
struct print_tuple<T, N, N> {
    static void print(std::ostream &os, T t)
    {
        os << +(std::get<N>(t));
    }
};
////////////////////////////////////////

template<typename T>
typename std::enable_if_t<std::is_integral<T>::value> _ip_print(T t, std::ostream &os)
{
    for(size_t n = sizeof(T); n > 0; --n) {
        os << ((t >> ((n-1)<<3)) & 0xff);
        if(n - 1 > 0)
            os << '.';
    }
}

template<typename T>
typename std::enable_if_t<std::is_array<T>::value && std::is_integral< std::remove_all_extents_t<T> >::value > _ip_print(const T &t, std::ostream &os)
{
    for(size_t n = 0; n < std::extent<T>::value; ++n) {
        if(n > 0)
            os << '.';
        os << +(t[n]);
    }
}

template<typename T>
typename std::enable_if_t<has_begin<T>::value && has_end<T>::value && std::is_integral<std::remove_reference_t<decltype(*(std::declval<T>().begin()))>>::value> _ip_print(const T &t, std::ostream &os)
{
    for(auto i = t.begin(); i != t.end(); ++i) {
        if(i != t.begin())
            os << '.';
        os << +(*i);
    }
}

template<typename T>
typename std::enable_if_t<is_tuple<T>::value> _ip_print(const T &t, std::ostream &os)
{
    print_tuple<T, 0, std::tuple_size<T>::value - 1>::print(os, t);
}

template<typename T>
std::ostream& ip_print(const T &t, std::ostream &os)
{
    _ip_print<T>(t, os);
    return os;
}
