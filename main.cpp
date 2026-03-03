#include "quick.h"


void solve() {
    int limit, n;
    cin >> limit >> n;
    vector<int> val(n), w(n), num(n);
    vector<int> V, W;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> val[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < num[i]; ++j) {
            V.push_back(val[i]);
            W.push_back(w[i]);
        }
    }

    vector<int> dp(limit + 1);
    for (int i = 0; i < V.size(); ++i) {
        for (int j = limit; j >= W[i]; --j) {
            dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
        }
    }

    cout << dp[limit] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
