// 55_JumpGame.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <map>
#include <deque>

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

class Solution961 {
public:
    int repeatedNTimes(vector<int>& A) {
    	int N = A.size()/2;

        map<int, int> duplicate;
        for (auto i:A) {
        	duplicate[i] ++;
        	if (duplicate[i] == N) return i;
        }
        return -1;
    }
};

class Solution962 {
public:
    int maxWidthRamp(vector<int>& A) {
    	int MaxWidth = 0;
    	for (int i=0; i<A.size() && A.size()-1-i > MaxWidth; ++i) {

    		for (int j=A.size()-1; j>i && j-i>MaxWidth; --j) {
    			if (A[i] <= A[j]) {
    				MaxWidth = j-i > MaxWidth? j-i : MaxWidth;
    				break;
    			}

    		}
    	}
    	return MaxWidth;
    }

};
class Solution962_2 {
public:
    int maxWidthRamp(vector<int>& A) {
    	int TestRamp = A.size()-1;
    	for (int ramp=TestRamp; ramp>0; --ramp) {
    		for (int i=0; i<A.size()-ramp; ++i) {
    			if (A[i] <= A[i+ramp]) return ramp;
    		}
    	}
    	return 0;
    }
};
class Solution962_3 {
public:
	int findRampFromIndex(vector<int>& A, int index, int MaxRamp) {
		int TestRamp = A.size()-1-index;
		for (auto ramp=TestRamp; ramp>MaxRamp; --ramp) {
			if(A[index] <= A[index+ramp]) return ramp;
		}
		return MaxRamp;
	}
    int maxWidthRamp(vector<int>& A) {
    	vector<int> keys(A.size());
    	int n=0;
    	generate(keys.begin(), keys.end(), [&](){return n++;});

    	stable_sort(keys.begin(), keys.end(), [&](int i, int j){
    		return (A[i] < A[j]);
    	});

    	int MaxRamp = 0;
    	int minKey = A.size();
    	for (auto k : keys) {
    		auto ramp = k - minKey; //findRampFromIndex(A, v.second, MaxRamp);
    		MaxRamp = ramp > MaxRamp? ramp : MaxRamp;
    		minKey = min(minKey, k);
    	}
    	return MaxRamp;
    }
};

class Solution962_test {
public:
    int maxWidthRamp(vector<int>& A) {
        int n = A.size();
        vector< int > t( n );
        t[0] = A[n-1];
        for(int i = n - 2 ; i >= 0 ; i--)
            t[n-1-i] = max( t[n-1-i-1], A[i] );

        int ans = 0;
        for(int i = 0 ; i < n - 1; i++){
            int l = 0, h = n - 2 - i;
            if( t[h] < A[i] )
                continue;
            if( t[0] >= A[i] ){
                ans = max( ans, n - i - 1 );
                continue;
            }
            while( l + 1 < h ){
                int mid = (l + h)>>1;
                if( t[mid] >= A[i] )
                    h = mid;
                else
                    l = mid;
            }
            //cout << A[i] << " " << h << endl;
            ans = max( ans, n - h - 1 - i );
        }

        return ans;
    }
};

class Solution962_4 {
public:
    int maxWidthRamp(vector<int>& A) {
    	deque<int> Lows;
    	for (int i=0; i<A.size(); ++i) {
    		if (Lows.empty() || A[Lows.front()] > A[i]) Lows.push_front(i);
    	}

    	int ramp =0;
    	for (int i=A.size()-1; i>=0; --i) {
    		while (!Lows.empty() && A[Lows.front()]<= A[i]) {
    			ramp = max(ramp, i-Lows.front());
    			Lows.pop_front();
    		}
    	}
    	return ramp;
    }
};
