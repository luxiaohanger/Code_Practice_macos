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
        if (intervals[i][0] <= ans.back()[1] &&
            intervals[i][1] > ans.back()[1]) {
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

// 206
// 用三个指针分别指向pre now next
// space O(1)
ListNode* reverseList(ListNode* head) {
    if (!head) return nullptr;
    ListNode* pre = head;
    ListNode* now = head->next;
    head->next = nullptr;
    while (now) {
        ListNode* next = now->next;
        now->next = pre;
        pre = now;
        now = next;
    }
    return pre;
}

// 234
// 原地空间翻转链表
bool isPalindrome(ListNode* head) {
    if (!head) return true;
    int n = 0;
    ListNode* t = head;
    while (t) {
        ++n;
        t = t->next;
    }
    if (n == 1) return true;
    ListNode* a;
    ListNode* b;
    int sa, sb;
    if (n % 2 == 1) {
        sa = n / 2 - 1;
        sb = n / 2 + 1;
    } else {
        sa = n / 2 - 1;
        sb = n / 2;
    }
    t = head;
    int st = 0;
    while (true) {
        if (st == sa) a = t;
        if (st == sb) {
            b = t;
            break;
        }
        t = t->next;
        st++;
    }
    a->next = nullptr;
    // reverse a
    ListNode* pre = head;
    ListNode* now = head->next;
    head->next = nullptr;
    while (now) {
        ListNode* next = now->next;
        now->next = pre;
        pre = now;
        now = next;
    }
    while (a && b) {
        if (a->val != b->val) {
            return false;
        }
        a = a->next;
        b = b->next;
    }
    return true;
}

// 141
// 快慢指针判环
bool hasCycle(ListNode* head) {
    if (!head) return false;
    ListNode* quick = head;
    ListNode* slow = head;
    while (slow && quick && quick->next) {
        slow = slow->next;
        quick = quick->next->next;
        if (slow == quick) return true;
    }
    return false;
}

// 142
ListNode* detectCycle(ListNode* head) {
    if (!head || !head->next) return nullptr;
    ListNode* quick = head;
    ListNode* slow = head;
    while (slow && quick && quick->next) {
        slow = slow->next;
        quick = quick->next->next;
        if (slow == quick) break;
    }
    if (slow != quick) return nullptr;
    slow = head;
    while (slow != quick) {
        slow = slow->next;
        quick = quick->next;
    }
    return slow;
}

// 21
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (!list1) return list2;
    if (!list2) return list1;
    ListNode* head;
    ListNode* now;
    if (list1->val > list2->val) {
        now = list2;
        list2 = list2->next;
    } else {
        now = list1;
        list1 = list1->next;
    }
    head = now;
    while (list1 && list2) {
        if (list1->val > list2->val) {
            now->next = list2;
            now = list2;
            list2 = list2->next;
        } else {
            now->next = list1;
            now = list1;
            list1 = list1->next;
        }
    }
    if (list1)
        now->next = list1;
    else
        now->next = list2;
    return head;
}

// 2
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int carry = 0;
    ListNode* a = l1;
    ListNode* b = l2;
    ListNode* protect = new ListNode(0);
    ListNode* prev = protect;
    while (a || b) {
        ListNode* newnode = new ListNode(0);

        int temp = carry;
        if (a) {
            temp += a->val;
            a = a->next;
        }
        if (b) {
            temp += b->val;
            b = b->next;
        }

        if (temp >= 10) {
            temp %= 10;
            carry = 1;
        } else {
            carry = 0;
        }

        newnode->val = temp;
        prev->next = newnode;
        prev = newnode;
    }
    if (carry != 0) {
        ListNode* newnode = new ListNode(1);
        prev->next = newnode;
    }
    return protect->next;
}

// 19
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* protect = new ListNode(0);
    protect->next = head;
    // check len
    ListNode* t = head;
    int num = 0;
    while (t) {
        num++;
        t = t->next;
    }
    int step = num - n;
    ListNode* prev = protect;
    ListNode* now = head;
    while (step--) {
        prev = prev->next;
        now = now->next;
    }
    prev->next = now->next;
    return protect->next;
}

// 24
void swap_node(ListNode* prev, ListNode* first, ListNode* second,
               ListNode* after) {
    prev->next = second;
    second->next = first;
    first->next = after;
}
ListNode* swapPairs(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* protect = new ListNode(0);
    protect->next = head;
    ListNode* prev = protect;
    ListNode* first = head;
    ListNode* second = head->next;
    ListNode* after = head->next->next;
    while (first && second) {
        swap_node(prev, first, second, after);
        prev = prev->next->next;
        first = prev->next;
        if (first)
            second = first->next;
        else
            second = nullptr;
        if (second)
            after = second->next;
        else
            after = nullptr;
    }
    auto ans = protect->next;
    delete protect;
    return ans;
}

// 25
// 编写翻转函数，使用本组节点的保护节点和尾节点为参数
// 分组使用翻转函数，原地修改链表
ListNode* my_reverse(ListNode* prev, ListNode* last) {
    ListNode* end = last->next;
    last->next = nullptr;
    ListNode* begin = prev->next;
    ListNode* first = prev;
    ListNode* second = begin;
    while (first && second) {
        ListNode* temp = second->next;
        second->next = first;
        first = second;
        second = temp;
    }
    prev->next = last;
    begin->next = end;
    return begin;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    int n = 0;
    ListNode* t = head;
    while (t) {
        n++;
        t = t->next;
    }
    if (n < k) return head;
    int groups = n / k;
    ListNode* safe = new ListNode(0);
    safe->next = head;
    ListNode* prev = safe;
    while (groups--) {
        ListNode* last = prev;
        int step = k;
        while (step--) {
            last = last->next;
        }
        prev = my_reverse(prev, last);
    }

    auto ans = safe->next;
    delete safe;
    return ans;
}

// 138
// 任意类型的原始指针都以整数形式存储（因为是地址），可以直接hash
Node* copyRandomList(Node* head) {
    unordered_map<Node*, Node*> ump;
    int n = 0;
    Node* t = head;
    Node* prev = new Node(0);
    prev->next = head;
    Node* copy_prev = new Node(0);
    ump[prev] = copy_prev;
    while (t) {
        n++;
        Node* node = new Node(t->val);
        ump[t] = node;
        ump[prev]->next = node;
        t = t->next;
        prev = prev->next;
    }
    t = head;
    while (t) {
        if (t->random) {
            ump[t]->random = ump[t->random];
        }
        t = t->next;
    }
    return ump[head];
}

// 148
// merge sort
ListNode* sortList(ListNode* head) {
    if (!head) return head;
    // check len
    int n = 0;
    ListNode* t = head;
    while (t) {
        n++;
        t = t->next;
    }
    if (n == 1) return head;
    int len1 = n / 2;
    ListNode* l1 = head;
    ListNode* l2 = head;
    while (len1--) l2 = l2->next;
    t = head;
    while (t->next != l2) t = t->next;
    t->next = nullptr;
    l1 = sortList(l1);
    l2 = sortList(l2);
    return mergeTwoLists(l1, l2);
}

// 23
// 直接顺序的合并所有链表会导致先被合并的链表在接下来每次合并都被遍历
// 总遍历次数达到 k^2, 时间O(k^2 * n)
// 采用分治思想分组处理，每次都两两一组合并
// 遍历次数 klogk 时间O(nklogk)
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    int step = 1;
    while (step <= lists.size()) {
        step *= 2;
        for (int i = 0; i < lists.size(); i += step) {
            if (i + step / 2 < lists.size())
                lists[i] = mergeTwoLists(lists[i], lists[i + step / 2]);
        }
    }
    return lists[0];
}

// 146
class LRUCache {
   private:
    int capacity;
    int num;
    double_list* safe;
    unordered_map<int, double_list*> map;

    void move_node(double_list* now) {
        // move now to head
        now->prev->next = now->next;
        now->next->prev = now->prev;
        now->next = safe->next;
        now->prev = safe;
        safe->next->prev = now;
        safe->next = now;
    }

   public:
    LRUCache(int capacity) {
        safe = new double_list(0, 0);
        safe->next = safe;
        safe->prev = safe;
        this->capacity = capacity;
        this->num = 0;
    }

    int get(int key) {
        int res = -1;
        if (map.contains(key)) {
            res = map[key]->val;
            move_node(map[key]);
        }
        return res;
    }

    void put(int key, int value) {
        if (map.contains(key)) {
            map[key]->val = value;
            move_node(map[key]);
        } else {
            if (num < capacity) {
                num++;
                double_list* node = new double_list(value, key);
                map[key] = node;
                node->prev = safe;
                node->next = safe->next;
                safe->next->prev = node;
                safe->next = node;
            } else {
                double_list* last = safe->prev;
                map.erase(last->key);
                last->key = key;
                last->val = value;
                map[key] = last;
                move_node(map[key]);
            }
        }
    }
};

// 94
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (!root) return ans;
    // 0 instack not visit , 1 visited
    unordered_map<TreeNode*, int> map;
    stack<TreeNode*> st;
    st.push(root);
    map[root] = 0;
    while (!st.empty()) {
        TreeNode* top = st.top();
        if (top->left && map[top->left] != 1) {
            st.push(top->left);
            continue;
        }
        ans.push_back(top->val);
        st.pop();
        map[top] = 1;
        if (top->right) {
            st.push(top->right);
        }
    }
    return ans;
}

// 104
int maxDepth(TreeNode* root) {
    int ans = 0;
    if (!root) return ans;
    queue<TreeNode*> q;
    q.push(root);
    unordered_map<TreeNode*, int> map;
    map[root] = 1;
    while (!q.empty()) {
        TreeNode* t = q.front();
        ans = max(ans, map[t]);
        if (t->left) {
            map[t->left] = map[t] + 1;
            q.push(t->left);
        }
        if (t->right) {
            map[t->right] = map[t] + 1;
            q.push(t->right);
        }
        q.pop();
    }
    return ans;
}

// 226
TreeNode* invertTree(TreeNode* root) {
    if (!root) return root;
    TreeNode* l = invertTree(root->left);
    TreeNode* r = invertTree(root->right);
    root->left = r;
    root->right = l;
    return root;
}

// 101
// 判断左右子树是否对称即可
bool isMirror(TreeNode* a, TreeNode* b) {
    if (!a && !b) return true;
    if (!(a && b)) return false;
    bool _1 = a->val == b->val;
    bool _2 = isMirror(a->left, b->right);
    bool _3 = isMirror(a->right, b->left);
    return _1 && _2 && _3;
}
bool isSymmetric(TreeNode* root) {
    if (!root) return true;
    return isMirror(root->left, root->right);
}

// 543
int count_depth(TreeNode* root, int& ans) {
    if (!root) return 0;
    int a = count_depth(root->left, ans);
    int b = count_depth(root->right, ans);
    ans = max(ans, a + b);
    return max(a, b) + 1;
}

int diameterOfBinaryTree(TreeNode* root) {
    int ans = 0;
    int d = count_depth(root, ans);
    return ans;
}

// 102
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if (!root) return ans;
    vector<int> temp;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    int level = 0;
    while (!q.empty()) {
        TreeNode* t = q.front().first;
        int n = q.front().second;
        q.pop();
        if (n == level) {
            temp.push_back(t->val);
        } else {
            level = n;
            ans.push_back(temp);
            temp.clear();
            temp.push_back(t->val);
        }
        if (t->left) {
            q.push({t->left, n + 1});
        }
        if (t->right) {
            q.push({t->right, n + 1});
        }
    }
    if (!temp.empty()) ans.push_back(temp);
    return ans;
}

// 108
TreeNode* reconstruct_108(const vector<int>& nums, int l, int r) {
    if (l == r) return new TreeNode(nums[l]);
    if (l > r) return nullptr;
    int mid = (l + r) / 2;
    //(l , mid - 1) ; mid ; (mid + 1 , r)
    TreeNode* root = new TreeNode(nums[mid]);
    TreeNode* left = reconstruct_108(nums, l, mid - 1);
    TreeNode* right = reconstruct_108(nums, mid + 1, r);
    root->left = left;
    root->right = right;
    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    if (nums.empty()) return nullptr;
    return reconstruct_108(nums, 0, nums.size() - 1);
}

// 98
bool isValidBST(TreeNode* root) {
    vector<int> inorder = inorderTraversal(root);
    for (int i = 1; i < inorder.size(); ++i) {
        if (inorder[i - 1] >= inorder[i]) return false;
    }
    return true;
}

int main() {
    ListNode* head = vectorToList({1, 2, 3, 4, 5});
    auto ans = reverseList(head);
    deleteList(head);
    return 0;
}
