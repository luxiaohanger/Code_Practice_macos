#pragma once

// 核心容器
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <list>
#include <array>

// 算法
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <complex>
#include <random>

// IO和工具
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>

// 常用别名
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;


struct DSU {
    int n;
    vector<int> pa;
    vector<int> sz;

    DSU(int x) : n(x), pa(x + 1), sz(x + 1, 1) {
        for (int i = 0; i <= n; ++i) {
            pa[i] = i;
        }
    }

    int find(int x) {
        return x == pa[x] ? x : pa[x] = find(pa[x]);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)return;
        if (sz[x] < sz[y])swap(x, y);
        pa[y] = x;
        sz[x] += sz[y];
    }
};


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
    }
};

struct monotonic_queue {
    deque<int> dq;

    void push_val(int val) {
        while (!dq.empty() && dq.back() < val) {
            dq.pop_back();
        }
        dq.push_back(val);
    }

    void pop_val(int val) {
        if (!dq.empty() && dq.front() == val)dq.pop_front();
    }

    void push_idx(int idx, const vector<int> &arr) {
        while (!dq.empty() && arr[dq.back()] < arr[idx]) {
            dq.pop_back();
        }
        dq.push_back(idx);
    }

    void pop_idx(int idx) {
        if (!dq.empty() && dq.front() == idx) {
            dq.pop_front();
        }
    }

    int get_max() {
        if (!dq.empty())
            return dq.front();
        return -1;
    }
};














