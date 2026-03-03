#include "../quick.h"

int maxn = 500005;

vector<vector<int>> g(maxn);
vector<int> dfn(maxn,-1);
vector<int> low(maxn);
vector<vector<int>> bccs;
int cnt = 0;
stack<int> st;

void tarjan(int u,int pa) {
    dfn[u] = low[u] = ++cnt;
    st.push(u);

    if (pa == u && g[u].empty()) {
        bccs.push_back({u});
        return;
    }

    for (const auto& v:g[u]) {
        if (v == pa)continue;
        if (dfn[v] < 0) {
            tarjan(v,u);
            if (low[v] >= dfn[u]) {
                //栈顶直到v是一个点双
               vector<int> temp;
                while (true) {
                    int t = st.top();
                    temp.push_back(t);
                    st.pop();
                    if (t == v)break;
                }
                temp.push_back(u);
                bccs.push_back(temp);
            }
            low[u] = min(low[u],low[v]);
        }else {
            low[u] = min(low[u],dfn[v]);
        }
    }
}




void solve() {
    int n,m;
    cin >> n >> m;
    for (int i=0;i<m;++i) {
        int u,v;
        cin >> u >> v;
        if (u != v) {
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }


    for (int i = 1;i<=n;++i) {
        if (dfn[i] < 0)tarjan(i,i);
    }

    cout << bccs.size() << '\n';
    for (auto& arr:bccs) {
        cout << arr.size() << ' ';
        for (int& x : arr)cout << x << ' ';
        cout << '\n';
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}