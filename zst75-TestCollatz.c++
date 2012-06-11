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

    void test_read () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    // ----
    // zst75 read tests
    // ----
    
    void zst75_test_read_1 () {
        std::istringstream r("5432 67899\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    5432);
        CPPUNIT_ASSERT(j ==   67899);}
    
    void zst75_test_read_2 () {
        std::istringstream r("432 678009\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    432);
        CPPUNIT_ASSERT(j ==   678009);}
    
    void zst75_test_read_3 () {
        std::istringstream r("999999 1000000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    999999);
        CPPUNIT_ASSERT(j ==   1000000);}
    
    
    // ----
    // eval
    // ----

    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
        std::cout << v << std::endl;
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

    // ----
    // zst75 eval test
    // ----
    
    void zst75_test_eval_1 () {
        const int v = collatz_eval(1, 2);
        CPPUNIT_ASSERT(v == 2);}
    
    void zst75_test_eval_2 () {
        const int v = collatz_eval(999999, 1000000);
	CPPUNIT_ASSERT(v == 259);}
    
    void zst75_test_eval_3 () {
        const int v = collatz_eval(368239, 368923);
	CPPUNIT_ASSERT(v == 317);}
    
    void zst75_test_eval_4 () {
        const int v = collatz_eval(599928, 604700);
        CPPUNIT_ASSERT(v == 403);}
    
    
    // ----
    // zst75 eval single helper test
    // ----
    
    void zst75_test_eval_single_helper_1 () {
        const int v = collatz_eval_single_helper(1, 0);
        CPPUNIT_ASSERT(v == 1);}
    
    void zst75_test_eval_single_helper_2 () {
        const int v = collatz_eval_single_helper(5, 100);
        CPPUNIT_ASSERT(v == 106);}
    
    void zst75_test_eval_single_helper_3 () {
        const int v = collatz_eval_single_helper(910107, 0);
        CPPUNIT_ASSERT(v == 476);}

    // ----
    // zst75 eval single test
    // ----
    
    void zst75_test_eval_single_1 () {
        const int v = collatz_eval_single(1);
        CPPUNIT_ASSERT(v == 1);}
    
    void zst75_test_eval_single_2 () {
        const int v = collatz_eval_single(5);
        CPPUNIT_ASSERT(v == 6);}
    
    void zst75_test_eval_single_3 () {
        const int v = collatz_eval_single(910107);
        CPPUNIT_ASSERT(v == 476);}
    
    
    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
    
    // -----
    // zst75 print tests
    // -----
    
    void zst75_test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 999999, 1000000, 999999);
        CPPUNIT_ASSERT(w.str() == "999999 1000000 999999\n");}
    
    void zst75_test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 1, 2, 2);
        CPPUNIT_ASSERT(w.str() == "1 2 2\n");}
    
    void zst75_test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 1, 1000000, 999999);
        CPPUNIT_ASSERT(w.str() == "1 1000000 999999\n");}
    

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
    
    // -----
    // zst75 solve tests
    // -----
    
    void zst75_test_solve_1 () {
        std::istringstream r("999999 1000000\n122123 123123\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "999999 1000000 259\n122123 123123 318\n201 210 89\n900 1000 174\n");}
    
    void zst75_test_solve_2 () {
        std::istringstream r("900 1000\n201 210\n100 200\n1 10\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n201 210 89\n100 200 125\n1 10 20\n");}
    
    void zst75_test_solve_3 () {
        std::istringstream r("900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(zst75_test_read_1);
    CPPUNIT_TEST(zst75_test_read_2);
    CPPUNIT_TEST(zst75_test_read_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(zst75_test_eval_1);
    CPPUNIT_TEST(zst75_test_eval_2);
    CPPUNIT_TEST(zst75_test_eval_3);
    CPPUNIT_TEST(zst75_test_eval_4);
    CPPUNIT_TEST(zst75_test_eval_single_1);
    CPPUNIT_TEST(zst75_test_eval_single_2);
    CPPUNIT_TEST(zst75_test_eval_single_3);
    CPPUNIT_TEST(zst75_test_eval_single_helper_1);
    CPPUNIT_TEST(zst75_test_eval_single_helper_2);
    CPPUNIT_TEST(zst75_test_eval_single_helper_3);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(zst75_test_print_1);
    CPPUNIT_TEST(zst75_test_print_2);
    CPPUNIT_TEST(zst75_test_print_3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(zst75_test_solve_1);
    CPPUNIT_TEST(zst75_test_solve_2);
    CPPUNIT_TEST(zst75_test_solve_3);
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
