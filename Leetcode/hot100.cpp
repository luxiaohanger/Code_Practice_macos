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


int main() {
    vector<string> in{"eat", "tea", "tan", "ate", "nat", "bat"};
    auto ans = groupAnagrams(in);
    return 0;
}
