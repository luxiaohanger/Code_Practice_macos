#include "../quick.h"

vector<int> dfn(10005,-1);
vector<int> low(10005);
int cnt = 0;
stack<int> st;
vector<bool> in_stack(10005,false);
vector<vector<int>> g(10005);
vector<vector<int>> ans;


void dfs(int u) {
    dfn[u] = low[u] = ++cnt;
    st.push(u);
    in_stack[u] = true;

    for (auto v:g[u]) {
        if (dfn[v] < 0) {
            dfs(v);
            low[u] = min(low[u],low[v]);
        }
        if (in_stack[v]) {
            low[u] = min(low[u],dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        vector<int> t;
        while (st.top() != u) {
            t.push_back(st.top());
            in_stack[st.top()] = false;
            st.pop();
        }
        t.push_back(st.top());
        in_stack[st.top()] = false;
        st.pop();
        sort(t.begin(), t.end());
        ans.push_back(t);
    }
}


//强连通分量
void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 0;i<m;++i) {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    for (int i = 1;i<=n;++i) {
        if (dfn[i] < 0)dfs(i);
    }

    sort(ans.begin(), ans.end(),[](auto& a,auto& b){return a[0]<b[0];});
    cout << ans.size() << '\n';
    for (auto& arr:ans) {
        for (auto& x:arr)cout << x << ' ';
        cout << '\n';
    }
}

int main() {

    solve();

    return 0;
}