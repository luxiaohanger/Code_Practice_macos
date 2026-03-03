#include "../quick.h"

int maxn = 500005;

int cnt = 0;
vector<int> dfn(maxn,-1);
vector<int> low(maxn,-1);
vector<vector<int>> ans;
vector<vector<pii>> g(maxn);
vector<bool> isbridge(2000005,false);
vector<bool> vis(maxn,false);


void tarjan(int u,int edge) {
    dfn[u] = low[u] = ++cnt;
    for (auto x:g[u]) {
        int v = x.first;
        int eidx = x.second;
        if (eidx == edge)continue;
        if (dfn[v] < 0) {
            tarjan(v,eidx);
            if (low[v] > dfn[u]) {
                isbridge[eidx] = true;
            }
            low[u] = min(low[u],low[v]);
        }else {
            //回边 或 前向边
            low[u] = min(low[u],dfn[v]);
        }
    }
}

void dfs(int u,vector<int>& ebcc) {
    ebcc.push_back(u);
    vis[u] = true;
    for (auto x:g[u]) {
        int v = x.first;
        int eidx = x.second;
        if (isbridge[eidx] || vis[v])continue;
        dfs(v,ebcc);
    }
}

void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 0;i<m;++i) {
        int u,v;
        cin >> u >> v;
        g[u].push_back({v,i});
        g[v].push_back({u,i});
    }

    for (int i = 1;i<=n;++i) {
        if (dfn[i] < 0)tarjan(i,-1);
    }

    for (int i = 1;i<=n;++i) {
        if (!vis[i]) {
            vector<int> ebcc;
            dfs(i,ebcc);
            ans.push_back(ebcc);
        }
    }

    cout << ans.size() << '\n';
    for (auto& arr:ans) {
        cout << arr.size() << ' ';
        for (auto& x:arr) {
            cout << x << ' ';
        }
        cout << '\n';
    }


}
int main() {
    solve();
    return 0;
}