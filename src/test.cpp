#define BOOST_TEST_MODULE TestMain
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <vector>
#include <list>
#include <deque>

#include "../bin/version.h"
#include "ip_print.h"

template<typename T>
std::string ip2str(const T &t)
{
    std::stringstream ss;
    ip_print(t, ss);
    return ss.str();
}

BOOST_AUTO_TEST_SUITE( test_suite )

BOOST_AUTO_TEST_CASE( test_version )
{
    BOOST_CHECK_GT(build_version(), 0);
}

BOOST_AUTO_TEST_CASE( test_integral )
{
    BOOST_CHECK_EQUAL(ip2str((uint8_t)0x01), "1");
    BOOST_CHECK_EQUAL(ip2str((uint16_t)0x0001), "0.1");
    BOOST_CHECK_EQUAL(ip2str((uint32_t)0x00000001), "0.0.0.1");
    BOOST_CHECK_EQUAL(ip2str((uint64_t)0x0000000000000001), "0.0.0.0.0.0.0.1");

    BOOST_CHECK_EQUAL(ip2str((uint8_t)0x01), "1");
    BOOST_CHECK_EQUAL(ip2str((uint16_t)0x0102), "1.2");
    BOOST_CHECK_EQUAL(ip2str((uint32_t)0x01020304), "1.2.3.4");
    BOOST_CHECK_EQUAL(ip2str((uint64_t)0x0102030405060708), "1.2.3.4.5.6.7.8");

    BOOST_CHECK_EQUAL(ip2str((uint8_t)0x00), "0");
    BOOST_CHECK_EQUAL(ip2str((uint16_t)0x0000), "0.0");
    BOOST_CHECK_EQUAL(ip2str((uint32_t)0x00020300), "0.2.3.0");
    BOOST_CHECK_EQUAL(ip2str((uint64_t)0x0002030405060700), "0.2.3.4.5.6.7.0");

    BOOST_CHECK_EQUAL(ip2str((int8_t)0x01), "1");
    BOOST_CHECK_EQUAL(ip2str((int16_t)0x0001), "0.1");
    BOOST_CHECK_EQUAL(ip2str((int32_t)0x00000001), "0.0.0.1");
    BOOST_CHECK_EQUAL(ip2str((int64_t)0x0000000000000001), "0.0.0.0.0.0.0.1");

    BOOST_CHECK_EQUAL(ip2str((int8_t)0x01), "1");
    BOOST_CHECK_EQUAL(ip2str((int16_t)0x0102), "1.2");
    BOOST_CHECK_EQUAL(ip2str((int32_t)0x01020304), "1.2.3.4");
    BOOST_CHECK_EQUAL(ip2str((int64_t)0x0102030405060708), "1.2.3.4.5.6.7.8");

    BOOST_CHECK_EQUAL(ip2str((int8_t)0x00), "0");
    BOOST_CHECK_EQUAL(ip2str((int16_t)0x0000), "0.0");
    BOOST_CHECK_EQUAL(ip2str((int32_t)0x00020300), "0.2.3.0");
    BOOST_CHECK_EQUAL(ip2str((int64_t)0x0002030405060700), "0.2.3.4.5.6.7.0");
}

template<typename T>
void test_array()
{
    T a1[] = {1};
    T a2[] = {0, 0};
    T a3[] = {0, 1, 0};
    T a4[] = {1, 2, 3, 4};
    T a5[] = {1, 0, 0, 0, 5};

    BOOST_CHECK_EQUAL(ip2str(a1), "1");
    BOOST_CHECK_EQUAL(ip2str(a2), "0.0");
    BOOST_CHECK_EQUAL(ip2str(a3), "0.1.0");
    BOOST_CHECK_EQUAL(ip2str(a4), "1.2.3.4");
    BOOST_CHECK_EQUAL(ip2str(a5), "1.0.0.0.5");

}

BOOST_AUTO_TEST_CASE( test_array_uint8 )
{
    test_array<uint8_t>();
}
BOOST_AUTO_TEST_CASE( test_array_uint16 )
{
    test_array<uint16_t>();
}
BOOST_AUTO_TEST_CASE( test_array_uint32 )
{
    test_array<uint32_t>();
}
BOOST_AUTO_TEST_CASE( test_array_uint64 )
{
    test_array<uint64_t>();
}

BOOST_AUTO_TEST_CASE( test_array_int8 )
{
    test_array<int8_t>();
}
BOOST_AUTO_TEST_CASE( test_array_int16 )
{
    test_array<int16_t>();
}
BOOST_AUTO_TEST_CASE( test_array_int32 )
{
    test_array<int32_t>();
}
BOOST_AUTO_TEST_CASE( test_array_int64 )
{
    test_array<int64_t>();
}

BOOST_AUTO_TEST_CASE( test_array_negative )
{
    int8_t a8[] = {1, -1, 1, -1};
    int16_t a16[] = {1, -1, 1, -1};
    int32_t a32[] = {1, -1, 1, -1};
    int64_t a64[] = {1, -1, 1, -1};

    BOOST_CHECK_EQUAL(ip2str(a8), "1.-1.1.-1");
    BOOST_CHECK_EQUAL(ip2str(a16), "1.-1.1.-1");
    BOOST_CHECK_EQUAL(ip2str(a32), "1.-1.1.-1");
    BOOST_CHECK_EQUAL(ip2str(a64), "1.-1.1.-1");
}

template<typename T>
void test_container()
{
    T c1, c2, c3, c4, c5;
    c1.push_back(1);
    c2.push_back(0);
    c2.push_back(0);
    c3.push_back(0);
    c3.push_back(1);
    c3.push_back(0);
    c4.push_back(1);
    c4.push_back(2);
    c4.push_back(3);
    c4.push_back(4);
    c5.push_back(1);
    c5.push_back(0);
    c5.push_back(0);
    c5.push_back(0);
    c5.push_back(5);

    BOOST_CHECK_EQUAL(ip2str(c1), "1");
    BOOST_CHECK_EQUAL(ip2str(c2), "0.0");
    BOOST_CHECK_EQUAL(ip2str(c3), "0.1.0");
    BOOST_CHECK_EQUAL(ip2str(c4), "1.2.3.4");
    BOOST_CHECK_EQUAL(ip2str(c5), "1.0.0.0.5");
}

BOOST_AUTO_TEST_CASE( test_vector_uint8 )
{
    test_container< std::vector<uint8_t> >();
}
BOOST_AUTO_TEST_CASE( test_vector_uint16 )
{
    test_container< std::vector<uint16_t> >();
}
BOOST_AUTO_TEST_CASE( test_vector_uint32 )
{
    test_container< std::vector<uint32_t> >();
}
BOOST_AUTO_TEST_CASE( test_vector_uint64 )
{
    test_container< std::vector<uint64_t> >();
}

BOOST_AUTO_TEST_CASE( test_vector_int8 )
{
    test_container< std::vector<int8_t> >();
}
BOOST_AUTO_TEST_CASE( test_vector_int16 )
{
    test_container< std::vector<int16_t> >();
}
BOOST_AUTO_TEST_CASE( test_vector_int32 )
{
    test_container< std::vector<int32_t> >();
}
BOOST_AUTO_TEST_CASE( test_vector_int64 )
{
    test_container< std::vector<int64_t> >();
}

BOOST_AUTO_TEST_CASE( test_list_uint8 )
{
    test_container< std::list<uint8_t> >();
}
BOOST_AUTO_TEST_CASE( test_list_uint16 )
{
    test_container< std::list<uint16_t> >();
}
BOOST_AUTO_TEST_CASE( test_list_uint32 )
{
    test_container< std::list<uint32_t> >();
}
BOOST_AUTO_TEST_CASE( test_list_uint64 )
{
    test_container< std::list<uint64_t> >();
}

BOOST_AUTO_TEST_CASE( test_list_int8 )
{
    test_container< std::list<int8_t> >();
}
BOOST_AUTO_TEST_CASE( test_list_int16 )
{
    test_container< std::list<int16_t> >();
}
BOOST_AUTO_TEST_CASE( test_list_int32 )
{
    test_container< std::list<int32_t> >();
}
BOOST_AUTO_TEST_CASE( test_list_int64 )
{
    test_container< std::list<int64_t> >();
}

BOOST_AUTO_TEST_CASE( test_deque_uint8 )
{
    test_container< std::deque<uint8_t> >();
}
BOOST_AUTO_TEST_CASE( test_deque_uint16 )
{
    test_container< std::deque<uint16_t> >();
}
BOOST_AUTO_TEST_CASE( test_deque_uint32 )
{
    test_container< std::deque<uint32_t> >();
}
BOOST_AUTO_TEST_CASE( test_deque_uint64 )
{
    test_container< std::deque<uint64_t> >();
}

BOOST_AUTO_TEST_CASE( test_deque_int8 )
{
    test_container< std::deque<int8_t> >();
}
BOOST_AUTO_TEST_CASE( test_deque_int16 )
{
    test_container< std::deque<int16_t> >();
}
BOOST_AUTO_TEST_CASE( test_deque_int32 )
{
    test_container< std::deque<int32_t> >();
}
BOOST_AUTO_TEST_CASE( test_deque_int64 )
{
    test_container< std::deque<int64_t> >();
}

template<typename T>
void test_container_negative()
{
    std::vector<T> v;
    std::list<T> l;
    std::deque<T> d;

    v.push_back(1);
    v.push_back(-1);
    v.push_back(1);
    v.push_back(-1);

    l.push_back(1);
    l.push_back(-1);
    l.push_back(1);
    l.push_back(-1);

    d.push_back(1);
    d.push_back(-1);
    d.push_back(1);
    d.push_back(-1);

    BOOST_CHECK_EQUAL(ip2str(v), "1.-1.1.-1");
    BOOST_CHECK_EQUAL(ip2str(l), "1.-1.1.-1");
    BOOST_CHECK_EQUAL(ip2str(d), "1.-1.1.-1");
}

BOOST_AUTO_TEST_CASE( test_container_negative_int8 )
{
    test_container_negative<int8_t>();
}
BOOST_AUTO_TEST_CASE( test_container_negative_int16 )
{
    test_container_negative<int16_t>();
}
BOOST_AUTO_TEST_CASE( test_container_negative_int32 )
{
    test_container_negative<int32_t>();
}
BOOST_AUTO_TEST_CASE( test_container_negative_int64 )
{
    test_container_negative<int64_t>();
}

template<typename T>
void test_tuple()
{
    auto t1 = std::make_tuple((T)1);
    auto t2 = std::make_tuple((T)0, (T)0);
    auto t3 = std::make_tuple((T)0, (T)1, (T)0);
    auto t4 = std::make_tuple((T)1, (T)2, (T)3, (T)4);
    auto t5 = std::make_tuple((T)1, (T)0, (T)0, (T)0, (T)5);

    BOOST_CHECK_EQUAL(ip2str(t1), "1");
    BOOST_CHECK_EQUAL(ip2str(t2), "0.0");
    BOOST_CHECK_EQUAL(ip2str(t3), "0.1.0");
    BOOST_CHECK_EQUAL(ip2str(t4), "1.2.3.4");
    BOOST_CHECK_EQUAL(ip2str(t5), "1.0.0.0.5");
}

BOOST_AUTO_TEST_CASE( test_tuple_uint8 )
{
    test_tuple<uint8_t>();
}
BOOST_AUTO_TEST_CASE( test_tuple_uint16 )
{
    test_tuple<uint16_t>();
}
BOOST_AUTO_TEST_CASE( test_tuple_uint32 )
{
    test_tuple<uint32_t>();
}
BOOST_AUTO_TEST_CASE( test_tuple_uint64 )
{
    test_tuple<uint64_t>();
}

BOOST_AUTO_TEST_CASE( test_tuple_int8 )
{
    test_tuple<int8_t>();
}
BOOST_AUTO_TEST_CASE( test_tuple_int16 )
{
    test_tuple<int16_t>();
}
BOOST_AUTO_TEST_CASE( test_tuple_int32 )
{
    test_tuple<int32_t>();
}
BOOST_AUTO_TEST_CASE( test_tuple_int64 )
{
    test_tuple<int64_t>();
}

BOOST_AUTO_TEST_CASE( test_tuple_negative )
{
    auto t8 = std::make_tuple((int8_t)1, (int8_t)-1, (int8_t)1, (int8_t)-1);
    auto t16 = std::make_tuple((int16_t)1, (int16_t)-1, (int16_t)1, (int16_t)-1);
    auto t32 = std::make_tuple((int32_t)1, (int32_t)-1, (int32_t)1, (int32_t)-1);
    auto t64 = std::make_tuple((int64_t)1, (int64_t)-1, (int64_t)1, (int64_t)-1);

    BOOST_CHECK_EQUAL(ip2str(t8), "1.-1.1.-1");
    BOOST_CHECK_EQUAL(ip2str(t16), "1.-1.1.-1");
    BOOST_CHECK_EQUAL(ip2str(t32), "1.-1.1.-1");
    BOOST_CHECK_EQUAL(ip2str(t64), "1.-1.1.-1");
}

BOOST_AUTO_TEST_CASE( test_tuple_getero )
{
    auto t = std::make_tuple((uint8_t)1, (uint16_t)2, (uint32_t)3, (uint64_t)4, (int8_t)5, (int16_t)6, (int32_t)7, (int64_t)8);

    BOOST_CHECK_EQUAL(ip2str(t), "1.2.3.4.5.6.7.8");
}

BOOST_AUTO_TEST_SUITE_END()
