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
// container checks
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
// tuple checks
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
    static void print(std::ostream &os, T t) {
        os << std::get<N>(t) << '.';
        print_tuple<T, N+1, S>::print(os, t);
    }
};

template<typename T, size_t N>
struct print_tuple<T, N, N> {
    static void print(std::ostream &os, T t) {
        os << std::get<N>(t);
    }
};
////////////////////////////////////////


template<typename T>
typename std::enable_if_t<std::is_integral<T>::value> _ip_print(T t, std::ostream &os) {
    os << "integral: " << t << std::endl;
    os << "\tsize: " << sizeof(T) << std::endl;
    os << "\tvalue: ";
    for(size_t n = sizeof(T); n > 0; --n) {
        std::cout << ((t >> ((n-1)<<3)) & 0xff);
        if(n - 1 > 0)
            std::cout << '.';
    }
    std::cout << std::endl;
}

template<typename T>
typename std::enable_if_t<std::is_array<T>::value && std::is_integral< std::remove_all_extents_t<T> >::value > _ip_print(const T &t, std::ostream &os) {
    os << "array: " << std::endl;
    os << "\trank: " << std::rank<T>::value << std::endl;
    os << "\textent: " << std::extent<T>::value << std::endl;
    os << "\tvalue: ";
    for(size_t n = 0; n < std::extent<T>::value; ++n) {
        if(n > 0)
            os << '.';
        os << t[n];
    }
    std::cout << std::endl;
}

template<typename T>
typename std::enable_if_t<has_begin<T>::value && has_end<T>::value && std::is_integral<std::remove_reference_t<decltype(*(std::declval<T>().begin()))>>::value> _ip_print(const T &t, std::ostream &os) {
    os << "container: " << std::endl;
    os << "\tvalue: ";
    for(auto i = t.begin(); i != t.end(); ++i) {
        if(i != t.begin())
            os << '.';
        os << *i;
    }
    std::cout << std::endl;
}

template<typename T>
typename std::enable_if_t<is_tuple<T>::value> _ip_print(const T &t, std::ostream &os) {
    os << "tuple: " << std::endl;
    os << "\tis_integral: " << is_tuple_integral<T>::value << std::endl;
    os << "\tvalue: ";
    print_tuple<T, 0, std::tuple_size<T>::value - 1>::print(os, t);
    std::cout << std::endl;
}


template<typename T>
void ip_print(const T &t, std::ostream &os) {
    os << "print from type: " << pretty_type_name<T>() << std::endl;
    os << "\tintegral: "  << std::is_integral<T>::value << std::endl;
    os << "\tpointer: " << std::is_pointer<T>::value << std::endl;
    os << "\tarray: " << std::is_array<T>::value << std::endl;
    os << "\thas_iterator: " << has_iterator<T>::value << std::endl;
    os << "\thas_begin: " << has_begin<T>::value << std::endl;
    os << "\thas_end: " << has_end<T>::value << std::endl;
   _ip_print<T>(t, os);
    os << std::endl;
}