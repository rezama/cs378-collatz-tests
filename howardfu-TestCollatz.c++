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

	void test_read_2() {
		std::istringstream r("1 1\n");
		int i, j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(j == 1);
	}

	void test_read_3() {
		std::istringstream r("  999999     999999\n");
		int i, j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 999999);
		CPPUNIT_ASSERT(j == 999999);
	}

	void test_read_4() {
		std::istringstream r("oawjegioa ogawieoj\n");
		int i, j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == false);
	}

	void test_read_5() {
		std::istringstream r("1 999999\n");
		int i, j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(j == 999999);
	}

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
        const int v = collatz_eval(800000, 900000);
        CPPUNIT_ASSERT(v == 525);}

    void test_eval_6 () {
        const int v = collatz_eval(1, 999999);
        CPPUNIT_ASSERT(v == 525);}

    void test_eval_7 () {
        const int v = collatz_eval(1, 1);
        CPPUNIT_ASSERT(v == 1);}

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
   
    void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 1, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n");}

    void test_print_3 () {
        std::ostringstream w;
        collatz_print(w, 1, 999999, 525);
        CPPUNIT_ASSERT(w.str() == "1 999999 525\n");}

    void test_print_4 () {
        std::ostringstream w;
        collatz_print(w, 100, 100, 9000);
        CPPUNIT_ASSERT(w.str() == "100 100 9000\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    void test_solve_2() {
        std::istringstream r("600000 900000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "600000 900000 525\n");
	}

    void test_solve_3() {
        std::istringstream r("1 999999\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 999999 525\n");
	}

    void test_solve_4() {
        std::istringstream r("1 1\n2 2\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1 1\n2 2 2\n");
	}


    void test_solve_5() {
        std::istringstream r("\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");
	}

    // ----
    // initcache
    // ----

    void test_initcache () {
    	unsigned long i = collatz_initcache();
    	CPPUNIT_ASSERT(cache[0]==0);
    	CPPUNIT_ASSERT(cache[27]==112);
    	CPPUNIT_ASSERT(cache[1]==1);
    	CPPUNIT_ASSERT(cache[2]==2);
    	CPPUNIT_ASSERT(cache[3]==8);
    	CPPUNIT_ASSERT(i == 1000000);
    }

    void test_initcache_2 () {
        for(int z = 0; z<1000000; ++z)
		cache[z] = 0;
    	unsigned long i = collatz_initcache();
    	CPPUNIT_ASSERT(cache[0]==0);
    	CPPUNIT_ASSERT(cache[27]==112);
    	CPPUNIT_ASSERT(cache[1]==1);
    	CPPUNIT_ASSERT(cache[2]==2);
    	CPPUNIT_ASSERT(cache[3]==8);
    	CPPUNIT_ASSERT(i == 1000000);
    }

    void test_initcache_3 () {
        
    	unsigned long i = 0;
	i = collatz_initcache();
    	CPPUNIT_ASSERT(i == 1000000);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_read_5);
    collatz_initcache();
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_print_4);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST(test_solve_5);
    CPPUNIT_TEST(test_initcache);
    CPPUNIT_TEST(test_initcache_2);
    CPPUNIT_TEST(test_initcache_3);
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
