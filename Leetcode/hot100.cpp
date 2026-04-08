#include "../quick.h"

//1
vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> ump;
    for (int i = 0; i < nums.size(); ++i) {
        if (ump.find(target - nums[i]) != ump.end()) {
            return vector<int>{i, ump[target - nums[i]]};
        }
        ump[nums[i]] = i;
    }
    return vector<int>{};
}

//49
vector<vector<string> > groupAnagrams(vector<string> &strs) {
    int n = strs.size();
    vector<string> cp(strs.begin(), strs.end());
    vector<vector<string> > ans;
    for (int i = 0; i < n; ++i) {
        sort(cp[i].begin(), cp[i].end());
    }
    unordered_map<string, int> ump;
    for (int i = 0; i < n; ++i) {
        if (ump.find(cp[i]) != ump.end()) {
            ans[ump[cp[i]]].push_back(strs[i]);
        } else {
            ump[cp[i]] = ans.size();
            ans.push_back({strs[i]});
        }
    }
    return ans;
}

//128
//通过hashset去重并查找前一个元素，确定每个连续序列的开始，对每个开头向后查找，确定长度
int longestConsecutive(vector<int> &nums) {
    unordered_set<int> st;
    for (int i = 0; i < nums.size(); ++i) {
        st.insert(nums[i]);
    }

    int ans = 0;
    for (auto it = st.begin(); it != st.end(); ++it) {
        if (st.contains(*it - 1))continue;
        int len = 1;
        int start = *it;
        while (st.contains(start + 1)) {
            len++;
            start++;
        }
        ans = max(len, ans);
    }
    return ans;
}

//283
void moveZeroes(vector<int> &nums) {
    int low = 0;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        if (nums[i] != 0) {
            nums[low] = nums[i];
            low++;
        }
    }
    while (low < n)nums[low++] = 0;
    return;
}

//11
int maxArea(vector<int> &height) {
    int l = 0;
    int r = height.size() - 1;
    int ans = 0;
    while (r - l > 0) {
        ans = max(ans, (r - l) * min(height[l], height[r]));
        if (height[l] < height[r]) {
            l++;
        } else {
            r--;
        }
    }
    return ans;
}

//15
//为了确定不重复的答案，用三个数的大小关系保证，a < b < c && nums[a]<=nums[b]<=nums[c]
//检索答案时确保每个位置的数和上一次不一样，保证唯一答案
//a确定时，bc使用双指针寻找，根据nums[a]+nums[b]+nums[c]和0的大小关系，唯一确定指针移动方向
//只要步骤中设计修改下标，那么就一定要注意检查合理下标范围
vector<vector<int> > threeSum(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int> > ans;
    int n = nums.size();
    for (int a = 0; a <= n - 3; ++a) {
        if (a != 0 && nums[a] == nums[a - 1])continue;
        int b = a + 1;
        int c = n - 1;
        while (b < c) {
            if (nums[a] + nums[b] + nums[c] > 0) {
                c--;
                while (b < c && nums[c] == nums[c + 1])c--;
            } else if (nums[a] + nums[b] + nums[c] < 0) {
                b++;
                while (b < c && nums[b] == nums[b - 1])b++;
            } else {
                ans.push_back({nums[a], nums[b], nums[c]});
                b++;
                while (b < c && nums[b] == nums[b - 1])b++;
            }
        }
    }
    return ans;
}

//42
int trap(vector<int> &height) {
    int n = height.size();
    //每个位置雨水的高度是左右两侧最高高度的较小值
    //使用动态规划预处理获得每个位置的高度
    vector<int> maxleft(n);
    vector<int> maxright(n);
    maxleft[0] = 0;
    maxright[n - 1];
    for (int i = 1; i < n; ++i) {
        maxleft[i] = max(maxleft[i - 1], height[i - 1]);
    }
    for (int i = n - 2; i >= 0; --i) {
        maxright[i] = max(maxright[i + 1], height[i + 1]);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int val = min(maxleft[i], maxright[i]);
        if (val > height[i]) {
            ans += val - height[i];
        }
    }
    return ans;
}

int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto res = threeSum(nums);
    return 0;
}
