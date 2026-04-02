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

int main() {
    vector<string> in{"eat", "tea", "tan", "ate", "nat", "bat"};
    auto ans = groupAnagrams(in);
    return 0;
}
