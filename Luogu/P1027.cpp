#include "../quick.h"

using pdi = pair<double,int>;
struct vertix {
    int vid;
    double x;
    double y;
    int cityid;
};

double dist(vertix a,vertix b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

void findFourthPoint(double x1, double y1, double x2, double y2, double x3, double y3, double& x4, double& y4) {
    double d12 = pow(x1 - x2, 2) + pow(y1 - y2, 2);
    double d13 = pow(x1 - x3, 2) + pow(y1 - y3, 2);
    double d23 = pow(x2 - x3, 2) + pow(y2 - y3, 2);

    if (d12 >= d13 && d12 >= d23) {
        // 点1和点2是对角点
        x4 = x1 + x2 - x3;
        y4 = y1 + y2 - y3;
    } else if (d13 >= d12 && d13 >= d23) {
        // 点1和点3是对角点
        x4 = x1 + x3 - x2;
        y4 = y1 + y3 - y2;
    } else {
        // 点2和点3是对角点
        x4 = x2 + x3 - x1;
        y4 = y2 + y3 - y1;
    }
}

struct cmp {
    bool operator()(pdi a,pdi b){
        return a.first > b.first;
    }
};
void solve() {
    int S,t,A,B;
    cin >> S >> t >> A >> B;
    vector<int> citycost(S + 1);
    vector<vertix> V;
    vector<int> source(4);
    vector<int> target(4);

    int cnt_v = 0;
    for (int i = 1;i<=S;++i) {
        double x1,x2,x3,x4,y1,y2,y3,y4;

        cin >> x1 >> y1 >> x2 >> y2
        >> x3 >> y3 >> citycost[i];

        findFourthPoint(x1,y1,x2,y2,x3,y3,x4,y4);

        if (i == A) {
            source[0] = cnt_v;
            source[1] = cnt_v + 1;
            source[2] = cnt_v + 2;
            source[3] = cnt_v + 3;
        }

        if (i == B) {
            target[0] = cnt_v;
            target[1] = cnt_v + 1;
            target[2] = cnt_v + 2;
            target[3] = cnt_v + 3;
        }


        V.push_back({cnt_v++,x1,y1,i});
        V.push_back({cnt_v++,x2,y2,i});
        V.push_back({cnt_v++,x3,y3,i});
        V.push_back({cnt_v++,x4,y4,i});
    }


    vector<vector<pdi>> g(cnt_v);

    for (int i =0;i<cnt_v;++i) {
        for (int j = i + 1;j<cnt_v;++j) {
            double d  = dist(V[i],V[j]);
            double cost = 0;
            if (V[i].cityid == V[j].cityid) {
                cost = d * citycost[V[i].cityid];
            }else {
                cost = d * t;
            }
            g[i].push_back({cost,j});
            g[j].push_back({cost,i});
        }
    }

    double inf = numeric_limits<double>::max();
    double ans = inf;
    for (int i =0;i<4;++i) {

        int s = source[i];
        vector<double> dis(cnt_v,inf);
        dis[s] = 0;
        priority_queue<pdi,vector<pdi>,cmp> pq;

        for (int i = 0;i<cnt_v;++i)pq.push({dis[i],i});

        while (!pq.empty()) {
            double d = pq.top().first;
            int id = pq.top().second;
            pq.pop();
            if (dis[id] != d)continue;
            for (const auto& e : g[id]) {
                double cost = e.first;
                int v = e.second;
                if (dis[id] != inf && dis[id] + cost < dis[v]) {
                    dis[v] = dis[id] + cost;
                    pq.push({dis[v],v});
                }
            }
        }

        for (int k=0;k<4;++k) {
            ans = min(ans,dis[target[k]]);
        }

    }

    cout << fixed << setprecision(1) << ans << '\n';

}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}