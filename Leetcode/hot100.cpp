#include "../quick.h"

// 1
vector<int> twoSum(vector<int>& nums, int target) {
  unordered_map<int, int> ump;
  for (int i = 0; i < nums.size(); ++i) {
    if (ump.find(target - nums[i]) != ump.end()) {
      return vector<int>{i, ump[target - nums[i]]};
    }
    ump[nums[i]] = i;
  }
  return vector<int>{};
}

// 49
vector<vector<string>> groupAnagrams(vector<string>& strs) {
  int n = strs.size();
  vector<string> cp(strs.begin(), strs.end());
  vector<vector<string>> ans;
  for (int i = 0; i < n; ++i) {
    sort(cp[i].begin(), cp[i].end());
  }
  unordered_map<string, int> ump;
  for (int i = 0; i < n; ++i) {
    if (ump.find(cp[i]) != ump.end()) {
      ans[ump[cp[i]]].push_back(strs[i]);
    } else {
      ump[cp[i]] = ans.size();
      ans.push_back({strs[i]});
    }
  }
  return ans;
}

// 128
// 通过hashset去重并查找前一个元素，确定每个连续序列的开始，对每个开头向后查找，确定长度
int longestConsecutive(vector<int>& nums) {
  unordered_set<int> st;
  for (int i = 0; i < nums.size(); ++i) {
    st.insert(nums[i]);
  }

  int ans = 0;
  for (auto it = st.begin(); it != st.end(); ++it) {
    if (st.contains(*it - 1)) continue;
    int len = 1;
    int start = *it;
    while (st.contains(start + 1)) {
      len++;
      start++;
    }
    ans = max(len, ans);
  }
  return ans;
}

// 283
void moveZeroes(vector<int>& nums) {
  int low = 0;
  int n = nums.size();
  for (int i = 0; i < n; ++i) {
    if (nums[i] != 0) {
      nums[low] = nums[i];
      low++;
    }
  }
  while (low < n) nums[low++] = 0;
  return;
}

// 11
int maxArea(vector<int>& height) {
  int l = 0;
  int r = height.size() - 1;
  int ans = 0;
  while (r - l > 0) {
    ans = max(ans, (r - l) * min(height[l], height[r]));
    if (height[l] < height[r]) {
      l++;
    } else {
      r--;
    }
  }
  return ans;
}

// 15
// 为了确定不重复的答案，用三个数的大小关系保证，a < b < c &&
// nums[a]<=nums[b]<=nums[c]
// 检索答案时确保每个位置的数和上一次不一样，保证唯一答案
// a确定时，bc使用双指针寻找，根据nums[a]+nums[b]+nums[c]和0的大小关系，唯一确定指针移动方向
// 只要步骤中设计修改下标，那么就一定要注意检查合理下标范围
vector<vector<int>> threeSum(vector<int>& nums) {
  sort(nums.begin(), nums.end());
  vector<vector<int>> ans;
  int n = nums.size();
  for (int a = 0; a <= n - 3; ++a) {
    if (a != 0 && nums[a] == nums[a - 1]) continue;
    int b = a + 1;
    int c = n - 1;
    while (b < c) {
      if (nums[a] + nums[b] + nums[c] > 0) {
        c--;
        while (b < c && nums[c] == nums[c + 1]) c--;
      } else if (nums[a] + nums[b] + nums[c] < 0) {
        b++;
        while (b < c && nums[b] == nums[b - 1]) b++;
      } else {
        ans.push_back({nums[a], nums[b], nums[c]});
        b++;
        while (b < c && nums[b] == nums[b - 1]) b++;
      }
    }
  }
  return ans;
}

// 42
int trap(vector<int>& height) {
  int n = height.size();
  // 每个位置雨水的高度是左右两侧最高高度的较小值
  // 使用动态规划预处理获得每个位置的高度
  vector<int> maxleft(n);
  vector<int> maxright(n);
  maxleft[0] = 0;
  maxright[n - 1];
  for (int i = 1; i < n; ++i) {
    maxleft[i] = max(maxleft[i - 1], height[i - 1]);
  }
  for (int i = n - 2; i >= 0; --i) {
    maxright[i] = max(maxright[i + 1], height[i + 1]);
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int val = min(maxleft[i], maxright[i]);
    if (val > height[i]) {
      ans += val - height[i];
    }
  }
  return ans;
}

// 3
// 子串问题可以用滑动窗口判定，当不符合条件时调整左端
// 用hashmap维护信息
int lengthOfLongestSubstring(string s) {
  int n = s.size();
  int ans = 0;
  unordered_map<char, int> ump;
  int left = 0;

  for (int right = 0; right < n; ++right) {
    if (!ump.contains(s[right])) {
      ans = max(right - left + 1, ans);
    } else {
      int t = ump[s[right]] + 1;
      while (left < t) {
        ump.erase(s[left]);
        ++left;
      }
    }
    ump[s[right]] = right;
  }
  return ans;
}

// 438
vector<int> findAnagrams(string s, string p) {
  int n = s.size();
  int l = p.size();
  vector<int> ans;
  if (n < l) return ans;
  vector<int> now(26);
  vector<int> target(26);
  for (int i = 0; i < l; ++i) {
    target[p[i] - 'a']++;
  }
  for (int i = 0; i < l; ++i) {
    now[s[i] - 'a']++;
    if (now == target) ans.push_back(0);
  }
  for (int i = l; i < n; ++i) {
    now[s[i - l] - 'a']--;
    now[s[i] - 'a']++;
    if (now == target) ans.push_back(i - l + 1);
  }
  return ans;
}

// 239
// O(nlogn)use a heap to maintain the max_val of window and delete the element
// in a delay way O(n)use monotonic queue
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
  monotonic_queue mq;
  vector<int> ans;
  for (int i = 0; i < k; ++i) {
    mq.push_idx(i, nums);
  }
  ans.push_back(nums[mq.get_max()]);
  for (int i = 1; i <= nums.size() - k; ++i) {
    mq.push_idx(i + k - 1, nums);
    mq.pop_idx(i - 1);
    ans.push_back(nums[mq.get_max()]);
  }
  return ans;
}

// 76
// use double pointer(slide window) to keep min window
// use set.empty() to check the coverage of t in O(1)
string minWindow(string s, string t) {
  unordered_map<char, int> check;
  unordered_set<char> st;
  for (char c : t) {
    check[c]++;
    st.insert(c);
  }
  unordered_map<char, int> now;
  int l = 0;
  int r = 0;
  int minlen = INT_MAX;
  int minl = 0, minr = 0;

  for (; r < s.size(); ++r) {
    now[s[r]]++;
    if (now[s[r]] >= check[s[r]] && st.contains(s[r])) st.erase(s[r]);
    if (!st.empty()) continue;
    while (st.empty()) {
      if (r - l + 1 < minlen) {
        minlen = r - l + 1;
        minl = l;
        minr = r;
      }
      now[s[l]]--;
      if (now[s[l]] < check[s[l]]) st.insert(s[l]);
      l++;
    }
  }
  if (minlen == INT_MAX) return "";
  string ans;
  for (int i = minl; i <= minr; ++i) ans += s[i];
  return ans;
}

// 56
// sort first in intervals question
struct cmp {
  bool operator()(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
  }
};

vector<vector<int>> merge(vector<vector<int>>& intervals) {
  sort(intervals.begin(), intervals.end(), cmp());
  vector<vector<int>> ans;
  ans.push_back(intervals[0]);
  for (int i = 1; i < intervals.size(); ++i) {
    if (intervals[i][0] <= ans.back()[1] && intervals[i][1] > ans.back()[1]) {
      ans.back()[1] = intervals[i][1];
    } else if (intervals[i][0] > ans.back()[1]) {
      ans.push_back(intervals[i]);
    }
  }
  return ans;
}

// 189
// use mod in rotate array
void rotate(vector<int>& nums, int k) {
  int n = nums.size();
  k %= n;
  vector<int> copy(nums.begin(), nums.end());
  for (int i = 0; i < n; ++i) {
    nums[(i + k) % n] = copy[i];
  }
}

// 238
// dont use / since exit 0
// memory left and right product of each element
vector<int> productExceptSelf(vector<int>& nums) {
  int n = nums.size();
  vector<int> left(n, 1);
  vector<int> right(n, 1);
  for (int i = 1; i < n; ++i) {
    left[i] = left[i - 1] * nums[i - 1];
  }

  for (int i = n - 2; i >= 0; --i) {
    right[i] = right[i + 1] * nums[i + 1];
  }

  vector<int> ans(n);
  for (int i = 0; i < n; ++i) {
    ans[i] = left[i] * right[i];
  }
  return ans;
}

// 41
int firstMissingPositive(vector<int>& nums) {
  unordered_set<int> st;
  for (int x : nums) {
    st.insert(x);
  }
  for (int i = 1; i <= nums.size() + 1; ++i) {
    if (!st.contains(i)) return i;
  }
  return 0;
}

// 73
void setZeroes(vector<vector<int>>& matrix) {
  unordered_set<int> s, t;
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[0].size(); ++j) {
      if (matrix[i][j] == 0) {
        s.insert(i);
        t.insert(j);
      }
    }
  }

  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[0].size(); ++j) {
      if (s.contains(i) || t.contains(j)) matrix[i][j] = 0;
    }
  }
}

// 54
void compute_next(int nowx, int nowy, int& tempx, int& tempy, int dir) {
  tempx = nowx;
  tempy = nowy;
  switch (dir) {
    case 0:
      tempy++;
      break;
    case 1:
      tempx++;
      break;
    case 2:
      tempy--;
      break;
    case 3:
      tempx--;
      break;
  }
}

vector<int> spiralOrder(vector<vector<int>>& matrix) {
  int row = matrix.size();
  int col = matrix[0].size();
  vector<int> ans;
  vector<vector<bool>> m(row, vector<bool>(col, true));
  int dir = 0;
  int nowx = 0, nowy = 0;
  int res = row * col;

  while (res) {
    res--;
    ans.emplace_back(matrix[nowx][nowy]);
    m[nowx][nowy] = false;
    // compute next position
    int tempx = nowx, tempy = nowy;
    compute_next(nowx, nowy, tempx, tempy, dir);
    if (!(tempx < row && tempx >= 0 && tempy < col && tempy >= 0 &&
          m[tempx][tempy])) {
      dir = (++dir) % 4;
      compute_next(nowx, nowy, tempx, tempy, dir);
    }
    nowx = tempx;
    nowy = tempy;
  }
  return ans;
}

// 48
void rotate(vector<vector<int>>& matrix) {
  int n = matrix.size();
  for (int i = 0; i < n / 2; ++i) {
    // martrix[i][i]
    for (int j = 0; j < n - i * 2 - 1; ++j) {
      // martrix[i][i + j]
      int x = i, y = i + j;
      int temp = matrix[x][y];
      int times = 4;
      while (times--) {
        int newx = y, newy = n - x - 1;
        int t = matrix[newx][newy];
        matrix[newx][newy] = temp;
        temp = t;
        x = newx;
        y = newy;
      }
    }
  }
}

// 240
bool searchMatrix(vector<vector<int>>& matrix, int target) {
  int n = matrix.size(), m = matrix[0].size();
  int x = 0, y = m - 1;
  while (x >= 0 && x < n && y >= 0 && y < m) {
    if (target > matrix[x][y])
      ++x;
    else if (target < matrix[x][y])
      --y;
    else
      return true;
  }
  return false;
}

// 160
// 通过长度差对齐起点，利用双指针同步遍历寻找交点。
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
  int n1 = 0, n2 = 0;
  auto temp = headA;
  while (temp) {
    n1++;
    temp = temp->next;
  }
  temp = headB;
  while (temp) {
    n2++;
    temp = temp->next;
  }
  auto pa = headA;
  auto pb = headB;
  ListNode*& c = n1 > n2 ? pa : pb;
  int step = abs(n1 - n2);
  while (step--) {
    c = c->next;
  }
  while (pa != pb) {
    pa = pa->next;
    pb = pb->next;
  }
  return pa;
}

int main() {
  vector<vector<int>> m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  auto res = spiralOrder(m);
  return 0;
}
