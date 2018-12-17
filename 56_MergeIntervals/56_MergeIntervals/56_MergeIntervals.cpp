// 56_MergeIntervals.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <deque>
using namespace std;


//Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution56 {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        if (intervals.size() < 2) return intervals;

        auto less = [](const Interval& a, const Interval& b) {
            return a.start < b.start;
        };
        sort(intervals.begin(), intervals.end(), less);

        auto overlapped = [](const Interval& a, const Interval& b) {
            return a.end >= b.start;
        };

        auto merge2 = [](const Interval& a, const Interval& b) {
            return Interval(min(a.start, b.start), max(a.end, b.end));
        };

        deque<Interval> temp(intervals.begin(), intervals.end());
        vector<Interval> result;

        while(temp.size() > 1) {
            auto next = temp.cbegin();
            if (overlapped(*next, *(next + 1))) {
                Interval merged = merge2(*next, *(next+1));
                temp.pop_front();
                temp.pop_front();
                temp.push_front(merged);
            }
            else {
                result.push_back(temp.front());
                temp.pop_front();
            }
        }
        result.push_back(temp.front());
        return result;
    }
};

class Solution56_1 {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        if (intervals.size() < 2) return intervals;

        auto less = [](const Interval& a, const Interval& b) {
            return a.start < b.start;
        };
        sort(intervals.begin(), intervals.end(), less);

        auto overlapped = [](const Interval& a, const Interval& b) {
            return a.end >= b.start;
        };

        auto merge2 = [](const Interval& a, const Interval& b) {
            return Interval(min(a.start, b.start), max(a.end, b.end));
        };

        vector<Interval> result;
        for (auto i : intervals) {
            if (result.empty() ||
                result.back().end < i.start) {
                result.push_back(i);
            }
            else {
                result.back().end = max(result.back().end, i.end);
            }
        }
        return result;
    }
};

class Solution56_2 {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        //vector<int> starts, ends;
        deque<int> starts, ends;
        for (auto i : intervals) {
            starts.push_back(i.start);
            ends.push_back(i.end);
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());
        starts.push_back(INT_MAX);
        vector<int> tempItvl;
        vector<Interval> result;
        while (!ends.empty()) {
            if (starts.front() <= ends.front()) {
                tempItvl.push_back(starts.front());
                starts.pop_front();
            }
            else {
                if (tempItvl.size() == 1) {
                    result.push_back(Interval(tempItvl.back(), ends.front()));
                    ends.pop_front();
                    tempItvl.pop_back();
                }
                else {
                    tempItvl.pop_back();
                    ends.pop_front();
                }
            }
        }
        return result;
    }
};

class Solution56_3 {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        multiset<int> start_list;
        multiset<int> end_list;

        for (auto i : intervals) {
            start_list.insert(i.start);
            end_list.insert(i.end);
        }
        start_list.insert(INT_MAX);

        vector<Interval> result;
        vector<int> tempItv;
        auto s_itr = start_list.begin();
        auto e_itr = end_list.begin();

        while (e_itr != end_list.end()) {
            if (*s_itr <= *e_itr) {
                tempItv.push_back(*s_itr);
                ++s_itr;
            }
            else {
                if (tempItv.size() == 1) {
                    result.push_back(Interval(tempItv.front(), *e_itr));
                    tempItv.pop_back();
                    ++e_itr;
                }
                else {
                    tempItv.pop_back();
                    ++e_itr;
                }
            }
        }
        return result;
    }
};

class Solution1 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> complement;
        for (auto i = 0; i < nums.size(); ++i) {
            auto itr = complement.find(nums[i]);
            if (itr != complement.end())
                return{ itr->second, i };
            else complement[target - nums[i]] = i;
        }
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> input{ 2, 7, 11, 15 };
    int target = 9;
    Solution1 s;
    vector<int> ans = s.twoSum(input, target);

    vector<Interval> input56 = { Interval(4, 5), Interval(2, 4), Interval(4, 6), Interval(3, 4), Interval(0, 0), Interval(1, 1), Interval(3, 5), Interval(2, 2) };
    Solution56 s56;
    vector<Interval> ans56 = s56.merge(input56);

    Solution56 s56_1;
    vector<Interval> ans56_1 = s56_1.merge(input56);

    Solution56_2 s56_2;
    vector<Interval> ans56_2 = s56_2.merge(input56);

    Solution56_3 s56_3;
    vector<Interval> ans56_3 = s56_3.merge(input56);
    return 0;
}

