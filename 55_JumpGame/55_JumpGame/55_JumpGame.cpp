// 55_JumpGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    bool canReach(vector<int>& nums, int i, int j) {
        if (nums[i] == 0 && j - i > 0) return false;
        else if (nums[j] == 0 && j < nums.size() - 1) return false;
        else if (nums[i] >= j - i) return true;
        else {
            bool can = false;
            for (auto n = 1; n <= nums[i]; ++n) {
                if (nums[i+n] == 0) continue;
                if (canReach(nums, i, i + n) && canReach(nums, i + n, j)) {
                    can = true;
                    break;
                }
            }
            return can;
        }
    }
    bool canJump(vector<int>& nums) {
        auto lastPos = nums.size()-1;

        return canReach(nums, 0, lastPos);
    }
};

class Solution2 {
public:
    set<int> leftHandSide(vector<int>& nums, int start, int posOfZero) {
        set<int> middlePos;
        for (auto i = start; i < posOfZero; ++i) {
            if (i + nums[i] >= nums.size() - 1){
                middlePos.insert(nums.size() - 1);
                break;
            }
            if (i + nums[i] > posOfZero) {
                for (auto n = 1; n <= (i + nums[i] - posOfZero); ++n) {
                    if (nums[posOfZero+n] !=0) middlePos.insert(posOfZero + n);
                }
            }
        }
        return middlePos;
    }
    bool findZeroBeforeEnd(vector<int>& nums, int start, int& posOfZero) {
        vector<int>::iterator itrStart = nums.begin();// +start;
        itrStart += start;
        auto itrZeroPos = find(itrStart, nums.end(), 0);

        if (itrZeroPos == nums.end() || itrZeroPos == nums.end() - 1) {
            return false;
        }
        else {
            posOfZero = distance(nums.begin(), itrZeroPos);
            return true;
        }
    }
    bool rightHandSide(vector<int>& nums, int start) {
        int zeroPos;
        if (!findZeroBeforeEnd(nums, start, zeroPos)) return true;
        else {
            set<int> middlePos = leftHandSide(nums, start, zeroPos);
            if (middlePos.empty()) return false;
            bool can = false;
            for (auto p : middlePos) {
                if (rightHandSide(nums, p)) {
                    can = true;
                    break;
                }
            }
            return can;
        }
    }
    bool canJump(vector<int>& nums) {
        return rightHandSide(nums, 0);
    }
};

class Solution3 {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() == 0) return false;
        if (nums.size() == 1) return true;

        auto reach = nums[0];

        for (auto i = 1; i <= reach; ++i) {
            reach = max(reach, i + nums[i]);
            if (reach >= nums.size() - 1) return true;
        }
        return false;
    }

};
int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> input{ 2, 3, 1, 1, 4 };
    vector<int> in2{ 3, 2, 1, 0, 4 };
    vector<int> in3{ 2, 0, 0 };
    vector<int> in4{ 3, 0, 8, 2, 0, 0, 1 };
    vector<int> in5{ 1, 1, 1, 0 };

    Solution3 s;
    bool b = s.canJump(input);
    b = s.canJump(in2);
    b = s.canJump(in3);
    b = s.canJump(in4);
    b = s.canJump(in5);
	return 0;
}

//Input:[2, 3, 1, 1, 4]
//Output : true
//Explanation : Jump 1 step from index 0 to 1, then 3 steps to the last index.
//
//Input : [3, 2, 1, 0, 4]
//Output : false
//Explanation : You will always arrive at index 3 no matter what.Its maximum
//jump length is 0, which makes it impossible to reach the last index.

// [0,0,0,0]
// [1,1,1,1]
// [2,2,2,2]
// [1,0] : total steps >= lastPos
// [1,1,0]
// [2,0,0] : total steps can skip 1 slot
// [0,2,0] : 
// [3,0,0,0] : total steps ok, can skip 2 slots
// [2,1,0,0] (x)
// [1,2,0,0]
// [0, xxx] : no go
// [xxx, 0] : no effect
// [xxx, 0, xxx] : no 0 on the left hand side , the nums[left] must larger than distance from any left index to the position of 0.