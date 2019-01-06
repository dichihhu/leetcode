#include <vector>
#include <cmath>

using namespace std;

class Solution970 {
public:
    vector<int> powerfulIntegers(int x, int y, int bound) {
        vector<int> vec_x_power{1}, vec_y_power{1};
        for (size_t i=1; ;++i) {
            auto px = pow(x, i);
            if (px==1 || px>=bound) break;
            else vec_x_power.push_back(px);
        }
        for (size_t i=1; ; ++i) {
            auto py = pow(y,i);
            if (py==1 || py>=bound) break;
            else vec_y_power.push_back(py);
        }
        auto isPowerful = [&](int i) {
            for (auto px:vec_x_power) {
                for (auto py:vec_y_power) {
                    if (px+py == i) return true;
                    if (px+py > i) break;
                }
            }
            return false;
        };
        vector<int> powerful;
        for (int i=1; i<=bound;i++) {
            if (isPowerful(i)) powerful.push_back(i);
        }
        return powerful;
    }
};