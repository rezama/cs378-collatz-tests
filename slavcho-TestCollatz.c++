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
		
	void test_read_2 () {                       // empty
        std::istringstream r("");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == false);
	}

    void test_read_3 () {
        std::istringstream r("113382 \t 1 \n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b ==  true);
        CPPUNIT_ASSERT(i == 113382);
        CPPUNIT_ASSERT(j ==      1);
	}	
	
	// ---------
	// cycle_len
	// ---------
	
	void cycle_len_1 () {
	    const int v = cycle_len(1);
		CPPUNIT_ASSERT(v == 1);
	}
	
	void cycle_len_2 () {
	    const int v = cycle_len(113382);
		CPPUNIT_ASSERT(v == 67);
	}
	
	void cycle_len_3 () {
	    const int v = cycle_len(1000000);
		CPPUNIT_ASSERT(v == 153);
	}
	
	void cycle_len_4 () {                         // overflow
	    const int v = cycle_len(113383);
		CPPUNIT_ASSERT(v == 248);
	}
	
	void cycle_len_5 () {                         // max
	    const int v = cycle_len(837799);
		CPPUNIT_ASSERT(v == 525);
	}
	
	// ----------
    // itt_blocks
    // ----------
	
	void test_itt_blocks_1 () {             // i and j in same block (no empty block)
	    const int v = itt_blocks(24, 56);
		CPPUNIT_ASSERT(v == 0);
	}
	
	void test_itt_blocks_2 () {            // i and j differ by 1 block (no empty block)
	    const int v = itt_blocks(56, 124);
		CPPUNIT_ASSERT(v == 0);
	}
	
	void test_itt_blocks_3 () {           // on boundries
	    const int v = itt_blocks(100, 201);
		CPPUNIT_ASSERT(v == 125);
	}
	
	void test_itt_blocks_4 () {           // on boundries
	    const int v = itt_blocks(1, 100);
		CPPUNIT_ASSERT(v == 0);
	}
	
	void test_itt_blocks_5 () {
	    const int v = itt_blocks(223, 7982);
		CPPUNIT_ASSERT(v == 262);
	}

    // ----
    // eval
    // ----

    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
        std::cout << v;
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
      const int v = collatz_eval(1, 1);         // identity for 1
        CPPUNIT_ASSERT(v == 1);}
    
    void test_eval_6 () {
      const int v = collatz_eval(7, 7);         // identity for != 1
        CPPUNIT_ASSERT(v == 17);}

    void test_eval_7 () {
      const int v = collatz_eval(3, 4);          // max is first el
        CPPUNIT_ASSERT(v == 8);}

    void test_eval_8 () {
      const int v = collatz_eval(1, 2);          // max is last el
        CPPUNIT_ASSERT(v == 2);}
 
    void test_eval_9 () {
      const int v = collatz_eval(1, 1024);          // max not on boundry
        CPPUNIT_ASSERT(v == 179);}

    void test_eval_10 () {
      const int v = collatz_eval(1, 113382);          // no overflow
        CPPUNIT_ASSERT(v == 354);}
    
	void test_eval_11 () {
      const int v = collatz_eval(113382, 1);          // reverse
        CPPUNIT_ASSERT(v == 354);}
		
	void test_eval_12 () {
      const int v = collatz_eval(1, 1000000);          // time
        CPPUNIT_ASSERT(v == 525);}	

    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
    
	void test_print_2 () {
        std::ostringstream w;
        collatz_print(w, 1, 113382, 354);
        CPPUNIT_ASSERT(w.str() == "1 113382 354\n");}
		
	void test_print_3 () {                             // reverse
        std::ostringstream w;
        collatz_print(w, 113382, 1, 354);
        CPPUNIT_ASSERT(w.str() == "113382 1 354\n");}	

    // -----
    // solve
    // -----

    void test_solve_1 () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
		
	void test_solve_2 () {                    // empty
        std::istringstream r("");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");}

    void test_solve_3 () {
        std::istringstream r("113382 1\n1 1\n 23 88\n600000 900000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "113382 1 354\n1 1 1\n23 88 116\n600000 900000 525\n");}		

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_read_3);
	CPPUNIT_TEST(cycle_len_1);
	CPPUNIT_TEST(cycle_len_2);
	CPPUNIT_TEST(cycle_len_3);
	CPPUNIT_TEST(cycle_len_4);
	CPPUNIT_TEST(cycle_len_5);
	CPPUNIT_TEST(test_itt_blocks_1);
	CPPUNIT_TEST(test_itt_blocks_2);
	CPPUNIT_TEST(test_itt_blocks_3);
	CPPUNIT_TEST(test_itt_blocks_4);
	CPPUNIT_TEST(test_itt_blocks_5);
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
    CPPUNIT_TEST(test_eval_12);
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
    gen_cyclen_array();  // initialize cache

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
