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
    int ls = (int) pow(2,n-1) - 1;
    if (k == (l + 1) / 2)return '1';
    if (k < (l + 1) / 2)return findKthBit(n - 1, k);
    return findKthBit(n - 1, ls - k + (l + 1) / 2 + 1) == '0' ? '1' : '0';
}
