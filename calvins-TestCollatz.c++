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
    // eval
    // ----

    void test_eval_1 () {
		int* cache = new int[1000000];
		for (int i=0;i<1000000;++i) {
			cache[i] = 0;}
        const int v = collatz_eval(1, 10, cache);
        CPPUNIT_ASSERT(v == 20);
		delete [] cache;}

    void test_eval_2 () {
		int* cache = new int[1000000];
		for (int i=0;i<1000000;++i) {
			cache[i] = 0;}
        const int v = collatz_eval(100, 200, cache);
        CPPUNIT_ASSERT(v == 125);
		delete [] cache;}

    void test_eval_3 () {
		int* cache = new int[1000000];
		for (int i=0;i<1000000;++i) {
			cache[i] = 0;}
        const int v = collatz_eval(201, 210, cache);
        CPPUNIT_ASSERT(v == 89);
		delete [] cache;}

    void test_eval_4 () {
		int* cache = new int[1000000];
		for (int i=0;i<1000000;++i) {
			cache[i] = 0;}
        const int v = collatz_eval(900, 1000, cache);
        CPPUNIT_ASSERT(v == 174);
		delete [] cache;}

	// ----
	// calc
	// ----

	void test_calc_1 () {
		const int n = collatz_calc(5);
		CPPUNIT_ASSERT(n == 6);}

	void test_calc_2 () {
		const int n = collatz_calc(1);
		CPPUNIT_ASSERT(n == 1);}

	void test_calc_3 () {
		const int n = collatz_calc(7);
		CPPUNIT_ASSERT(n == 17);}

	// ----------
	// cache_calc
	// ----------

	void test_cache_calc_1 () {
		int* cache = new int[1000000];
		for (int i=0;i<1000000;++i) {
			cache[i] = 0;}
		const int n = collatz_cache_calc(5,cache);
		CPPUNIT_ASSERT(n == 6);
		CPPUNIT_ASSERT(cache[5] == 6); 
		delete [] cache;}

	void test_cache_calc_2 () {
		int* cache = new int[1000000];
		for (int i=0;i<1000000;++i) {
			cache[i] = 0;}
		const int n = collatz_cache_calc(1,cache);
		CPPUNIT_ASSERT(n == 1); 
		CPPUNIT_ASSERT(cache[5] == 0); 
		delete [] cache;}

	void test_cache_calc_3 () {
		int* cache = new int[1000000];
		for (int i=0;i<1000000;++i) {
			cache[i] = 0;}
		const int n = collatz_cache_calc(7,cache);
		CPPUNIT_ASSERT(n == 17);
		CPPUNIT_ASSERT(cache[5] == 6); 
		delete [] cache;}

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
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_calc_1);
    CPPUNIT_TEST(test_calc_2);
    CPPUNIT_TEST(test_calc_3);
    CPPUNIT_TEST(test_cache_calc_1);
    CPPUNIT_TEST(test_cache_calc_2);
    CPPUNIT_TEST(test_cache_calc_3);
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
