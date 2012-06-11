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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

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
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(j == 10);}

    // ----
    // eval
    // ----

    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
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

    void my_test_eval_1 () {
	const int v = collatz_eval(50, 51);
	CPPUNIT_ASSERT(v == 25);}

    void my_test_eval_2 () {
	const int v = collatz_eval(18, 19);   // equal cycle length
	CPPUNIT_ASSERT(v == 21);}

    void my_test_eval_3 () {
	const int v = collatz_eval(21, 23);
	CPPUNIT_ASSERT(v == 16);}
    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    void my_test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 100, 200, 125);
        CPPUNIT_ASSERT(w.str() == "100 200 125\n");}

    void my_test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 201, 210, 89);
        CPPUNIT_ASSERT(w.str() == "201 210 89\n");}

    void my_test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 900, 1000, 174);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void my_test_solve_1 () {
        std::istringstream r("100 200\n900 1000\n201 210\n1 10\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "100 200 125\n900 1000 174\n201 210 89\n1 10 20\n");}

    void my_test_solve_2 () {
        std::istringstream r("900 1000\n201 210\n100 200\n1 10\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "900 1000 174\n201 210 89\n100 200 125\n1 10 20\n");}

    void my_test_solve_3 () {
        std::istringstream r("50 51\n18 19\n21 23\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "50 51 25\n18 19 21\n21 23 16\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(my_test_eval_1);
    CPPUNIT_TEST(my_test_eval_2);
    CPPUNIT_TEST(my_test_eval_3);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(me_test_print_1);
    CPPUNIT_TEST(me_test_print_2);
    CPPUNIT_TEST(me_test_print_3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(my_test_solve_1);
    CPPUNIT_TEST(my_test_solve_2);
    CPPUNIT_TEST(my_test_solve_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}