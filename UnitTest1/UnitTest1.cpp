#include "pch.h"
#include "CppUnitTest.h"
#define UNIT_TEST
#include "C:\Users\sasab\source\repos\LR10.2B\LR10.2B\LR10.2B.cpp"
#include <cmath>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

Student* Sample()
{
    Student* s = new Student[4];
    s[0] = { "Shevchenko", 2, CS, 5, 5,{ 5 } };
    s[1] = { "Koval", 1, INF, 5, 4,{ 0 } };
    s[1].numerical = 5;
    s[2] = { "Bondar", 1, ME, 4, 4,{ 0 } };
    s[2].pedagogy = 4;
    s[3] = { "Adam", 2, CS, 5, 5,{ 4 } };
    return s;
}

namespace UnitTests
{
    TEST_CLASS(StudentTests)
    {
    public:
        TEST_METHOD(Test1)
        {
            Student* s = Sample();
            int index[4];
            IndexSort(s, index, 4);
            Student key = s[1];
            key.surname = "Unknown";
            bool ok = (index[0] == 3 && index[1] == 0 && index[2] == 1 && index[3] == 2);
            delete[] s;
            Assert::IsTrue(ok);
        }
        TEST_METHOD(Test2)
        {
            Student* s = Sample();
            int index[4];
            IndexSort(s, index, 4);
            Student key = s[1];
            key.surname = "Unknown";
            bool ok = (s[0].surname == "Shevchenko");
            delete[] s;
            Assert::IsTrue(ok);
        }
        TEST_METHOD(Test3)
        {
            Student* s = Sample();
            int index[4];
            IndexSort(s, index, 4);
            Student key = s[1];
            key.surname = "Unknown";
            bool ok = (BinSearch(s, index, 4, s[1]) == 1);
            delete[] s;
            Assert::IsTrue(ok);
        }
        TEST_METHOD(Test4)
        {
            Student* s = Sample();
            int index[4];
            IndexSort(s, index, 4);
            Student key = s[1];
            key.surname = "Unknown";
            bool ok = (BinSearch(s, index, 4, key) == -1);
            delete[] s;
            Assert::IsTrue(ok);
        }
        TEST_METHOD(Test5)
        {
            Student* s = Sample();
            int index[4];
            IndexSort(s, index, 4);
            Student key = s[1];
            key.surname = "Unknown";
            Sort(s, 4);
            bool ok = (s[0].surname == "Adam" && s[1].surname == "Shevchenko" && s[2].surname == "Koval" && s[3].surname == "Bondar");
            delete[] s;
            Assert::IsTrue(ok);
        }
    };
}
