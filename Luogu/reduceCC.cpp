#include "../quick.h"

int maxn = 10005;
vector<int> dfn(maxn, -1);
vector<int> low(maxn);
int cnt = 0;
vector<bool> instack(maxn, false);
vector<vector<int> > g(maxn);
stack<int> st;
vector<int> w(maxn);
vector<vector<int> > scc;
vector<vector<int> > g2;
vector<pair<int, int> > edges;
vector<int> W;
vector<int>scc_id(maxn);
int scc_cnt = 0;

void tarjan(int u) {
    st.push(u);
    instack[u] = true;
    dfn[u] = low[u] = ++cnt;
    for (const auto &v: g[u]) {
        if (dfn[v] < 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }


    if (low[u] == dfn[u]) {
        vector<int> t;
        while (true) {
            int k = st.top();
            scc_id[k] = scc_cnt;
            t.push_back(k);
            st.pop();
            instack[k] = false;
            if (k == u)break;
        }
        scc.push_back(t);
        scc_cnt++;
    }
}


void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        edges.push_back({u, v});
    }

    for (int i = 1; i <= n; ++i) {
        if (dfn[i] < 0)tarjan(i);
    }


    W.resize(scc_cnt);
    for (int i =0;i<scc.size();++i) {
        int newW = 0;
        for (auto &x: scc[i]) {
            newW += w[x];
        }
       W[i] = newW;
    }



    g2.resize(scc_cnt);
    vector<int> in(scc_cnt);
    for (const auto &e: edges) {
        int u = e.first;
        int v = e.second;
        u = scc_id[u];
        v = scc_id[v];
        if (u != v) {
            bool check  = true;
            for (const auto& to:g2[u]) {
                if (to == v) {
                    check = false;
                    break;
                }
            }
            if (!check)continue;
            g2[u].push_back(v);
            in[v]++;
        }
    }

    queue<int> q;
    vector<int> toposort;
    for (int i = 0; i < scc_cnt; ++i) {
        if (in[i] == 0)q.push(i);
    }

    while (!q.empty()) {
        int id = q.front();
        q.pop();
        toposort.push_back(id);
        for (const auto &v: g2[id]) {
            in[v]--;
            if (in[v] == 0)q.push(v);
        }
    }


    vector<int> dp(W.begin(), W.end());
    int ans  = dp[0];
    for (const auto &id: toposort) {
        for (const auto &v: g2[id]) {
            dp[v] = max(dp[v], dp[id] + W[v]);
            ans = max(ans,dp[v]);
        }
    }

    cout << ans;
}

int main() {
    solve();
    return 0;
}
