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
		
	void test_eval_56440_56487 () {
        const int v = collatz_eval(56440, 56487);
        CPPUNIT_ASSERT(v == 291);}
		
	void test_eval_56487_56487 () {
        const int v = collatz_eval(56487, 56487);
        CPPUNIT_ASSERT(v == 291);}

	void test_eval_514373_514671 () {
        const int v = collatz_eval(514373, 514671);
        CPPUNIT_ASSERT(v == 364);}
		
	void test_eval_171_230 () {
        const int v = collatz_eval(171, 230);
        CPPUNIT_ASSERT(v == 125);}
		
	void test_ccache_0 () {
		const int v = collatz_ccache(0);
		CPPUNIT_ASSERT(v == 0);}
		
	void test_ccache_1 () {
		const int v = collatz_ccache(1);
		CPPUNIT_ASSERT(v == 1);}
		
	void test_ccache_276735 () {
		const int v = collatz_ccache(276735);
		CPPUNIT_ASSERT(v == 164);}
		
	void test_ccache_1000001 () {
		const int v = collatz_ccache(1000001);
		CPPUNIT_ASSERT(v == 0);}
		
	void test_lcache_17 () {
		collatz_lcache(7);
		const int v = collatz_ccache(7);
		CPPUNIT_ASSERT(v == 17);}
		
	void test_lcache_53 () {
		collatz_lcache(53);
		const int v = collatz_ccache(53);
		CPPUNIT_ASSERT(v == 12);}
		
	void test_lcache_333333 () {
		collatz_lcache(333333);
		const int v = collatz_ccache(333333);
		CPPUNIT_ASSERT(v == 154);}
		

    // -----
    // print
    // -----
/*
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
*/
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
/*    
	CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_solve);
*/
	CPPUNIT_TEST(test_eval_56440_56487);
	CPPUNIT_TEST(test_eval_56487_56487);
	CPPUNIT_TEST(test_eval_171_230);
	CPPUNIT_TEST(test_eval_514373_514671);
	CPPUNIT_TEST(test_eval_56440_56487);
	CPPUNIT_TEST(test_ccache_0);
	CPPUNIT_TEST(test_ccache_1);
	CPPUNIT_TEST(test_ccache_276735);
	CPPUNIT_TEST(test_ccache_1000001);
	CPPUNIT_TEST(test_lcache_17);
	CPPUNIT_TEST(test_lcache_53);
	CPPUNIT_TEST(test_lcache_333333);
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
