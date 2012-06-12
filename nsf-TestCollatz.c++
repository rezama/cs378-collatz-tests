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

	void test_read_1 () {
		std::istringstream r("\n");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == false);
	}

	void test_read_2 () {
		std::istringstream r("1 10\n");
		int i;
		int j;
		const bool b1 = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b1 == true);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(j == 10);
		const bool b2 = collatz_read(r, i ,j);
		CPPUNIT_ASSERT(b2 == false);
	}

	void test_read_3 () {
		std::istringstream r("1 10\n100 200");
		int i;
		int j;
		const bool b1 = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b1 == true);
		CPPUNIT_ASSERT(i == 1);
		CPPUNIT_ASSERT(j == 10);
		const bool b2 = collatz_read(r, i ,j);
		CPPUNIT_ASSERT(b2 == true);
		CPPUNIT_ASSERT(i == 100);
		CPPUNIT_ASSERT(j == 200);
		const bool b3 = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b3 == false);
	}

	void test_read_4 () {
		std::istringstream r("113001 113888\n");
		int i;
		int j;
		const bool b = collatz_read(r, i, j);
		CPPUNIT_ASSERT(b == true);
	}

    // ----
    // eval
    // ----

    void test_eval_1 () {
	collatz_cache();
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_2 () {
	collatz_cache();
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_3 () {
	collatz_cache();
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_4 () {
	collatz_cache();
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);}

	void test_eval_5 () {
		collatz_cache();
		const int v = collatz_eval(1, 1);
		CPPUNIT_ASSERT(v == 1);
	}

	void test_eval_6 () {
		collatz_cache();
		const int v = collatz_eval(1000000, 1000000);
		CPPUNIT_ASSERT(v == 153);
	}

	void test_eval_7 () {
		collatz_cache();
		const int v = collatz_eval(2, 5);
		CPPUNIT_ASSERT(v == 8);
	}

	void test_eval_8 () {
		collatz_cache();
		const int v = collatz_eval(113001, 113888);
		CPPUNIT_ASSERT(v == 292);
	}

	void test_eval_9 () {
		collatz_cache();
		const int v = collatz_eval(114001, 114887);
		CPPUNIT_ASSERT(v == 305);
	}

	void test_eval_10 () {
		collatz_cache();
		const int v = collatz_eval(113383, 113888);
		CPPUNIT_ASSERT(v == 292);
	}

	void test_eval_11 () {
		collatz_cache();
		const int v = collatz_eval(113383, 113384);
		CPPUNIT_ASSERT(v == 248);
	}

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}

	void test_print_1 () {
		std::ostringstream w;
		collatz_print(w, 100, 200, 125);
		CPPUNIT_ASSERT(w.str() == "100 200 125\n");
	}

	void test_print_2 () {
		std::ostringstream w;
		collatz_print(w, 201, 210, 89);
		CPPUNIT_ASSERT(w.str() == "201 210 89\n");
	}

	void test_print_3 () {
		std::ostringstream w;
		collatz_print(w, 900, 1000, 174);
		CPPUNIT_ASSERT(w.str() == "900 1000 174\n");
	}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

	void test_solve_1 () {
	        std::istringstream r("6 90\n60 620\n450 610\n20000 25000\n");
	        std::ostringstream w;
	        collatz_solve(r, w);
	        CPPUNIT_ASSERT(w.str() == "6 90 116\n60 620 144\n450 610 142\n20000 25000 282\n");}

	void test_solve_2 () {
	        std::istringstream r("1 2\n999999 1000000\n333 555\n6000 9870\n");
	        std::ostringstream w;
	        collatz_solve(r, w);
	        CPPUNIT_ASSERT(w.str() == "1 2 2\n999999 1000000 259\n333 555 142\n6000 9870 262\n");}

	void test_solve_3 () {
	        std::istringstream r("");
	        std::ostringstream w;
	        collatz_solve(r, w);
	        CPPUNIT_ASSERT(w.str() == "");}


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_eval_7);
    CPPUNIT_TEST(test_eval_8);
    CPPUNIT_TEST(test_eval_9);
    CPPUNIT_TEST(test_eval_10);
    CPPUNIT_TEST(test_eval_11);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
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
