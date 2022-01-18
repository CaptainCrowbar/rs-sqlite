// This file is generated by the rs-update-tests script

#include "rs-unit-test.hpp"

int main(int argc, char** argv) {

    RS::UnitTest::begin_tests(argc, argv);

    // sqlite-test.cpp
    UNIT_TEST(rs_sqlite_connection)

    // version-test.cpp
    UNIT_TEST(rs_sqlite_version)

    // unit-test.cpp

    return RS::UnitTest::end_tests();

}
