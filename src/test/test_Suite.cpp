/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     test_Suite.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/test/test_Suite.h>
#include <nn/test/test_Output.h>
#include <nn/test/test_Time.h>
#include <nn/test/test_Api.h>

#if !defined(NN_HARDWARE_CTR_CTTS) && defined(NN_PLATFORM_HAS_MMU) && defined(TEST_WITH_GUI) && !defined(NN_PROCESSOR_ARM946ES)
#include <nn/test/gui/test_Gui.h>
#endif

#include <nn/dbg/dbg_PrintResult.h>

namespace nn{ namespace test{

    namespace {
        Suite* s_CurrentSuite = 0;

#ifdef NN_PROCESSOR_ARM946ES
        const int NUM_RESULTHOLDER = 32;
        const bit32 INVALID_THREADID = 0xffffffff;

        struct ThreadLocalStrageArm9 {
            bit32 threadId;
            uptr  value;
        } s_ResultHolderArm9[NUM_RESULTHOLDER];
#endif
    }

    Suite::Suite() : 
        m_pOutput(NULL), m_TotalTestsNum(0), m_pExitTestJumpBuffer(NULL),
            m_IsSuccess(false), m_Continue(false), m_IsInitialized(false), m_MainThreadId(nn::os::Thread::GetCurrentId())
    {
#ifdef NN_PROCESSOR_ARM946ES
        for ( int i = 0; i < NUM_RESULTHOLDER; i++ ) 
        {
            s_ResultHolderArm9[i].threadId = INVALID_THREADID;
            s_ResultHolderArm9[i].value = 0;
        }
#endif
    }

    Suite::~Suite()
    {
    }

    bool Suite::IsOnMainThread() const
    {
        return m_MainThreadId == nn::os::Thread::GetCurrentId();
    }
    
    void Suite::AddSubSuite(Suite* pSuite)
    {
        m_SubSuites.PushBack(pSuite);
        m_TotalTestsNum += pSuite->m_TotalTestsNum;
    }
    
    bool Suite::Run(Output& output, bool isContinue)
    {
        int total = TotalTests();               // Number of tests including sub-suites
        int subSuiteNum = m_SubSuites.GetNum(); 

        // Initialization before starting test
        m_Continue = isContinue;
        output.OnInitialize(total, (subSuiteNum+1));
        Initialize();

        Time    time;
        time.Start();
        DoRun(&output, isContinue);
        time.End();
        output.OnFinished(total, time);
        Finalize();
        return m_IsSuccess;
    }
    
    void Suite::DoRun(Output* pOutput, bool isContinue)
    {
        m_IsSuccess = true;
        int testsNum = m_Tests.GetNum();        // Number of tests not including sub-suites
        m_pOutput = pOutput;

        // Executing test maintained by this suite
        pOutput->OnSuiteStart(testsNum, m_TestName);
        Time timeSuite;
        timeSuite.Start();
        while(!m_Tests.IsEmpty())
        {
            TestInfo info = m_Tests.PopFront();
            bool testResult = DoRunSpecificTest(info, pOutput);
            m_IsSuccess &= testResult;
        }
        timeSuite.End();
        pOutput->OnSuiteEnd(testsNum, m_TestName, timeSuite);

        // Execute child suite
        while(!m_SubSuites.IsEmpty())
        {
            Suite* pSuite = m_SubSuites.PopFront();
            pSuite->Initialize();
            pSuite->DoRun(pOutput, isContinue);
            pSuite->Finalize();
            m_IsSuccess &= pSuite->m_IsSuccess;
        }
    }
    
    void Suite::AddAssertInfo(AssertInfo info)
    {
        m_pOutput->OnAssert(info);
        // Test fails if caught by an assert even once.
        m_IsTestSuccess = false;
    }

    void Suite::RegisterTest(TestFunc func, const String& name)
    {
        m_Tests.PushBack(TestInfo(func, name));
        m_TotalTestsNum++;
    }

    void Suite::UnregisterTest(TestFunc func)
    {
        NN_TASSERT_(m_TotalTestsNum == m_Tests.GetNum());
        for (int i = 0; i < m_TotalTestsNum; i++)
        {
            if (m_Tests.GetElement(i).testFunc == func)
            {
                m_Tests.DeleteElement(i);
                i--;
                m_TotalTestsNum--;
            }
        }
    }

    void Suite::RegisterTestWithInfo(TestFunc func, const String& name, const String& info)
    {
        m_Tests.PushBack(TestInfo(func, name, info));
        m_TotalTestsNum++;
    }

    void Suite::ExitCurrentTest()
    {
        if (!IsOnMainThread())
        {
            // Force thread to terminate if it is not the main thread
            nn::svc::ExitThread();
            NN_TASSERT_(0);
        }
        if(m_pExitTestJumpBuffer)
        {
            ::std::longjmp(*m_pExitTestJumpBuffer, 1);
        }
        else
        {
            NN_TPANIC_("Failed long jump, Suite::ExitCurrentTest()");
        }
    }

    void Suite::OnPanic(const char* pFilename, int lineNo, const char* pMessage)
    {
        AddAssertInfo(AssertInfo(pFilename, lineNo, pMessage));
        ExitCurrentTest();
    }

    nn::os::ThreadLocalStorage Suite::ResultHolder::tls_pExpectedResult;

    inline Suite::ResultHolder* Suite::ResultHolder::GetCurrent()
    {
#ifndef NN_PROCESSOR_ARM946ES
        return reinterpret_cast<Suite::ResultHolder*>(tls_pExpectedResult.GetValue());
#else
        bit32 threadId = nn::os::Thread::GetCurrentId();
        for ( int i = 0; i < NUM_RESULTHOLDER; i++ ) 
        {
            if ( threadId == s_ResultHolderArm9[i].threadId )
            {
                return reinterpret_cast<Suite::ResultHolder*>(s_ResultHolderArm9[i].value);
            }
        }
        return 0;
#endif
    }

    inline void Suite::ResultHolder::SetCurrent(Suite::ResultHolder* result)
    {
#ifndef NN_PROCESSOR_ARM946ES
        tls_pExpectedResult.SetValue(reinterpret_cast<uptr>(result));
#else
        bit32 threadId = nn::os::Thread::GetCurrentId();
        int lastBlank = -1;
        for ( int i = 0; i < NUM_RESULTHOLDER; i++ ) 
        {
            if ( threadId == s_ResultHolderArm9[i].threadId )
            {
                s_ResultHolderArm9[i].value = reinterpret_cast<uptr>(result);
                return;
            }
            if ( s_ResultHolderArm9[i].threadId == INVALID_THREADID )
            {
                lastBlank = i;
            }
        }
        if ( lastBlank != -1 )
        {
            s_ResultHolderArm9[lastBlank].threadId = threadId;
            s_ResultHolderArm9[lastBlank].value = reinterpret_cast<uptr>(result);
            return;
        }
        NN_TPANIC_("Is not empty ThreadLocalStorage for Arm9");
#endif
    }

    Result Suite::ResultHolder::GetCurrentResult()
    {
        return GetCurrent()->m_Result;
    }

    Suite::ResultHolder::ResultHolder()
    {
        NN_TASSERT_(!GetCurrent());
        SetCurrent(this);
    }

    Suite::ResultHolder::~ResultHolder()
    {
        NN_TASSERT_(GetCurrent());
#ifndef NN_PROCESSOR_ARM946ES
        SetCurrent(0);
#else
        bit32 threadId = nn::os::Thread::GetCurrentId();
        bool foundStorage = false;
        for ( int i = 0; i < NUM_RESULTHOLDER; i++ ) 
        {
            if ( threadId == s_ResultHolderArm9[i].threadId )
            {
                s_ResultHolderArm9[i].threadId = INVALID_THREADID;
                s_ResultHolderArm9[i].value = 0;
                foundStorage = true;
            }
        }
        if ( !foundStorage )
        {
            NN_TPANIC_("Not found ThreadLocalStorage for Arm9");
        }
#endif
    }

    ::std::jmp_buf* Suite::ResultHolder::GetJmpbuf()
    {
        return &m_Jmpbuf;
    }

    void Suite::ResultHolder::ResultFailureHandler(Result result, const char* filename, int lineno, const char* fmt, ::std::va_list vlist)
    {
        if (GetCurrent())
        {
            GetCurrent()->m_Result = result;
            longjmp(GetCurrent()->m_Jmpbuf, 1);
            NN_TPANIC_("longjmp failed.");
        }
        else
        {
            char buf[256];
            ::std::vsnprintf(buf, sizeof(buf), fmt, vlist);
            NN_TLOG_("Result Failure\n");
            NN_DBG_TPRINT_RESULT_(result);

            NN_TASSERT_(s_CurrentSuite);
            s_CurrentSuite->OnPanic(filename, lineno, buf);
            // Should not return
            NN_TPANIC_("Failed OnPanic\n");
        }
    }

    void Suite::ResultHolder::ResultPanicHandler(Result result, const char* filename, int lineno, const char* fmt, ::std::va_list vlist)
    {
        if (GetCurrent())
        {
            GetCurrent()->m_Result = result;
            longjmp(GetCurrent()->m_Jmpbuf, 1);
            NN_TPANIC_("longjmp failed.");
        }
        else
        {
            NN_TASSERT_(s_CurrentSuite);
            char buf[256];
            ::std::vsnprintf(buf, sizeof(buf), fmt, vlist);
            NN_TLOG_("Panic Result\n");
            NN_DBG_TPRINT_RESULT_(result);
            s_CurrentSuite->OnPanic(filename, lineno, buf);
            // Should not return
            NN_TPANIC_("Failed OnPanic\n");
        }
    }

    bool    Suite::RunSpecificTestFunc(const char* testFuncName, Output& output, bool contAfterFail)
    {
        //Get TestInfo that includes the appropriate test functions
        String funcNameStr = String(testFuncName);
        TestInfo testInfo;
        if(GetTestInfo(funcNameStr, testInfo) == false)
        {
            //When the appropriate test functions are not registered in the Suite
            return false;
        }

        PreProcessForSpecificTest(&output, contAfterFail);
        bool result = DoRunSpecificTest(testInfo, &output);
        PostProcessForSpecificTest();

        return result;
    }

    bool    Suite::RunSpecificTestFunc(const char* subSuiteName, const char* testFuncName, Output& output, bool contAfterFail)
    {
        //Get the sub Suite
        Suite* correspondSuite = NULL;
        String suiteNameStr = String(subSuiteName);
        if(GetSubSuite(suiteNameStr, &correspondSuite) == false)
        {
            //When the specified sub Suite does not exist
            return false;
        }

        return correspondSuite->RunSpecificTestFunc(testFuncName, output, contAfterFail);
    }

    bool    Suite::RunSpecificTestFunc(s32 testFuncId, Output& output, bool contAfterFail)
    {
        //Get TestInfo that includes the appropriate test functions
        TestInfo testInfo;
        if(GetTestSuiteAndInfo(testFuncId, NULL, testInfo) == false)
        {
            //When the appropriate test functions are not registered in the Suite
            return false;
        }

        PreProcessForSpecificTest(&output, contAfterFail);
        bool result = DoRunSpecificTest(testInfo, &output);
        PostProcessForSpecificTest();

#if defined(TEST_WITH_GUI)
        nn::test::FlushLog();
#endif
        return result;
    }

    bool Suite::GetTestFuncInfos(s32 testId, String& suiteName, String& testFuncName)
    {
       Suite* correspondSuite = NULL;
       TestInfo correspondTestInfo;
       bool resultGetInfo = GetTestSuiteAndInfo(testId, &correspondSuite, correspondTestInfo);
       if(resultGetInfo == true)
       {
           suiteName = correspondSuite->GetTestName();
           testFuncName = correspondTestInfo.testName;
           return true;
       }
       else
       {
           return false;
       }
    }

    bool Suite::GetTestFuncInfos(s32 testId, String& suiteName, String& testFuncName, String& testInfo)
    {
       Suite* correspondSuite = NULL;
       TestInfo correspondTestInfo;
       bool resultGetInfo = GetTestSuiteAndInfo(testId, &correspondSuite, correspondTestInfo);
       if(resultGetInfo == true)
       {
           suiteName = correspondSuite->GetTestName();
           testFuncName = correspondTestInfo.testName;
           testInfo = correspondTestInfo.testInfo;
           return true;
       }
       else
       {
           return false;
       }
    }

    void Suite::UnregisterTest(s32 testId)
    {
        NN_TASSERT_(m_TotalTestsNum == m_Tests.GetNum());
        if (m_TotalTestsNum < testId)
        {
            return;
        }

        m_Tests.DeleteElement(testId - 1);
        m_TotalTestsNum--;
    }


    bool    Suite::DoRunSpecificTest(Suite::TestInfo& testInfo, Output* pOutput)
    {
        /*
         * Success or failure of the test is set in m_IsTestSuccess. Before the test starts, m_IsTestSuccess is set to true. When it fails, it is reset to false.
         */
        m_IsTestSuccess = true;
        Time timeCase;
        bool testResult = true;

        SetUp();

        pOutput->OnTestStart(testInfo.testName);

        timeCase.Start();
        ::std::jmp_buf jumpBuf;
        m_pExitTestJumpBuffer = &jumpBuf;
        s_CurrentSuite = this;
        if(setjmp(jumpBuf) == 0)
        {
            (this->*testInfo.testFunc)();
        }
        else
        {
            /*
                                      For test in the "do not proceed to subsequent tests when an assert is encountered" mode, ExitCurrentTest is called and this path is taken.
              (Mode is specified by the Run() or RunSpecificTestFunc() argument)
                                      For test in the "do not proceed to subsequent tests when an assert is encountered" mode,this path is not taken at the time of the assert.
                                      Instead enters Suite::AddAssertInfo() and sets m_IsTestSuccess.
             */
            m_IsTestSuccess = false;
        }
        m_pExitTestJumpBuffer = NULL;
        s_CurrentSuite = 0;
        timeCase.End();
        pOutput->OnTestEnd(testInfo.testName, testResult, timeCase);

        TearDown();

        return m_IsTestSuccess;
    }

    bool Suite::GetSubSuite(String& subSuiteName, Suite** ppSuite)
    {
        NN_TASSERT_(ppSuite != NULL);
        bool isSuiteFound = false;
        const u32 subSuiteNum = m_SubSuites.GetNum();

        for(unsigned int i = 0; i < subSuiteNum; ++i)
        {
            Suite* suitPos = m_SubSuites.GetElement(i);
            if(suitPos->GetTestName() == subSuiteName)
            {
                *ppSuite = suitPos;
                isSuiteFound = true;
                break;
            }
        }

        return isSuiteFound;
    }

    bool Suite::GetTestSuiteAndInfo(s32 testId, Suite** ppSuite, Suite::TestInfo& testInfoBuf)
    {
        //Confirms whether the test function corresponding to the ID exists
         if(testId > m_TotalTestsNum)
         {
             //When it does not exist
             return false;
         }

         //Confirms whether the test corresponding to the ID exists in this Suite itself or in a sub-Suite
         if(testId <= m_Tests.GetNum())
         {
             //When it exists in this Suite itself
             if(GetTestInfo(testId, testInfoBuf) == false)
             {
                 return false;
             }
             
             if(ppSuite != NULL)
             {
                *ppSuite = this;
             }
             return true;
         }
         else
         {
             //When it exists in a sub-Suite
             u32 checkedIdMax = m_Tests.GetNum();//Maximum value of the confirmed ID. Used to check in which sub-Suite the function corresponding to the ID exists.//
             const u32 subSuiteNum = m_SubSuites.GetNum();
             for(unsigned int i = 0; i < subSuiteNum; ++i)
             {
                 Suite* pSuit = m_SubSuites.GetElement(i);
                 const u32 subSuiteMaxId = checkedIdMax + pSuit->GetTotalTestNum();
                 if(testId > subSuiteMaxId)
                 {
                     //Because the ID is not included in the sub-Suite indicated by pSuit, updates the checked ID and moves on to check the next sub-Suite.
                     checkedIdMax = subSuiteMaxId;
                 }
                 else
                 {
                     /*
                      * When the ID is included in the sub-Suite indicated by pSuit, the Suite and TestInfo is obtained with GetTestSuiteAndInfo() of that sub-Suite.
                      * The argument ID is converted to testID in the sub-Suite origin.
                      */
                     const u32 testIdInSubSuite = testId - checkedIdMax;
                     pSuit->GetTestSuiteAndInfo(testIdInSubSuite, ppSuite, testInfoBuf);
                     break;
                 }
             }

             return true;
         }
    }


    bool Suite::GetTestInfo(String funcName, Suite::TestInfo& testInfoBuf)
    {
        bool isInfoFound = false;
        const u32 infoNum = m_Tests.GetNum();
        for(unsigned int i = 0; i < infoNum; ++i)
        {
            TestInfo pTestInfo = m_Tests.GetElement(i);
            if(pTestInfo.testName == funcName)
            {
                isInfoFound = true;
                testInfoBuf = pTestInfo;
                break;
            }
        }

        return isInfoFound;
    }


    bool Suite::GetTestInfo(s32 testInfoId, Suite::TestInfo& testInfoBuf)
    {
        //Confirms whether TestInfo corresponding to the ID exists
        if((testInfoId > m_Tests.GetNum()) || (testInfoId == 0))
        {
            //When it does not exist
            return false;
        }

        testInfoBuf = m_Tests.GetElement((testInfoId-1));
        return true;
    }

    void Suite::Initialize()
    {
        if(m_IsInitialized == false)
        {
            InitializeSuite();
            m_IsInitialized = true;
        }
    }

    void Suite::Finalize()
    {
        if(m_IsInitialized == true)
        {
            FinalizeSuite();
#if defined(TEST_WITH_GUI)
            nn::test::FlushLog();
#endif
            m_IsInitialized = false;
        }
    }

    void Suite::PreProcessForSpecificTest(Output* pOutput, bool contAfterFail)
    {
        Initialize();
        m_Continue = contAfterFail;
        m_pOutput = pOutput;
        m_pOutput->OnInitialize(1, 1);
        m_pOutput->OnSuiteStart(1, GetTestName());
    }

    void Suite::PostProcessForSpecificTest()
    {
        Time time;//In the operation of a specific test, the operation time is output as 0 since it is meaningless to measure the operation time as a Suite (only the single unit test operation time needs to be known) //
        m_pOutput->OnSuiteEnd(1, GetTestName(), time);
        m_pOutput->OnFinished(1, time);
        Finalize();
    }

    Suite* Suite::GetCurrentSuite()
    {
        if ( !s_CurrentSuite )
        {
            NN_PANIC("No running test suite");
        }
        return s_CurrentSuite;
    }
}}

extern "C" int nnResultFailureHandler(nnResult result, const char* filename, int lineno, const char* fmt, ...)
{
    va_list vlist;
    va_start(vlist, fmt);
    nn::test::Suite::ResultHolder::ResultFailureHandler(reinterpret_cast<nn::Result&>(result), filename, lineno, fmt, vlist);
    va_end(vlist);
    return 0;
}

extern "C" int nnResultTFailureHandler(nnResult result, const char* filename, int lineno, const char* fmt, ...)
{
    va_list vlist;
    va_start(vlist, fmt);
    nn::test::Suite::ResultHolder::ResultFailureHandler(reinterpret_cast<nn::Result&>(result), filename, lineno, fmt, vlist);
    va_end(vlist);
    return 0;
}

extern "C" int nnResultPanicHandler(nnResult result, const char* filename, int lineno, const char* fmt, ...)
{
    va_list vlist;
    va_start(vlist, fmt);
    nn::test::Suite::ResultHolder::ResultPanicHandler(reinterpret_cast<nn::Result&>(result), filename, lineno, fmt, vlist);
    va_end(vlist);
    return 0;
}

extern "C" int nnResultTPanicHandler(nnResult result, const char* filename, int lineno, const char* fmt, ...)
{
    va_list vlist;
    va_start(vlist, fmt);
    nn::test::Suite::ResultHolder::ResultPanicHandler(reinterpret_cast<nn::Result&>(result), filename, lineno, fmt, vlist);
    va_end(vlist);
    return 0;
}
/*
void nn::dbg::Panic(const char* filename, int lineno, const char* fmt, va_list vlist)
{
    nn::Result result = nnMakeInvalidResult();
    nn::test::Suite::ResultHolder::ResultPanicHandler(reinterpret_cast<nn::Result&>(result), filename, lineno, fmt, vlist);
}

void nn::dbg::TVPanic(const char* filename, int lineno, const char* fmt, va_list vlist)
{
    nn::Result result = nnMakeInvalidResult();
    nn::test::Suite::ResultHolder::ResultPanicHandler(reinterpret_cast<nn::Result&>(result), filename, lineno, fmt, vlist);
}
*/
