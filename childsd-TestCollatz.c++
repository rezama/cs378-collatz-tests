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
            
        void test_eval_5 () {
            const int v = collatz_eval(999999, 999999);
            CPPUNIT_ASSERT(v == 259);}
            
        void test_eval_6 () {
            const int v = collatz_eval(1, 999999);
            CPPUNIT_ASSERT(v == 525);}
            
        void test_eval_7 () {
            const int v = collatz_eval(837800, 999999);
            CPPUNIT_ASSERT(v == 507);}

        // -----
        // print
        // -----

        void test_print () {
            std::ostringstream w;
            collatz_print(w, 1, 10, 20);
            CPPUNIT_ASSERT(w.str() == "1 10 20\n");}
            
        void test_print_1 () {
            std::ostringstream w;
            collatz_print(w, 0, 1, 1000000);
            CPPUNIT_ASSERT(w.str() == "0 1 1000000\n");}
            
        void test_print_2 () {
            std::ostringstream w;
            collatz_print(w, 1000002, 1000000, 1000001);
            CPPUNIT_ASSERT(w.str() == "1000002 1000000 1000001\n");}
            
        void test_print_3 () {
            std::ostringstream w;
            collatz_print(w, 0, 1, 0);
            CPPUNIT_ASSERT(w.str() == "0 1 0\n");}

        // -----
        // solve
        // -----

        void test_solve () {
            std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
            std::ostringstream w;
            collatz_solve(r, w);
            CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
            
        void test_solve_1 () {
            std::istringstream r("1 999999\n999998 999999\n999 1000\n100000 900000\n");
            std::ostringstream w;
            collatz_solve(r, w);
            CPPUNIT_ASSERT(w.str() == "1 999999 525\n999998 999999 259\n999 1000 112\n100000 900000 525\n");}
            
        void test_solve_2 () {
            std::istringstream r("1 2\n2 3\n3 4\n4 5\n");
            std::ostringstream w;
            collatz_solve(r, w);
            CPPUNIT_ASSERT(w.str() == "1 2 2\n2 3 8\n3 4 8\n4 5 6\n");}
            
        void test_solve_3 () {
            std::istringstream r("1 10\n10 100\n100 1000\n1000 10000\n");
            std::ostringstream w;
            collatz_solve(r, w);
            CPPUNIT_ASSERT(w.str() == "1 10 20\n10 100 119\n100 1000 179\n1000 10000 262\n");}

        // -----
        // suite
        // -----

        CPPUNIT_TEST_SUITE(TestCollatz);
        CPPUNIT_TEST(test_read);
        CPPUNIT_TEST(test_eval_1);
        CPPUNIT_TEST(test_eval_2);
        CPPUNIT_TEST(test_eval_3);
        CPPUNIT_TEST(test_eval_4);
        CPPUNIT_TEST(test_eval_5);
        CPPUNIT_TEST(test_eval_6);
        CPPUNIT_TEST(test_eval_7);
        CPPUNIT_TEST(test_print);
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
        ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
        cout << "TestCollatz.c++" << endl;

        CppUnit::TextTestRunner tr;
        tr.addTest(TestCollatz::suite());
        tr.run();

        cout << "Done." << endl;
        return 0;}