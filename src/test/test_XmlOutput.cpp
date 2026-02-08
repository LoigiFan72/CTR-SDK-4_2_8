/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     test_XmlOutput.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/test/test_XmlOutput.h>
#include <nn/test/test_Time.h>
#include <cstring>
#include <cstdlib>

#define NN_PRINT_TEST_LOG(...) (void)::nn::dbg::detail::TPrintf(__VA_ARGS__)

using namespace nn::dbg;

namespace nn{ namespace test{

    namespace {
        void PrintXmlHeader() {
            NN_PRINT_TEST_LOG("<?xml version=\"1.0\"?>\n");
        }

        void PrintNnTestHeader()
        {
            NN_PRINT_TEST_LOG("<!-- begin: nntest-Results.xml -->\n");
        }

        void PrintNnTestFooter()
        {
            NN_PRINT_TEST_LOG("<!-- end: nntest-Results.xml -->\n");
        }

        void PrintCunitEndMarker(bool isSuccess)
        {
            NN_PRINT_TEST_LOG("CU_TEST_EXIT:%s\n", isSuccess ? "SUCCESS" : "FAIL");
        }

        // Converts special characters
        // & ---> &amp;
        // < ---> &lt;
        // > ---> &gt;
        // " ---> &quot;
        // ' ---> &apos; 
        String ConvertToXmlString(const char* string)
        {
            const int STR_LEN = 383;
            char buf[STR_LEN + 1];

            const char  specials[]  = {'&', '<', '>', '"', '\''};
            const char* converts[] = {"&amp;", "&lt;", "&gt;", "&quot;", "&apos;"};
            const int   copyLens[] = {5, 4, 4, 6, 6};
            const int   SPECIALS_NUM = sizeof(specials);
            const char* pSrc = string;
            char* pDst = buf;
            while(*pSrc != '\0')
            {
                int index = 0;
                for(index = 0; index < SPECIALS_NUM; ++index)
                {
                    if(*pSrc == specials[index])
                    {
                        if(pDst + copyLens[index] - buf > STR_LEN)
                        {
                            NN_TPANIC_("Failed to convert '%s', too long.\n", string);
                        }
                        ::std::memcpy(pDst, converts[index], copyLens[index]);
                        pDst += copyLens[index];
                        break;
                    }
                }
                if(index == SPECIALS_NUM) // Not a special character
                {
                    if(pDst + 1 - buf > STR_LEN)
                    {
                        NN_TPANIC_("Failed convert '%s', too long.\n", string);
                    }
                    *pDst++ = *pSrc;
                }
                pSrc++;
            }
            *pDst = '\0';
            return String(buf);
        }

    }
// --------------------------------------------------------

    void Attribute::Print()
    {
        NN_PRINT_TEST_LOG(" %s=\"", m_Name.GetBuffer());
        NN_PRINT_TEST_LOG(ConvertToXmlString(m_Value.GetBuffer()).GetBuffer());
        NN_PRINT_TEST_LOG("\"");
    }
// --------------------------------------------------------

    Node::~Node()
    {
        // Destroy attribute
        for(Attribute* pAttr = m_Attributes.PopFront();
            pAttr;
            pAttr = m_Attributes.PopFront())
        {
            delete pAttr;
        }
        // Destroy child element
        for(Node* pNode = m_Children.PopFront();
            pNode;
            pNode = m_Children.PopFront())
        {
            delete pNode;
        }
    }

    Node*   Node::CreateChildNode(const char* name)
    {
        Node*   pChild = new Node();
        if(pChild == NULL)
        {
            return NULL;
        }
        pChild->m_Name = name;

        AddChildNode(pChild);
        return pChild;
    }

    void    Node::SetAttribute(const char* name, const char* value)
    {
        Attribute* pAttr = new Attribute(name, value);
        if(pAttr == NULL)
        {
            NN_TPANIC_("Failed to set attribute");
        }
        m_Attributes.PushBack(pAttr);
    }

    void Node::PrintIndent(int depth)
    {
        // Indent output
        for(int i = 0; i < depth * INDENT; ++i)
        {
            NN_PRINT_TEST_LOG(" ");
        }
    }

    void Node::PrintBeginTag()
    {
        // Name output
        NN_PRINT_TEST_LOG("<");
        NN_PRINT_TEST_LOG(m_Name.GetBuffer());

        // Attribute output
        for(Attribute* pAttr = m_Attributes.GetFront();
            pAttr;
            pAttr = m_Attributes.GetNext(pAttr))
        {
            pAttr->Print();
        }

        // Tag finish
        NN_PRINT_TEST_LOG(">");

    }

    void Node::PrintEndTag()
    {
        NN_PRINT_TEST_LOG("</%s>", m_Name.GetBuffer());
    }

    void Node::Print(int depth)
    {
        // Indent
        PrintIndent(depth);

        // Output start tag
        PrintBeginTag();

        // TODO:
        // If there is a value AND child element
        // Panic for now
        if(m_Value != "" && !m_Children.IsEmpty())
        {
            NN_TPANIC_("<%s> has value and children", m_Name.GetBuffer());
        }
        
        // Output value
        if(m_Value != "")
        {
//            OutputDebugString("%s", m_Value.GetBuffer());
            NN_PRINT_TEST_LOG(ConvertToXmlString(m_Value.GetBuffer()).GetBuffer());
        }
        // Child element output
        else if(!m_Children.IsEmpty())
        {
            NN_PRINT_TEST_LOG("\n");
            for(Node* pNode = m_Children.GetFront();
                pNode;
                pNode = m_Children.GetNext(pNode))
            {
                pNode->Print(depth + 1);
            }
            PrintIndent(depth);
        }
        
        // Output end tag
        PrintEndTag();

        // Newline
        NN_PRINT_TEST_LOG("\n");
    }



    int Node::GetSpecificChildrenNum(const char* name)
    {
        int num = 0;
        if(!m_Children.IsEmpty())
        {
            for(Node* pNode = m_Children.GetFront();
                pNode;
                pNode = m_Children.GetNext(pNode))
            {
                if(String(name) == pNode->GetName())
                {
                    ++num;
                }

                num += pNode->GetSpecificChildrenNum(name);
            }
        }

        return num;
    }

// --------------------------------------------------------

    XmlOutput::XmlOutput() : m_pCurrentSuiteResult(NULL), m_pCurrentCaseResult(NULL), m_OutputMutex(false)
    {
    }

    XmlOutput::~XmlOutput()
    {
        for(Node* pNode = m_Results.PopFront();
            pNode;
            pNode = m_Results.PopFront())
        {
            delete pNode;
        }
    }
    

    void XmlOutput::OnInitialize(int testsNum, int suitesNum)
    {
        NN_TASSERT_(m_Results.IsEmpty());

        NN_PRINT_TEST_LOG("%d tests exist\n", testsNum);
        NN_PRINT_TEST_LOG("%d suites exist\n", suitesNum);

        m_IsSuccess = true;
    }

    void XmlOutput::OnFinished(int testsNum, const Time& time)
    {
        NN_UNUSED_VAR(testsNum);
        NN_UNUSED_VAR(time);

        for(Node* pResult = m_Results.GetFront();
            pResult;
            pResult = m_Results.GetNext(pResult))
        {
            NN_PRINT_TEST_LOG("----------------------------------\n");
            PrintNnTestHeader();
            PrintXmlHeader();
            pResult->Print();
            PrintNnTestFooter();
        }
        m_Results.Clear();

        PrintCunitEndMarker(m_IsSuccess);
    }


    void XmlOutput::OnSuiteStart(int testsNum, const String testName)
    {
        NN_PRINT_TEST_LOG("Suite: %s\n", testName.GetBuffer());

        //Create root node for XML to store the result of this suite
        m_pCurrentSuiteResult = new Node("testsuite");
        NN_TASSERT_(m_pCurrentSuiteResult);
        m_pCurrentSuiteResult->SetAttribute("name", testName.GetBuffer());
        m_pCurrentSuiteResult->SetAttribute("tests", testsNum);

        m_Results.PushBack(m_pCurrentSuiteResult);
    }

    void XmlOutput::OnSuiteEnd(int testsNum, const String suiteName,
            const Time& time)
    {
        NN_UNUSED_VAR(suiteName);
        NN_UNUSED_VAR(time);
        NN_UNUSED_VAR(testsNum);
        int errorNum = m_pCurrentSuiteResult->GetSpecificChildrenNum("error");
        m_pCurrentSuiteResult->SetAttribute("errors", errorNum);
        m_pCurrentSuiteResult->SetAttribute("time", time.GetElapsedTime());
    }
		
    void XmlOutput::OnTestStart(const String testName)
    {
        NN_PRINT_TEST_LOG("  Test: %s ...\n", testName.GetBuffer());
        m_CurrentTestName = testName;

        NN_TASSERT_(m_pCurrentCaseResult == NULL);
        NN_TASSERT_(m_pCurrentSuiteResult);
        m_pCurrentCaseResult = m_pCurrentSuiteResult->CreateChildNode("testcase");
        m_pCurrentCaseResult->SetAttribute("classname", "nn");
        m_pCurrentCaseResult->SetAttribute("name", m_CurrentTestName.GetBuffer());
    }

    void XmlOutput::OnTestEnd(const String testName, bool isSuccess,
            const Time& time)
    {
        NN_UNUSED_VAR(time);
        NN_UNUSED_VAR(testName);
        NN_UNUSED_VAR(isSuccess);

        m_pCurrentCaseResult->SetAttribute("time", time.GetElapsedTime());
        m_pCurrentCaseResult = NULL;
    }

    void XmlOutput::PrintAssertInfo(const AssertInfo& info)
    {
        const String& fileName = info.GetFilename();
        const String& message = info.GetMessage();

        NN_PRINT_TEST_LOG("   - %s, line:%d, ", fileName.GetBuffer(), info.GetLine());
        NN_PRINT_TEST_LOG(message.GetBuffer());
        NN_PRINT_TEST_LOG("\n");
    }
		
    void XmlOutput::OnAssert(const AssertInfo& info)
    {
        nn::os::Mutex::ScopedLock lk(m_OutputMutex);
        PrintAssertInfo(info);

        Node* pErrorNode = m_pCurrentCaseResult->CreateChildNode("error");
        pErrorNode->SetAttribute("type", "");
        pErrorNode->SetAttribute("message", info.GetMessage().GetBuffer());
        String value = "File: ";
        value += info.GetFilename();
        value += " Line:";
        value += String(info.GetLine());
        pErrorNode->SetValue(value.GetBuffer());

        m_IsSuccess = false;        // Fails even if one assert is called
    }

}}
