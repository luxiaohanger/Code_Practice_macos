#include "../quick.h"

//738
int monotoneIncreasingDigits(int n) {
    if (n == 0)return 0;
    string s = to_string(n);
    int flag = s.size(); //注意初始化
    //逆向构造 同时改变数字
    for (int i = s.size() - 1; i > 0; --i) {
        if (s[i] < s[i - 1]) {
            s[i - 1]--;
            flag = i;
        }
    }

    for (int i = flag; i < s.size(); ++i)s[i] = '9';

    return stoi(s); //巧妙忽略字符串前导 0
}


//968
int dfs968(TreeNode *root, int &cnt) {
    // 1 被监控   0 不被监控  2 是监控
    if (!root)return 1;
    int l = dfs968(root->left, cnt);
    int r = dfs968(root->right, cnt);
    if (l == 0 || r == 0) {
        cnt++;
        return 2;
    }

    if (l == 2 || r == 2)return 1;
    return 0;
}

int minCameraCover(TreeNode *root) {
    int cnt = 0;
    int k = dfs968(root, cnt);
    if (k == 0)cnt++;
    return cnt;
}

//561
int arrayPairSum(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    int ans = 0;
    for (int i = 0; i < nums.size(); i += 2) {
        ans += nums[i];
    }
    return ans;
}

//198
int rob(vector<int> &nums) {
    int n = nums.size();
    vector<int> dp(n);

    dp[0] = nums[0];
    if (n > 1) {
        dp[1] = max(nums[0], nums[1]);
    }

    for (int i = 2; i < n; ++i) {
        dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
    }
    return dp[n - 1];
}

//300
int lengthOfLIS(vector<int> &nums) {
    int n = nums.size();
    if (n <= 1)return n;
    vector<int> dp(n);

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i])dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(dp[i], ans);
    }
    return ans;
}

//213
int rob2(vector<int> &nums) {
    int n = nums.size();
    vector<int> dp(n);
    vector<int> pd(n);

    if (n == 1)return nums[0];
    dp[0] = nums[0];
    if (n > 1) {
        dp[1] = max(nums[0], nums[1]);
    }

    for (int i = 2; i < n - 1; ++i) {
        dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
    }

    if (n > 1)pd[1] = nums[1];

    for (int i = 2; i < n; ++i) {
        pd[i] = max(pd[i - 2] + nums[i], pd[i - 1]);
    }

    return max(dp[n - 2], pd[n - 1]);
}

//337
unordered_map<TreeNode *, int> umap;

int rob(TreeNode *root) {
    if (!root)return 0;
    if (umap[root])return umap[root];
    auto l = root->left;
    auto r = root->right;
    if (!l && !r) {
        return root->val;
    }
    int ansl = rob(l);
    int ansr = rob(r);

    int ll = 0, lr = 0, rl = 0, rr = 0;
    if (l) {
        ll = rob(l->left);
        lr = rob(l->right);
    }
    if (r) {
        rl = rob(r->left);
        rr = rob(r->right);
    }
    umap[root] = max(root->val + ll + lr + rl + rr, ansl + ansr);
    return umap[root];
}

//123
int maxProfit(vector<int> &prices) {
    vector<vector<int> > dp(prices.size(), vector<int>(5));
    dp[0][1] = -prices[0];
    dp[0][3] = -prices[0];
    for (int i = 1; i < prices.size(); ++i) {
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
        dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
        dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
    }

    return dp[prices.size() - 1][4];
}

//188
int maxProfit(int k, vector<int> &prices) {
    vector<vector<int> > dp(prices.size(), vector<int>(2 * k + 1));

    for (int i = 1; i < 2 * k; i += 2) {
        dp[0][i] = -prices[0];
    }

    for (int i = 1; i < prices.size(); ++i) {
        for (int j = 1; j < 2 * k; j += 2) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] - prices[i]);
            dp[i][j + 1] = max(dp[i - 1][j + 1], dp[i - 1][j] + prices[i]);
        }
    }

    return dp[prices.size() - 1][2 * k];
}

//309
int maxProfit_plus(vector<int> &prices) {
    vector<vector<int> > dp(prices.size(), vector<int>(4)); //0 持有 1 卖出 2 非持有 3 冷冻

    dp[0][0] = -prices[0];

    for (int i = 1; i < prices.size(); ++i) {
        dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][2] - prices[i], dp[i - 1][3] - prices[i]));
        dp[i][1] = dp[i - 1][0] + prices[i];
        dp[i][2] = max(dp[i - 1][1], max(dp[i - 1][2], dp[i - 1][3]));
        dp[i][3] = dp[i - 1][1];
    }

    return max(dp[prices.size() - 1][1], max(dp[prices.size() - 1][2], dp[prices.size() - 1][3]));
}

//714
int maxProfit(vector<int> &prices, int fee) {
    vector<vector<int> > dp(prices.size(), vector<int>(2));
    dp[0][0] = -prices[0];
    for (int i = 1; i < prices.size(); ++i) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
    }
    return dp[prices.size() - 1][1];
}

//674
int findLengthOfLCIS(vector<int> &nums) {
    vector<int> dp(nums.size(), 1);
    int ans = 0;
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] > nums[i - 1])dp[i] = max(dp[i], dp[i - 1] + 1);
        ans = max(ans, dp[i]);
    }
    return ans;
}

//718
int findLength(vector<int> &nums1, vector<int> &nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    vector<vector<int> > dp(n1, vector<int>(n2));
    int ans = 0;

    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            if (nums1[i] == nums2[j]) {
                if (i > 0 && j > 0)dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = 1;
            }
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}

//1143
int longestCommonSubsequence(string text1, string text2) {
    int n1 = text1.size();
    int n2 = text2.size();

    vector<vector<int> > dp(n1, vector<int>(n2));

    for (int i = 0; i < n1; ++i) {
        if (text1[i] == text2[0]) {
            for (int k = i; k < n1; ++k)dp[k][0] = 1;
            break;
        }
    }

    for (int j = 0; j < n2; ++j) {
        if (text2[j] == text1[0]) {
            for (int k = j; k < n2; ++k)dp[0][k] = 1;
            break;
        }
    }

    for (int i = 1; i < n1; ++i) {
        for (int j = 1; j < n2; ++j) {
            if (text1[i] == text2[j])dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n1 - 1][n2 - 1];
}

//1035
int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    int ans = 0;
    vector<vector<int> > dp(n1, vector<int>(n2));
    vector<vector<int> > findmax(n1, vector<int>(n2));
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            if (i > 0 && j > 0)
                findmax[i][j] = max(dp[i - 1][j - 1], max(findmax[i][j - 1], findmax[i - 1][j]));
            if (nums1[i] == nums2[j]) {
                dp[i][j] = findmax[i][j] + 1;
                ans = max(ans, dp[i][j]);
            }
        }
    }
    return ans;
}

//53
int maxSubArray(vector<int> &nums) {
    int ans = 0;
    vector<int> dp(nums.size());
    dp[0] = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        dp[i] = max(dp[i - 1] + nums[i], nums[i]);
        ans = max(dp[i], ans);
    }
    return ans;
}

//115
int numDistinct(string s, string t) {
    int n1 = s.size();
    int n2 = t.size();
    vector<vector<ull> > dp(n1, vector<ull>(n2));

    ull cnt = 0;

    for (int i = 0; i < n1; ++i) {
        if (s[i] == t[0])dp[i][0] = ++cnt;
        else dp[i][0] = cnt;
    }

    for (int i = 1; i < n1; ++i) {
        for (int j = 1; j < n2; ++j) {
            if (s[i] == t[j])dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            else dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n1 - 1][n2 - 1];
}

//583
int minDistance_(string word1, string word2) {
    int n1 = word1.size();
    int n2 = word2.size();
    vector<vector<int> > dp(n1, vector<int>(n2,INT_MAX));
    bool check = false;
    for (int i = 0; i < n1; ++i) {
        if (word1[i] == word2[0])check = true;
        if (check)dp[i][0] = i;
        else dp[i][0] = i + 2;
    }
    check = false;
    for (int j = 0; j < n2; ++j) {
        if (word1[0] == word2[j])check = true;
        if (check)dp[0][j] = j;
        else dp[0][j] = j + 2;
    }

    for (int i = 1; i < n1; ++i) {
        for (int j = 1; j < n2; ++j) {
            if (word1[i] == word2[j])dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
            else dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
        }
    }

    return dp[n1 - 1][n2 - 1];
}

//72
int minDistance(string word1, string word2) {
    int n1 = word1.size();
    int n2 = word2.size();
    if (n1 == 0)return n2;
    if (n2 == 0)return n1;
    vector<vector<int> > dp(n1, vector<int>(n2,INT_MAX));
    bool c = false;
    for (int i = 0; i < n1; ++i) {
        if (word1[i] == word2[0])c = true;
        if (c)dp[i][0] = i;
        else dp[i][0] = i + 1;
    }
    c = false;
    for (int j = 0; j < n2; ++j) {
        if (word1[0] == word2[j])c = true;
        if (c)dp[0][j] = j;
        else dp[0][j] = j + 1;
    }

    for (int i = 1; i < n1; ++i) {
        for (int j = 1; j < n2; ++j) {
            int del_dis = dp[i - 1][j] + 1;
            int insert_dis = dp[i][j - 1] + 1;
            int eq = word1[i] == word2[j] ? 0 : 1;
            int subti_dis = dp[i - 1][j - 1] + eq;
            dp[i][j] = min(del_dis, min(insert_dis, subti_dis));
        }
    }
    return dp[n1 - 1][n2 - 1];
}

//647
int countSubstrings(string s) {
    int n = s.size();
    vector<vector<bool> > dp(n, vector<bool>(n));
    int cnt = 0;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i; j < n; ++j) {
            if (s[i] == s[j] && (i + 1 > j - 1 || dp[i + 1][j - 1])) {
                dp[i][j] = true;
                cnt++;
            }
        }
    }
    return cnt;
}

//516
int longestPalindromeSubseq(string s) {
    int n = s.size();
    vector<vector<int>> dp(n,vector<int>(n));
    int ans = 0;
    for (int i = 0;i<n;++i)dp[i][i] = 1;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
                ans = max(ans,dp[i][j]);
            }else {
                dp[i][j] = max(dp[i + 1][j],dp[i][j - 1]);
            }
        }
    }
    return ans;
}

int main() {
    string s1 = "aabb";
    string s2 = "ab";
    int l = numDistinct(s1, s2);

    return 0;
}
