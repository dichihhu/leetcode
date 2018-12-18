// RepeatedStringMatch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
using namespace std;

class Solution2 {
public:
    int repeatedStringMatch(string A, string B) {
        string multipleA = A;
        auto repeat = 1;
        while (multipleA.length() < B.length()) {
            multipleA += A;
            ++repeat;
        }
        if (multipleA.find(B) != string::npos) return repeat;
        if ((multipleA + A).find(B) != string::npos) return repeat + 1;
        return -1;
    }
};
class Solution3 {
public:
    int repeatedStringMatch(string A, string B) {

        auto checkPos = 0;
        for (; checkPos < A.length(); ++checkPos) {
            auto repeat = 1;
            auto j = 0;
            auto i = checkPos;
            for (; j < B.length(); ++j) {
                if (i == A.length()) {
                    i = 0;
                    ++repeat;
                }
                if (A[i] == B[j]) ++i;
                else break;
            }
            if (j == B.length()) return repeat;
        }
        return -1;
    }
};
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        if (A.find(B) != string::npos) return 1;
        
        //before duplicate A, firstly find if A's any rotation form is a substr of B
        if (A.length() <= B.length()) {
            string rotateA = A;
            auto n = 0;
            for (; n < A.length(); ++n) {
                if (B.find(rotateA) != string::npos) break;
                rotateA = rotateA.substr(1) + rotateA.substr(0, 1);
            }
            if (n == A.length()) return -1;
        }

        auto repeat = 1;
        string multipleA = A;
        while (multipleA.find(B) == string::npos ) {
            if (multipleA.length() > 10000) {
                repeat = -1;
                break;
            }
            multipleA += A;
            ++repeat;
        }

        return repeat;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    string A{ "a" };
    string B{ "aa" };

    Solution3 s;
    auto ans = s.repeatedStringMatch(A, B);

	return 0;
}

//aa
//a

//ab
//abab

//ab ab ab
//baba//

//abcd abcd abcd
//dabcda

//b
//ab [non existing character]

//ab ab
//ba

//abc abc abc
//bca

//abc abc abc
//acb [different character order]

//abc abc abc, bca, cab
//cba [A's any one of the rotates is not a substr of B]

//aaac
//aac

//aa
//a

//a
//aa

//abcd
//dabcda

//aabaa
//aaab