// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2011
// Glenn P. Downing
//
// Specific Implementation: Chris Renke
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
#include <stdint.h> // for large ints

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

    void test_read_1 () {
        std::istringstream r("1 10\n");
        uint64_t i;
        uint64_t j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}
    void test_read_2 () {
        std::istringstream r("19 91\n");
        uint64_t i;
        uint64_t j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   19);
        CPPUNIT_ASSERT(j ==   91);}
    void test_read_3 () {
        std::istringstream r("101 510\n");
        uint64_t i;
        uint64_t j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   101);
        CPPUNIT_ASSERT(j ==   510);}
    void test_read_4 () {
        std::istringstream r("22221 222210\n");
        uint64_t i;
        uint64_t j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   22221);
        CPPUNIT_ASSERT(j ==  222210);}

    // ----
    // eval
    // ----

    void test_eval_1 () {
        const uint64_t v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_2 () {
        const uint64_t v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_3 () {
        const uint64_t v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_4 () {
        const uint64_t v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);}

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 741229, 741690, 318);
        CPPUNIT_ASSERT(w.str() == "741229 741690 318\n");}
    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 6083, 6878, 262);
        CPPUNIT_ASSERT(w.str() == "6083 6878 262\n");}
    void test_print_4 () {
        std::ostringstream w;
        collatz_print(w, 178904, 179073, 272);
        CPPUNIT_ASSERT(w.str() == "178904 179073 272\n");}

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
    void test_solve_2 () {
        std::istringstream r("6083 6878\n75317 75976\n73517 73719\n84746 85100\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "6083 6878 262\n75317 75976 294\n73517 73719 232\n84746 85100 258\n");}
    void test_solve_3 () {
        std::istringstream r("1000000 999999\n99 3\n9 3\n1 99\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1000000 999999 259\n99 3 119\n9 3 20\n1 99 119\n");}
    void test_solve_4 () {
        std::istringstream r("178904 179073\n805352 805527\n741229 741690\n697661 698018\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "178904 179073 272\n805352 805527 331\n741229 741690 318\n697661 698018 261\n");}

    // -----
    // init - only really one way to test it, can't really write 3 of these
    // -----  
    
    void test_init () {
        bool valid = init_cache();
        CPPUNIT_ASSERT(valid);}
         
    // ------------
    // collatz_recursive_cache
    // ------------
    void test_recurse_1 () {
        const uint64_t v = collatz_recursive_cache(111111);
        CPPUNIT_ASSERT(v == 116);}

    void test_recurse_2 () {
        const uint64_t v = collatz_recursive_cache(20);
        CPPUNIT_ASSERT(v == 8);}

    void test_recurse_3 () {
        const uint64_t v = collatz_recursive_cache(211210);
        CPPUNIT_ASSERT(v == 143);}

    void test_recurse_4 () {
        const uint64_t v = collatz_recursive_cache(981929);
        CPPUNIT_ASSERT(v == 197);}

    
    
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_init);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);   
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
