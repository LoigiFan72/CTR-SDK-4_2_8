/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     test_Test.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 47284 $
 *---------------------------------------------------------------------------*/

#include <nn.h>
//#include <nn/Result.h>
//#include <nn/os.h>
//#include <nn/Handle.h>
//#include <nn/os/os_Thread.h>
#include <nn/os/os_Initialize.h>
#include <nn/test/test_Test.h>
using namespace nn::dbg;
using namespace nn::os;

using nn::Handle;
using nn::test::String;
using nn::test::TextOutput;
using nn::test::XmlOutput;
using nn::test::AssertInfo;


// Test suite definitions
//
// Class that inherits Suite is the test suite
// Create test method in this class and register it in the constructor
class Test : public nn::test::Suite
{
public:
    Test()
    {
        // Test suite name
        SUITE_NAME("Test");

        // Test case registration
        TEST_ADD(Test::Test1)
        TEST_ADD(Test::Test2)
        TEST_ADD(Test::Test3)
        TEST_ADD(Test::Test4)
    }
    virtual ~Test() {}

private:
    // The following is the test method
    void	Test1()
    {
    }
    void	Test2()
    {
        NN_TEST_ASSERT(1 == 0);
        NN_TEST_ASSERT(2 & 0);
    }
    void    Test3()
    {
        NN_TEST_ASSERT(1 > 2);
    }

    void    Test4()
    {
        NN_TEST_ASSERT_EQUAL(1, 2);
    }
};


class SuccessTest : public nn::test::Suite
{
public:
    SuccessTest()
    {
        // Test suite name
        SUITE_NAME("SuccessTest");

        // Test case registration
        TEST_ADD(SuccessTest::Test1)
        TEST_ADD(SuccessTest::Test2)
        TEST_ADD(SuccessTest::Test3)
        TEST_ADD(SuccessTest::Test4)
    }
    virtual ~SuccessTest() {}

private:
    // The following is the test method
    void    Test1()
    {
    }
    void    Test2()
    {
        NN_TEST_ASSERT(1 == 1);
        NN_TEST_ASSERT(2 & 2);
    }
    void    Test3()
    {
        NN_TEST_ASSERT(1 > 0);
    }

    void    Test4()
    {
        NN_TEST_ASSERT_EQUAL(1, 1);
    }
};



class SubTest1 : public nn::test::Suite
{
public:
    SubTest1()
    {
        SUITE_NAME("SubTest1");
        TEST_ADD(SubTest1::Test1)
        TEST_ADD(SubTest1::Test2)
        TEST_ADD(SubTest1::Test3)
    }
private:
    void Test1()
    {
        NN_TLOG_("SubTest1::Test1 in");
        NN_TEST_BEGIN_EXPECT_FAILURE_ANY
        {
            NN_TASSERT_(0);
        }
        NN_TEST_END_EXPECT_FAILURE

        NN_TLOG_("SubTest1::Test1 out");

    }
    void Test2()
    {
        NN_TLOG_("SubTest1::Test2 in");
        NN_TEST_ASSERTMSG(10 == 9, "Assert!, %d\n", 1 + 2);
        NN_TEST_ASSERT(1 == 2);
        NN_TLOG_("SubTest1::Test2 out");
    }
    void Test3()
    {
        NN_TLOG_("SubTest1::Test3 in");
        NN_TEST_ASSERT(10 == 9);
        NN_TLOG_("SubTest1::Test3 out");
    }
};



class SubTest2 : public nn::test::Suite
{
public:
    SubTest2()
    {
        SUITE_NAME("SubTest2");
        TEST_ADD_WITH_INFO(SubTest2::Test1, "SubTest2::Test1", "2_1 info")
        TEST_ADD_WITH_INFO(SubTest2::Test2, "SubTest2::Test2", "2_2 info")
    }
private:
    void Test1()
    {
        NN_TLOG_("Do SubTest2::Test1.Success");
    }
    void Test2()
    {
        NN_TLOG_("Do SubTest2::Test2.Failure");
        NN_TEST_ASSERT(1 == 2);
    }
};



class SubTest3 : public nn::test::Suite
{
public:
    SubTest3()
    {
        SUITE_NAME("SubTest3");
        TEST_ADD_WITH_NAME(SubTest3::Test1, "Test3_1GO")
    }
private:
    void Test1()
    {
        NN_TLOG_("Do SubTest3::Test1.Failure");
        NN_TEST_ASSERT(1 == 2);
    }
};



class InitializeFinalizeSuiteTest : public nn::test::Suite
{
public:
    InitializeFinalizeSuiteTest()
    {
        SUITE_NAME("InitializeFinalizeSuiteTest");
        TEST_ADD(InitializeFinalizeSuiteTest::Test)

        isInitialized = false;
        isFinalized = false;
        isTested = false;
    }

    bool isInitialized;
    bool isFinalized;
    bool isTested;

protected:
    virtual bool InitializeSuite() { isInitialized = true; } // Called once before starting the test belonging to the suite
    virtual void FinalizeSuite() {isFinalized = true;}                 // Called when ending the test belonging to the suite


private:
    void Test()
    {
        NN_TLOG_("Do InitializeFinalizeSuiteTest::Test");
        isTested = true;
    }
};

#define TOTAL_TEST_NUM 11


/* Please see man pages for details 
 
 */
void testRun(nn::test::Output& out)
{
    // Execute Run. All tests succeed in this case.
    {
        SuccessTest test;
        NN_TASSERT_(true == test.Run(out, false));
    }

    // Execute Run. A failure occurs. If the second argument is true, do not exit test case even if caught by an assert
    {
        Test test;              // Create test suite

        // If there is a test suite to execute as a child of a test case
        // Child can be registered with the AddSubSuite method
        SubTest1 subTest1;
        test.AddSubSuite(&subTest1);

        // Execute test
        NN_TASSERT_(false == test.Run(out, true));
    }

    // Execute Run. A failure occurs. If the second argument is false, exit test case when caught by an assert
    {
        Test test;              // Create test suite

        // If there is a test suite to execute as a child of a test case
        // Child can be registered with the AddSubSuite method
        SubTest1 subTest1;
        test.AddSubSuite(&subTest1);

        // Execute test
        NN_TASSERT_(false == test.Run(out, false));
    }

    // Execute Run. Test to confirm that Initialize() and FinalizeSuite() of the sub Suite execute
    {
        SuccessTest test;              // Create test suite
        InitializeFinalizeSuiteTest initializeFinalizeSuiteTest;
        test.AddSubSuite(&initializeFinalizeSuiteTest);

        NN_TASSERT_(initializeFinalizeSuiteTest.isInitialized == false);
        NN_TASSERT_(initializeFinalizeSuiteTest.isFinalized == false);
        NN_TASSERT_(initializeFinalizeSuiteTest.isTested == false);
        NN_TASSERT_(true == test.Run(out, true));
        NN_TASSERT_(initializeFinalizeSuiteTest.isInitialized == true);
        NN_TASSERT_(initializeFinalizeSuiteTest.isFinalized == true);
        NN_TASSERT_(initializeFinalizeSuiteTest.isTested == true);
    }
}


/* Please see man pages for details 
 
 */
void testGetFunc()
{
    Test test;
    SubTest1 subTest1;
    test.AddSubSuite(&subTest1);
    SubTest2 subTest2;
    test.AddSubSuite(&subTest2);
    SubTest3 subTest3;
    test.AddSubSuite(&subTest3);

    /*---------------------------------------------------------------------------*
        GetTestName()
     *---------------------------------------------------------------------------*/
    NN_TASSERT_(test.GetTestName() == "Test");
    NN_TASSERT_(subTest1.GetTestName() == "SubTest1");
    NN_TASSERT_(subTest2.GetTestName() == "SubTest2");
    NN_TASSERT_(subTest3.GetTestName() == "SubTest3");
    
    /*---------------------------------------------------------------------------*
        GetTestNum()
     *---------------------------------------------------------------------------*/
    NN_TASSERT_(test.GetTestNum() == 4);
    NN_TASSERT_(subTest1.GetTestNum() == 3);
    NN_TASSERT_(subTest2.GetTestNum() == 2);
    NN_TASSERT_(subTest3.GetTestNum() == 1);
    
    /*---------------------------------------------------------------------------*
        GetTotalTestNum()
     *---------------------------------------------------------------------------*/
    NN_TASSERT_(test.GetTotalTestNum() == 10);
    NN_TASSERT_(subTest1.GetTotalTestNum() == 3);
    NN_TASSERT_(subTest2.GetTotalTestNum() == 2);
    NN_TASSERT_(subTest3.GetTotalTestNum() == 1);
    
    /*---------------------------------------------------------------------------*
        GetTestFuncInfos()
     *---------------------------------------------------------------------------*/
    String suiteName;
    String funcName;
    
    NN_TASSERT_(false == test.GetTestFuncInfos(0, suiteName, funcName));
    
    NN_TASSERT_(true == test.GetTestFuncInfos(1, suiteName, funcName));
    NN_TASSERT_(suiteName == "Test");
    NN_TASSERT_(funcName == "Test::Test1");
    
    NN_TASSERT_(true == test.GetTestFuncInfos(4, suiteName, funcName));
    NN_TASSERT_(suiteName == "Test");
    NN_TASSERT_(funcName == "Test::Test4");

    NN_TASSERT_(true == test.GetTestFuncInfos(5, suiteName, funcName));
    NN_TASSERT_(suiteName == "SubTest1");
    NN_TASSERT_(funcName == "SubTest1::Test1");
    
    NN_TASSERT_(true == test.GetTestFuncInfos(7, suiteName, funcName));
    NN_TASSERT_(suiteName == "SubTest1");
    NN_TASSERT_(funcName == "SubTest1::Test3");
    
    NN_TASSERT_(true == test.GetTestFuncInfos(8, suiteName, funcName));
    NN_TASSERT_(suiteName == "SubTest2");
    NN_TASSERT_(funcName == "SubTest2::Test1");
    
    NN_TASSERT_(true == test.GetTestFuncInfos(9, suiteName, funcName));
    NN_TASSERT_(suiteName == "SubTest2");
    NN_TASSERT_(funcName == "SubTest2::Test2");

    NN_TASSERT_(true == test.GetTestFuncInfos(10, suiteName, funcName));
    NN_TASSERT_(suiteName == "SubTest3");
    NN_TASSERT_(funcName == "Test3_1GO");
    
    NN_TASSERT_(false == test.GetTestFuncInfos(11, suiteName, funcName));

    //Confirms that test extra information can be obtained
    String funcInfo;
    NN_TASSERT_(true == test.GetTestFuncInfos(7, suiteName, funcName, funcInfo));
    NN_TASSERT_(funcInfo == "");

    
    NN_TASSERT_(true == test.GetTestFuncInfos(8, suiteName, funcName, funcInfo));
    NN_TASSERT_(funcInfo == "2_1 info");

    NN_TASSERT_(true == test.GetTestFuncInfos(9, suiteName, funcName, funcInfo));
    NN_TASSERT_(funcInfo == "2_2 info");

}


/* Please see man pages for details 
 
 */
void testRunSpecificTestFunc(nn::test::Output& output)
{
    Test test;
    SubTest1 subTest1;
    test.AddSubSuite(&subTest1);
    SubTest2 subTest2;
    test.AddSubSuite(&subTest2);
    SubTest3 subTest3;
    test.AddSubSuite(&subTest3);
    InitializeFinalizeSuiteTest initializeFinalizeSuiteTest;
    test.AddSubSuite(&initializeFinalizeSuiteTest);

    test.Initialize();
    /*Test "specifying test name and executing"*/
    NN_TASSERT_(true == test.RunSpecificTestFunc("Test::Test1", output));
    NN_TASSERT_(false == test.RunSpecificTestFunc("Test::Test2", output));
    NN_TASSERT_(false == test.RunSpecificTestFunc("Test::Test3", output));
    NN_TASSERT_(false == test.RunSpecificTestFunc("Test::Test4", output));
    //// When executing by specifying test name, the sub Suite test cannot be executed //
    NN_TASSERT_(false == test.RunSpecificTestFunc("SubTest1::Test1", output));
    NN_TASSERT_(test.GetTotalTestNum() == TOTAL_TEST_NUM);
    
    /*Test "specifying test ID and executing"*/
    NN_TASSERT_(true == test.RunSpecificTestFunc(1, output));
    NN_TASSERT_(false == test.RunSpecificTestFunc(2, output));
    NN_TASSERT_(false == test.RunSpecificTestFunc(3, output));
    NN_TASSERT_(false == test.RunSpecificTestFunc(4, output));
    //// When "executing by specifying test ID," the sub Suite test can also be executed //
    NN_TASSERT_(true == test.RunSpecificTestFunc(5, output));
    NN_TASSERT_(test.GetTotalTestNum() == TOTAL_TEST_NUM);
    
    /*Test "specifying test Suite and test name and executing"*/
    NN_TASSERT_(true == test.RunSpecificTestFunc("SubTest1", "SubTest1::Test1", output));
    NN_TASSERT_(false == test.RunSpecificTestFunc("SubTest1", "SubTest1::Test2", output));
    NN_TASSERT_(false == test.RunSpecificTestFunc("SubTest1", "SubTest1::Test3", output));
    NN_TASSERT_(true == test.RunSpecificTestFunc("SubTest2", "SubTest2::Test1", output));
    NN_TASSERT_(true == test.RunSpecificTestFunc(8, output));
    NN_TASSERT_(false == test.RunSpecificTestFunc("SubTest2", "SubTest2::Test2", output));

    NN_TASSERT_(false == test.RunSpecificTestFunc("SubTest3", "SubTest3::Test1", output));
    NN_TASSERT_(false == test.RunSpecificTestFunc("SubTest3", "Test3_1GO", output));
    NN_TASSERT_(test.GetTotalTestNum() == TOTAL_TEST_NUM);

    //// With "specifying test Suite and test name and executing," execution fails if the Suite and test name do not match //
    NN_TASSERT_(false == test.RunSpecificTestFunc("SubTest3", "SubTest1::Test1", output));
    NN_TASSERT_(false == test.RunSpecificTestFunc("SubTest3", "SubTest2::Test1", output));
    NN_TASSERT_(test.GetTotalTestNum() == TOTAL_TEST_NUM);


    /*Test when the contAfterFail argument of RunSpecificTestFunc() is set to false*/
    NN_TASSERT_(true == test.RunSpecificTestFunc(1, output, false));
    NN_TASSERT_(false == test.RunSpecificTestFunc(2, output, false));
    NN_TASSERT_(false == test.RunSpecificTestFunc(3, output, false));
    NN_TASSERT_(false == test.RunSpecificTestFunc(4, output, false));
    NN_TASSERT_(true == test.RunSpecificTestFunc(5, output, false));
    NN_TASSERT_(true == test.RunSpecificTestFunc("SubTest1", "SubTest1::Test1", output, false));
    NN_TASSERT_(false == test.RunSpecificTestFunc("SubTest1", "SubTest1::Test2", output, false));
    NN_TASSERT_(false == test.RunSpecificTestFunc("SubTest1", "SubTest1::Test3", output, false));
    NN_TASSERT_(true == test.RunSpecificTestFunc("SubTest2", "SubTest2::Test1", output, false));
    NN_TASSERT_(true == test.RunSpecificTestFunc(8, output));
    NN_TASSERT_(false == test.RunSpecificTestFunc("SubTest2", "SubTest2::Test2", output, false));
    NN_TASSERT_(test.GetTotalTestNum() == TOTAL_TEST_NUM);

    /*Test to confirm that Initialize() and FinalizeSuite() of the sub Suite execute for RunSpecificTestFunc()*/
    NN_TASSERT_(initializeFinalizeSuiteTest.isInitialized == false);
    NN_TASSERT_(initializeFinalizeSuiteTest.isFinalized == false);
    NN_TASSERT_(initializeFinalizeSuiteTest.isTested == false);
    NN_TASSERT_(true == test.RunSpecificTestFunc("InitializeFinalizeSuiteTest", "InitializeFinalizeSuiteTest::Test", output));
    NN_TASSERT_(initializeFinalizeSuiteTest.isInitialized == true);
    NN_TASSERT_(initializeFinalizeSuiteTest.isFinalized == true);
    NN_TASSERT_(initializeFinalizeSuiteTest.isTested == true);

    test.Finalize();
}


// For nninitStartup  and nnMain:
// Include in the test library when all test code is replaced
// Plan to switch so that CUnit is not used with the build system
//
// When replacing, define them for each test process.

// test::Startup must be called at startup
void    nninitStartUp()
{
    nn::test::InitializeAllocator();
}

void nnMain( void )
{
    //__breakpoint(0);
    // Output settings
#ifdef NN_TEST_DEBUG
    TextOutput out;          // Text output during debugging
#else
    XmlOutput out;           // XML output when not debugging (when automatic testing)
#endif
    /* Please see man pages for details 
     
     */
    testRun(out);


    /* Please see man pages for details 
     
     */
    testGetFunc();
     
     /* Please see man pages for details 
     
     */
     testRunSpecificTestFunc(out);

    NN_TLOG_("---test_Test.cpp nnMain() finished.(into infinite loop)");
    while(1)
    {
        // Continue Sleep.
        nn::os::Thread::Sleep(nn::fnd::TimeSpan::FromSeconds(1));
    }
}
