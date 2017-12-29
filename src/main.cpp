
#include <iostream>
#include <boost/program_options.hpp>
#include "../bin/version.h"

#include <vector>
#include <list>
#include <tuple>
#include "ip_print.h"

void body() {
    ip_print((int8_t)0x01, std::cout);
    ip_print((int16_t)0x0102, std::cout);
    ip_print((int32_t)0x01020304, std::cout);
    ip_print((int64_t)0x0102030405060708, std::cout);
    ip_print("123", std::cout); // char [4] = {'1', '2', '3', '\0'}

    int a[3] = {1, 2, 3};
    ip_print(a, std::cout);

    std::vector<int> v{1, 2, 3};
    ip_print(v, std::cout);

    std::list<long> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    ip_print(l, std::cout);

    auto t = std::make_tuple(1, 2, 3);
    ip_print(t, std::cout);
}

int main(int argc, char** argv) 
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
    ("help,h", "print usage message")
    ("version,v", "print version number");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
    } else if (vm.count("version")) {
        std::cout << "Build version: " << build_version() << std::endl;
        std::cout << "Boost version: " << (BOOST_VERSION / 100000) << '.' << (BOOST_VERSION / 100 % 1000) << '.' << (BOOST_VERSION % 100) << std::endl;
    } else {

        body();

    }

    return 0;
}
