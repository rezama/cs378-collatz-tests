// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2011
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -ansi -pedantic -lcppunit -ldl -Wall TestCollatz.c++ -o TestCollatz.c++.app
    % valgrind TestCollatz.c++.app >& TestCollatz.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_one_ten () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}



    void test_read_ten_one () {
        std::istringstream r("10 1\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   10);
        CPPUNIT_ASSERT(j ==    1);}



    void test_read_five_five () {
        std::istringstream r("5 5\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   5);
        CPPUNIT_ASSERT(j ==   5);}


    void test_read_max_unsigned_int_value () {
        std::istringstream r("2147483647 2147483647\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   2147483647);
        CPPUNIT_ASSERT(j ==   2147483647);}


    void test_read_overflow () {
        std::istringstream r("2147483648 2147483648\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}

    // ----
    // eval
    // ----

    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_upper_bounds () {
        const int v = collatz_eval(1, 9);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_2 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_3 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_4 () {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);}

    void test_eval_full_range () {
        const int v = collatz_eval(1, 1000000);
        CPPUNIT_ASSERT(v == 525);}

    // ------------
    // collatz_cycle_length
    // ------------

    void test_collatz_cycle_length_min_value() {
        assert(collatz_cycle_length(1) == 1);
    }


    void test_collatz_cycle_length_2000() {
        assert(collatz_cycle_length(2000) == 113);
    }


    void test_collatz_cycle_length_max_int_value() {
        assert(collatz_cycle_length(2147483647) == 451);
    }

    // -----
    // print
    // -----

    void test_print_one_ten_twenty () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}


    void test_print_one_one_one () {
        std::ostringstream w;
        collatz_print(w, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");}


    void test_print_100_200_125 () {
        std::ostringstream w;
        collatz_print(w, 100, 200, 125);
        CPPUNIT_ASSERT(w.str() == "100 200 125\n");}


    void test_print_max_int_values () {
        std::ostringstream w;
        collatz_print(w, 2147483647, 2147483647, 2147483647);
        CPPUNIT_ASSERT(w.str() == "2147483647 2147483647 2147483647\n");}



    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);

        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_1_999999 () {
        std::istringstream r("1 999999\n");
        std::ostringstream w;
        collatz_solve(r, w);

        CPPUNIT_ASSERT(w.str() == "1 999999 525\n");}


    void test_solve_999999_1 () {
        std::istringstream r("999999 1\n");
        std::ostringstream w;
        collatz_solve(r, w);

        CPPUNIT_ASSERT(w.str() == "999999 1 525\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_one_ten);
    CPPUNIT_TEST(test_read_ten_one);
    CPPUNIT_TEST(test_read_five_five);
    CPPUNIT_TEST(test_read_max_unsigned_int_value);
    CPPUNIT_TEST(test_read_overflow);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_upper_bounds);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_full_range);
    CPPUNIT_TEST(test_collatz_cycle_length_min_value);
    CPPUNIT_TEST(test_collatz_cycle_length_2000);
    CPPUNIT_TEST(test_collatz_cycle_length_max_int_value);
    CPPUNIT_TEST(test_print_one_ten_twenty);
    CPPUNIT_TEST(test_print_one_one_one);
    CPPUNIT_TEST(test_print_100_200_125);
    CPPUNIT_TEST(test_print_max_int_values);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_1_999999);
    CPPUNIT_TEST(test_solve_999999_1);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
