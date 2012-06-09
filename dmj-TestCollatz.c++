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

    void test_read_1() {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);
	}

	void test_read_2() {
		std::istringstream r("40 30");
		int i, j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 40);
		CPPUNIT_ASSERT(j == 30);
	}

	void test_read_3() {
		std::istringstream r("  5000     5000");
		int i, j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i == 5000);
		CPPUNIT_ASSERT(j == 5000);
	}

	void test_read_4() {
		std::istringstream r("");
		int i, j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == false);
	}

	void test_read_5() {
		std::istringstream r("	  ");
		int i, j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == false);
	}

	void test_read_6() {
		std::istringstream r("hello world");
		int i, j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == false);
	}

	// -----------------
	// find_cycle_length
	// -----------------
	
	void test_find_cycle_length_1() {
		int n = 1;
		int c = find_cycle_length(n);
		CPPUNIT_ASSERT(c == 1);
	}

	void test_find_cycle_length_2() {
		int n = 999999;
		int c = find_cycle_length(n);
		CPPUNIT_ASSERT(c == 259);
	}

	void test_find_cycle_length_3() {
		int n = 5001;
		int c = find_cycle_length(n);
		CPPUNIT_ASSERT(c == 65);
	}

	// ----
	// swap
	// ----
	
	void test_swap_1() {
		int i = 5;
		int j = 5;
		swap(i, j);
		CPPUNIT_ASSERT(i == 5);
		CPPUNIT_ASSERT(j == 5);
	}

	void test_swap_2() {
		int i = 1000000;
		int j = 5000000;
		swap(i, j);
		CPPUNIT_ASSERT(i == 5000000);
		CPPUNIT_ASSERT(j == 1000000);
	}

	void test_swap_3() {
		int i = 800000;
		int j = 3;
		swap(i, j);
		CPPUNIT_ASSERT(i == 3);
		CPPUNIT_ASSERT(j == 800000);
	}

    // ----
    // eval
    // ----

    void test_eval_1() {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);
	}

    void test_eval_2() {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);
	}

    void test_eval_3() {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);
	}

    void test_eval_4() {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);
	}

	void test_eval_5() {
		const int v = collatz_eval(5100, 5000);
		CPPUNIT_ASSERT(v == 179);
	}

	void test_eval_6() {
		const int v = collatz_eval(700000, 900000);
		CPPUNIT_ASSERT(v == 525);
	}

    // -----
    // print
    // -----

    void test_print_1() {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");
	}

    void test_print_2() {
        std::ostringstream w;
        collatz_print(w, 999999, 1, 476);
        CPPUNIT_ASSERT(w.str() == "999999 1 476\n");
	}

    void test_print_3() {
        std::ostringstream w;
        collatz_print(w, 100, 100, 26);
        CPPUNIT_ASSERT(w.str() == "100 100 26\n");
	}

    // -----
    // solve
    // -----

    void test_solve_1() {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
	}

    void test_solve_2() {
        std::istringstream r("600000 900000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "600000 900000 525\n");
	}

    void test_solve_3() {
        std::istringstream r("\n\n\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");
	}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_read_5);
    CPPUNIT_TEST(test_read_6);
	CPPUNIT_TEST(test_find_cycle_length_1);
	CPPUNIT_TEST(test_find_cycle_length_2);
	CPPUNIT_TEST(test_find_cycle_length_3);
	CPPUNIT_TEST(test_swap_1);
	CPPUNIT_TEST(test_swap_2);
	CPPUNIT_TEST(test_swap_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
	CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();
};

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
    return 0;
}
