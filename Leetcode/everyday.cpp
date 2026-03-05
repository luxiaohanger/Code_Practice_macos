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
    return min(cnt1,cnt2);
}
