/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     test_TextOutput.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/test/test_TextOutput.h>
#include <nn/test/test_Time.h>

#define NN_PRINT_TEST_LOG(...) (void)::nn::dbg::detail::TPrintf(__VA_ARGS__)

namespace nn{ namespace test{
    TextOutput::TextOutput() : 
            m_CurrentSuiteIndex(0), m_SuiteNum(0), m_pSuiteInfos(NULL)
    {
    }

    TextOutput::~TextOutput()
    {
        Finalize();
    }
    
    void TextOutput::Initialize(int testsNum, int suitesNum)
    {
        NN_UNUSED_VAR(testsNum);
        m_SuiteNum = suitesNum;
        m_CurrentSuiteIndex = 0;
        m_CurrentTestIndex = 0;
        m_pSuiteInfos = new SuiteInfo[m_SuiteNum];
    }

    void TextOutput::Finalize()
    {
        delete [] m_pSuiteInfos;
    }

    void TextOutput::OnInitialize(int testsNum, int suitesNum)
    {
        NN_PRINT_TEST_LOG("Test initialize.\n");
        NN_PRINT_TEST_LOG("%d tests exist\n", testsNum);
        NN_PRINT_TEST_LOG("%d suites exist\n", suitesNum);

        if(m_pSuiteInfos)
        {
            Finalize();
        }
        Initialize(testsNum, suitesNum);
    }

    void TextOutput::OnFinished(int testsNum, const Time& time)
    {
        NN_PRINT_TEST_LOG("------------------------------\n");
        NN_PRINT_TEST_LOG("%d tests done.\n", testsNum);
        NN_PRINT_TEST_LOG("Elapsed time: %lld\n", time.GetElapsedTime());

        // Outputs assert list
        int  assertNum = 0;
        for(int i = 0; i < m_SuiteNum; ++i)
        {
            if(m_pSuiteInfos[i].failureNum == 0)
            {
                continue;
            }
            NN_PRINT_TEST_LOG("\n");
            NN_PRINT_TEST_LOG("[%s]\n", m_pSuiteInfos[i].suiteName.GetBuffer());
            for(int j = 0; j < m_pSuiteInfos[i].testsNum; ++j)
            {
                if(m_pSuiteInfos[i].pTestInfos[j].failureCount != 0)
                {
                    NN_PRINT_TEST_LOG(" [%s]\n", m_pSuiteInfos[i].pTestInfos[j].testName.GetBuffer());
                    AssertInfos& assertInfos = m_pSuiteInfos[i].pTestInfos[j].assertInfos;
                    while(!assertInfos.IsEmpty())
                    {
                        assertNum++;
                        PrintAssertInfo(assertInfos.PopFront());
                    }
                }
            }
        }
        if(assertNum == 0)
        {
            NN_PRINT_TEST_LOG("All tests PASSED\n");
        }
        else
        {
            NN_PRINT_TEST_LOG("%d asserts \n", assertNum);
            NN_PRINT_TEST_LOG("Tests FAILED\n");
        }
    }

    void TextOutput::PrintAssertInfo(const AssertInfo& info)
    {
        const String& fileName = info.GetFilename();
        const String& message = info.GetMessage();
        NN_PRINT_TEST_LOG(" - %s, line:%d, %s\n", fileName.GetBuffer(), info.GetLine(), message.GetBuffer());
    }

    void TextOutput::OnSuiteStart(int testsNum, const String testName)
    {
        NN_TASSERT_(m_pSuiteInfos);
        NN_PRINT_TEST_LOG("\n");
        NN_PRINT_TEST_LOG("[%s]\n", testName.GetBuffer());
        m_CurrentTestIndex = 0;
        m_pSuiteInfos[m_CurrentSuiteIndex].suiteName = testName;
        m_pSuiteInfos[m_CurrentSuiteIndex].testsNum = testsNum;
        m_pSuiteInfos[m_CurrentSuiteIndex].pTestInfos = new TestInfo[testsNum];
    }

    void TextOutput::OnSuiteEnd(int testsNum, const String suiteName,
            const Time& time)
    {
        NN_UNUSED_VAR(suiteName);
        
        NN_TASSERT_(m_pSuiteInfos);
        NN_PRINT_TEST_LOG("\n");
        NN_PRINT_TEST_LOG("  Number of tests        : %d\n", testsNum);
        NN_PRINT_TEST_LOG("  Number of failure tests: %d\n", m_pSuiteInfos[m_CurrentSuiteIndex].failureNum);
        NN_PRINT_TEST_LOG("  Elapsed time           : %lld\n", time.GetElapsedTime());

        m_pSuiteInfos[m_CurrentSuiteIndex].elapsedTime = time;
        m_CurrentSuiteIndex++;
    }
		
    void TextOutput::OnTestStart(const String testName)
    {
        NN_TASSERT_(m_pSuiteInfos);
        TestInfo info;
        m_pSuiteInfos[m_CurrentSuiteIndex].pTestInfos[m_CurrentTestIndex].testName = testName;
    }

    void TextOutput::OnTestEnd(const String testName, bool isSuccess,
            const Time& time)
    {
        NN_UNUSED_VAR(time);
        NN_TASSERT_(m_pSuiteInfos);
        if(!isSuccess)
        {
            NN_PRINT_TEST_LOG(" %s - [NG]\n", testName.GetBuffer());
        }
        ++m_CurrentTestIndex;
    }
		
    void TextOutput::OnAssert(const AssertInfo& info)
    {
        NN_TASSERT_(m_pSuiteInfos);
//        PrintAssertInfo(info);

        m_pSuiteInfos[m_CurrentSuiteIndex].pTestInfos[m_CurrentTestIndex].assertInfos.PushBack(info);
        if(m_pSuiteInfos[m_CurrentSuiteIndex].pTestInfos[m_CurrentTestIndex].failureCount == 0)
        {
            ++m_pSuiteInfos[m_CurrentSuiteIndex].failureNum;
        }
        ++m_pSuiteInfos[m_CurrentSuiteIndex].pTestInfos[m_CurrentTestIndex].failureCount;
    }

}}
