// 55_JumpGame.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <map>
#include <deque>

using namespace std;

class Solution
{
  public:
    bool canReach(vector<int> &nums, int i, int j)
    {
        if (nums[i] == 0 && j - i > 0)
            return false;
        else if (nums[j] == 0 && j < nums.size() - 1)
            return false;
        else if (nums[i] >= j - i)
            return true;
        else
        {
            bool can = false;
            for (auto n = 1; n <= nums[i]; ++n)
            {
                if (nums[i + n] == 0)
                    continue;
                if (canReach(nums, i, i + n) && canReach(nums, i + n, j))
                {
                    can = true;
                    break;
                }
            }
            return can;
        }
    }
    bool canJump(vector<int> &nums)
    {
        auto lastPos = nums.size() - 1;

        return canReach(nums, 0, lastPos);
    }
};

class Solution2
{
  public:
    set<int> leftHandSide(vector<int> &nums, int start, int posOfZero)
    {
        set<int> middlePos;
        for (auto i = start; i < posOfZero; ++i)
        {
            if (i + nums[i] >= nums.size() - 1)
            {
                middlePos.insert(nums.size() - 1);
                break;
            }
            if (i + nums[i] > posOfZero)
            {
                for (auto n = 1; n <= (i + nums[i] - posOfZero); ++n)
                {
                    if (nums[posOfZero + n] != 0)
                        middlePos.insert(posOfZero + n);
                }
            }
        }
        return middlePos;
    }
    bool findZeroBeforeEnd(vector<int> &nums, int start, int &posOfZero)
    {
        vector<int>::iterator itrStart = nums.begin(); // +start;
        itrStart += start;
        auto itrZeroPos = find(itrStart, nums.end(), 0);

        if (itrZeroPos == nums.end() || itrZeroPos == nums.end() - 1)
        {
            return false;
        }
        else
        {
            posOfZero = distance(nums.begin(), itrZeroPos);
            return true;
        }
    }
    bool rightHandSide(vector<int> &nums, int start)
    {
        int zeroPos;
        if (!findZeroBeforeEnd(nums, start, zeroPos))
            return true;
        else
        {
            set<int> middlePos = leftHandSide(nums, start, zeroPos);
            if (middlePos.empty())
                return false;
            bool can = false;
            for (auto p : middlePos)
            {
                if (rightHandSide(nums, p))
                {
                    can = true;
                    break;
                }
            }
            return can;
        }
    }
    bool canJump(vector<int> &nums)
    {
        return rightHandSide(nums, 0);
    }
};

class Solution3
{
  public:
    bool canJump(vector<int> &nums)
    {
        if (nums.size() == 0)
            return false;
        if (nums.size() == 1)
            return true;

        auto reach = nums[0];

        for (auto i = 1; i <= reach; ++i)
        {
            reach = max(reach, i + nums[i]);
            if (reach >= nums.size() - 1)
                return true;
        }
        return false;
    }
};

class Solution961
{
  public:
    int repeatedNTimes(vector<int> &A)
    {
        int N = A.size() / 2;

        map<int, int> duplicate;
        for (auto i : A)
        {
            duplicate[i]++;
            if (duplicate[i] == N)
                return i;
        }
        return -1;
    }
};

class Solution962
{
  public:
    int maxWidthRamp(vector<int> &A)
    {
        int MaxWidth = 0;
        for (int i = 0; i < A.size() && A.size() - 1 - i > MaxWidth; ++i)
        {

            for (int j = A.size() - 1; j > i && j - i > MaxWidth; --j)
            {
                if (A[i] <= A[j])
                {
                    MaxWidth = j - i > MaxWidth ? j - i : MaxWidth;
                    break;
                }
            }
        }
        return MaxWidth;
    }
};
class Solution962_2
{
  public:
    int maxWidthRamp(vector<int> &A)
    {
        int TestRamp = A.size() - 1;
        for (int ramp = TestRamp; ramp > 0; --ramp)
        {
            for (int i = 0; i < A.size() - ramp; ++i)
            {
                if (A[i] <= A[i + ramp])
                    return ramp;
            }
        }
        return 0;
    }
};
class Solution962_3
{
  public:
    int findRampFromIndex(vector<int> &A, int index, int MaxRamp)
    {
        int TestRamp = A.size() - 1 - index;
        for (auto ramp = TestRamp; ramp > MaxRamp; --ramp)
        {
            if (A[index] <= A[index + ramp])
                return ramp;
        }
        return MaxRamp;
    }
    int maxWidthRamp(vector<int> &A)
    {
        vector<int> keys(A.size());
        int n = 0;
        generate(keys.begin(), keys.end(), [&]() { return n++; });

        stable_sort(keys.begin(), keys.end(), [&](int i, int j) {
            return (A[i] < A[j]);
        });

        int MaxRamp = 0;
        int minKey = A.size();
        for (auto k : keys)
        {
            auto ramp = k - minKey; //findRampFromIndex(A, v.second, MaxRamp);
            MaxRamp = ramp > MaxRamp ? ramp : MaxRamp;
            minKey = min(minKey, k);
        }
        return MaxRamp;
    }
};

class Solution962_test
{
  public:
    int maxWidthRamp(vector<int> &A)
    {
        int n = A.size();
        vector<int> t(n);
        t[0] = A[n - 1];
        for (int i = n - 2; i >= 0; i--)
            t[n - 1 - i] = max(t[n - 1 - i - 1], A[i]);

        int ans = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int l = 0, h = n - 2 - i;
            if (t[h] < A[i])
                continue;
            if (t[0] >= A[i])
            {
                ans = max(ans, n - i - 1);
                continue;
            }
            while (l + 1 < h)
            {
                int mid = (l + h) >> 1;
                if (t[mid] >= A[i])
                    h = mid;
                else
                    l = mid;
            }
            //cout << A[i] << " " << h << endl;
            ans = max(ans, n - h - 1 - i);
        }

        return ans;
    }
};

class Solution962_4
{
  public:
    int maxWidthRamp(vector<int> &A)
    {
        deque<int> Lows;
        for (int i = 0; i < A.size(); ++i)
        {
            if (Lows.empty() || A[Lows.front()] > A[i])
                Lows.push_front(i);
        }

        int ramp = 0;
        for (int i = A.size() - 1; i >= 0; --i)
        {
            while (!Lows.empty() && A[Lows.front()] <= A[i])
            {
                ramp = max(ramp, i - Lows.front());
                Lows.pop_front();
            }
        }
        return ramp;
    }
};

int main()
{
    vector<int> input{2, 3, 1, 1, 4};
    vector<int> in2{3, 2, 1, 0, 4};
    vector<int> in3{2, 0, 0};
    vector<int> in4{3, 0, 8, 2, 0, 0, 1};
    vector<int> in5{1, 1, 1, 0};

    Solution3 s;
    bool b = s.canJump(input);
    b = s.canJump(in2);
    b = s.canJump(in3);
    b = s.canJump(in4);
    b = s.canJump(in5);
    //    cout << b << endl;

    Solution961 s961;

    vector<int> in961{1, 2, 3, 3};
    vector<int> in961_2{2, 1, 2, 5, 3, 2};
    vector<int> in961_3{5, 1, 5, 2, 5, 3, 5, 4};
    int i961 = s961.repeatedNTimes(in961);
    //    cout << i961 << endl;
    i961 = s961.repeatedNTimes(in961_2);
    //    cout << i961 << endl;
    i961 = s961.repeatedNTimes(in961_3);
    //    cout << i961 << endl;

    Solution962_4 s962;
    vector<int> in962_1{6, 0, 8, 2, 1, 5};
    vector<int> in962_2{9, 8, 1, 0, 1, 9, 4, 0, 4, 1};
    vector<int> in962_3{0, 0};
    vector<int> in962_4{1, 0};
    vector<int> in962_5{9, 9, 8, 8, 7, 7};
    vector<int> in962_6{1, 2, 3, 4, 5, 6};
    vector<int> in962_7{6, 5, 4, 3, 2, 1};
    vector<int> in962_8{0, 0, 9, 9, 5, 5};
    vector<int> in962_9{3, 28, 15, 1, 4, 12, 6, 19, 8, 15, 3, 9, 6, 4, 13, 12, 6, 12, 10, 1, 2, 1, 4, 1, 4, 0, 0, 1, 1, 0};

    int out962 = s962.maxWidthRamp(in962_1);
    cout << out962 << endl;
    out962 = s962.maxWidthRamp(in962_2);
    cout << out962 << endl;
    out962 = s962.maxWidthRamp(in962_3);
    cout << out962 << endl;
    out962 = s962.maxWidthRamp(in962_4);
    cout << out962 << endl;
    out962 = s962.maxWidthRamp(in962_5);
    cout << out962 << endl;
    out962 = s962.maxWidthRamp(in962_6);
    cout << out962 << endl;
    out962 = s962.maxWidthRamp(in962_7);
    cout << out962 << endl;
    out962 = s962.maxWidthRamp(in962_8);
    cout << out962 << endl;
    out962 = s962.maxWidthRamp(in962_9);
    cout << out962 << endl;
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
