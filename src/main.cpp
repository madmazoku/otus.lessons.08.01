
#include <iostream>
#include <boost/program_options.hpp>
#include "../bin/version.h"

#include <vector>
#include <list>
#include <tuple>
#include "ip_print.h"

/*! \file
  application entry point

  Usage:

    \--help,-h print help

    \--version,-v print application and boost version
*/

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

        std::cout << "Done nothing" << std::endl;

    }

    return 0;
}
