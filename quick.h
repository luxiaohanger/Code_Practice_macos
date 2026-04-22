#pragma once

// 核心容器
#include <array>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// 算法
#include <algorithm>
#include <cmath>
#include <complex>
#include <functional>
#include <numeric>
#include <random>

// IO和工具
#include <atomic>
#include <chrono>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

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

  int find(int x) { return x == pa[x] ? x : pa[x] = find(pa[x]); }

  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    pa[y] = x;
    sz[x] += sz[y];
  }
};

// Definition for a binary tree/list node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode() : val(0), left(nullptr), right(nullptr) {}

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

ListNode* vectorToList(vector<int> v) {
  ListNode* pre;
  ListNode* head;
  for (int i = 0; i < v.size(); ++i) {
    ListNode* node = new ListNode(v[i]);
    if (i == 0) {
      pre = node;
      head = node;
    } else
      pre->next = node;
    pre = node;
  }
  return head;
}

void deleteList(ListNode* head) {
  ListNode* t = head;
  while (t) {
    ListNode* next = t->next;
    delete t;
    t = next;
  }
}

struct monotonic_queue {
  deque<int> dq;

  void push_val(int val) {
    while (!dq.empty() && dq.back() < val) {
      dq.pop_back();
    }
    dq.push_back(val);
  }

  void pop_val(int val) {
    if (!dq.empty() && dq.front() == val) dq.pop_front();
  }

  void push_idx(int idx, const vector<int>& arr) {
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
    if (!dq.empty()) return dq.front();
    return -1;
  }
};
