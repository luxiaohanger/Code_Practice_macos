#include "../quick.h"

//1536
int minSwaps(vector<vector<int> > &grid) {
    int n = grid.size();
    vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
        for (int j = n - 1; j > 0; --j) {
            if (grid[i][j] == 0)cnt[i]++;
            else break;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int bar = n - i - 1;
        if (cnt[i] < bar) {
            for (int j = i + 1; j < n; ++j) {
                if (cnt[j] >= bar) {
                    for (int k = j; k > i; --k) {
                        swap(cnt[k], cnt[k - 1]);
                        ans++;
                    }
                    break;
                }
            }
            if (cnt[i] < bar)return -1;
        }
    }
    return ans;
}

//1545
char findKthBit(int n, int k) {
    if (n == 1)return '0';
    int l = (int) pow(2, n) - 1;
    int ls = (int) pow(2, n - 1) - 1;
    if (k == (l + 1) / 2)return '1';
    if (k < (l + 1) / 2)return findKthBit(n - 1, k);
    return findKthBit(n - 1, ls - k + (l + 1) / 2 + 1) == '0' ? '1' : '0';
}

//1582
int numSpecial(vector<vector<int> > &mat) {
    int n = mat.size();
    int m = mat[0].size();
    vector<int> cnt1(n);
    vector<int> cnt2(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mat[i][j] == 1) {
                cnt1[i]++;
                cnt2[j]++;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mat[i][j] == 1 && cnt1[i] == 1 && cnt2[j] == 1) {
                res++;
            }
        }
    }
    return res;
}

//1758
int minOperations(string s) {
    int n = s.size();
    int cnt1 = 0;
    int cnt2 = 0;
    int c1 = 1;
    int c2 = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] - '0' == c1)cnt1++;
        c1 = c1 == 0 ? 1 : 0;
        if (s[i] - '0' == c2)cnt2++;
        c2 = c2 == 0 ? 1 : 0;
    }
    return min(cnt1, cnt2);
}

//3212
int numberOfSubmatrices(vector<vector<char> > &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<pii> > dp(n, vector<pii>(m));
    if (grid[0][0] == 'X')dp[0][0] = {1, 0};
    else if (grid[0][0] == 'Y')dp[0][0] = {0, 1};
    else dp[0][0] = {0, 0};

    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i - 1][0];
        if (grid[i][0] == 'X')dp[i][0].first++;
        else if (grid[i][0] == 'Y')dp[i][0].second++;
    }

    for (int j = 1; j < m; ++j) {
        dp[0][j] = dp[0][j - 1];
        if (grid[0][j] == 'X')dp[0][j].first++;
        else if (grid[0][j] == 'Y')dp[0][j].second++;
    }


    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dp[i][j].first = dp[i][j - 1].first + dp[i - 1][j].first - dp[i - 1][j - 1].first;
            dp[i][j].second = dp[i][j - 1].second + dp[i - 1][j].second - dp[i - 1][j - 1].second;
            if (grid[i][j] == 'X')dp[i][j].first++;
            else if (grid[i][j] == 'Y')dp[i][j].second++;
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dp[i][j].first == dp[i][j].second && dp[i][j].first != 0)cnt++;
        }
    }
    return cnt;
}

//2906
vector<vector<int> > constructProductMatrix(vector<vector<int> > &grid) {
    int m = grid[0].size();
    int n = grid.size();
    vector<int> prefix(m * n);
    prefix[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == n - 1 && j == m - 1)break;
            prefix[i * m + j + 1] = (prefix[i * m + j] * (grid[i][j] % 12345)) % 12345;
        }
    }

    vector<int> suffix(m * n);
    suffix[m * n - 1] = 1;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (i == 0 && j == 0)break;
            suffix[i * m + j - 1] = (suffix[i * m + j] * (grid[i][j] % 12345)) % 12345;
        }
    }

    vector<vector<int> > ans(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans[i][j] = (prefix[i * m + j] * suffix[i * m + j]) % 12345;
        }
    }
    return ans;
}

//3546
bool canPartitionGrid(vector<vector<int> > &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<ull> ans;
    ull sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            sum += grid[i][j];
        }
        ans.push_back(sum);
    }

    sum = 0;
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            sum += grid[i][j];
        }
        ans.push_back(sum);
    }

    if (sum % 2 == 1)return false;
    sum /= 2;
    for (const auto &x: ans) {
        if (x == sum)return true;
    }
    return false;
}

//2839
bool canBeEqual(string s1, string s2) {
    bool t1 = s1[0] == s2[0] && s1[2] == s2[2];
    bool t2 = s1[0] == s2[2] && s1[2] == s2[0];
    bool t3 = s1[1] == s2[1] && s1[3] == s2[3];
    bool t4 = s1[1] == s2[3] && s1[3] == s2[1];
    return (t1 || t2) && (t3 || t4);
}

//560
int subarraySum(vector<int> &nums, int k) {
    int n = nums.size();
    vector<int> prefix(n);
    prefix[0] = nums[0];
    for (int i = 1; i < n; ++i) {
        prefix[i] = nums[i] + prefix[i - 1];
    }

    int ans = 0;
    unordered_map<int,int> umap;
    for (int i = 0;i<n;++i) {
        if (prefix[i] == k)ans++;
        if (umap.find(prefix[i] - k) != umap.end())ans += umap[prefix[i] - k];
        umap[prefix[i]]++;
    }
    return ans;
}
