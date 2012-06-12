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

    void test_read_1 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_read_2 () {
        std::istringstream r("");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);}

	// -----
	// cycle
	// -----

	void test_cycle_1 () {
		const int v = collatz_cycle(1);
		CPPUNIT_ASSERT(v == 1);}

	void test_cycle_2 () {
		const int v = collatz_cycle(2);
		CPPUNIT_ASSERT(v == 2);}

	void test_cycle_3 () {
		const int v = collatz_cycle(3);
		CPPUNIT_ASSERT(v == 8);}

	void test_cycle_4 () {
		const int v = collatz_cycle(4);
		CPPUNIT_ASSERT(v == 3);}

	void test_cycle_5 () {
		const int v = collatz_cycle(5);
		CPPUNIT_ASSERT(v == 6);}

	void test_cycle_6 () {
		const int v = collatz_cycle(6);
		CPPUNIT_ASSERT(v == 9);}

	void test_cycle_7 () {
		const int v = collatz_cycle(7);
		CPPUNIT_ASSERT(v == 17);}

	void test_cycle_8 () {
		const int v = collatz_cycle(8);
		CPPUNIT_ASSERT(v == 4);}

	void test_cycle_9 () {
		const int v = collatz_cycle(9);
		CPPUNIT_ASSERT(v == 20);}

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

	void test_eval_5 () {
		const int v = collatz_eval(10, 1);
		CPPUNIT_ASSERT(v == 20);}

	void test_eval_6() {
		const int v = collatz_eval(5100, 5000);
		CPPUNIT_ASSERT(v == 179);}

	void test_eval_7() {
		const int v = collatz_eval(803885, 39210);
		CPPUNIT_ASSERT(v == 470);}

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_cycle_1);
	CPPUNIT_TEST(test_cycle_2);
	CPPUNIT_TEST(test_cycle_3);
	CPPUNIT_TEST(test_cycle_4);
	CPPUNIT_TEST(test_cycle_5);
	CPPUNIT_TEST(test_cycle_6);
	CPPUNIT_TEST(test_cycle_7);
	CPPUNIT_TEST(test_cycle_8);
	CPPUNIT_TEST(test_cycle_9);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
	CPPUNIT_TEST(test_eval_5);
	CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_solve);
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
