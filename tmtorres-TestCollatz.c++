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

using namespace std;

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit :: TestFixture {
    // ----
    // read
    // ----

    void test_read () 
	{
		int i;
        int j;
        istringstream r("21 6\n");
		istringstream s("10 1\n");

        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    21);
        CPPUNIT_ASSERT(j ==   6);

	}

    void test_read2 () 
	{
        std::istringstream r("239 1298\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    239);
        CPPUNIT_ASSERT(j ==   1298);
	}


    void test_read3 () 
	{
        std::istringstream r("4590 4590\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    4590);
        CPPUNIT_ASSERT(j ==   4590);
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

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        collatz_print(w, 56, 79, 34);
        CPPUNIT_ASSERT(w.str() == "56 79 34\n");}

    void test_print2 () {
        std::ostringstream w;
        collatz_print(w, 843, 231, 139);
        CPPUNIT_ASSERT(w.str() == "843 231 139\n");}

    void test_print3 () {
        std::ostringstream w;
        collatz_print(w, 467, 35, 21);
        CPPUNIT_ASSERT(w.str() == "467 35 21\n");}

    // -----
    // solve
    // -----

    void test_solve () 
	{
        istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
	}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
	CPPUNIT_TEST(test_read2);
	CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
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