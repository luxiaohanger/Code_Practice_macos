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

// 230
int kthSmallest(TreeNode* root, int k) {
    vector<int> v = inorderTraversal(root);
    return v[k - 1];
}

// 199
// use level_order to get message about level
vector<int> rightSideView(TreeNode* root) {
    vector<int> ans;
    if (!root) return ans;
    queue<TreeNode*> q;
    q.push(root);
    int n = 1;
    while (!q.empty()) {
        int next_n = 0;
        TreeNode* t;
        while (n--) {
            t = q.front();
            q.pop();
            if (t->left) {
                next_n++;
                q.push(t->left);
            }
            if (t->right) {
                next_n++;
                q.push(t->right);
            }
        }
        n = next_n;
        ans.push_back(t->val);
    }
    return ans;
}

// 114
void reconstruct_114(TreeNode* root, TreeNode*& tail) {
    if (!root) return;
    TreeNode* left = root->left;
    TreeNode* right = root->right;
    tail->right = root;
    tail = root;
    tail->left = nullptr;
    tail->right = nullptr;
    reconstruct_114(left, tail);
    reconstruct_114(right, tail);
}

void flatten(TreeNode* root) {
    TreeNode* tail = new TreeNode(0);
    reconstruct_114(root, tail);
    // delete tail;
}

// 105
TreeNode* reconstruct_105(vector<int>& preorder, vector<int>& inorder, int prel,
                          int prer, int inl, int inr,
                          unordered_map<int, int>& umap) {
    if (prel > prer) return nullptr;
    TreeNode* root = new TreeNode(preorder[prel]);
    if (prel == prer) return root;
    // preorder : root,lefttree,righttree
    // inorder : lefttree,root,righttree
    int left_prel, left_prer, right_prel, right_prer, left_inl, left_inr,
        right_inl, right_inr;

    int i = umap[preorder[prel]];
    left_inl = inl;
    left_inr = i - 1;
    right_inl = i + 1;
    right_inr = inr;

    int n_left = left_inr - left_inl + 1;
    left_prel = prel + 1;
    left_prer = left_prel + n_left - 1;
    right_prel = left_prer + 1;
    right_prer = prer;
    root->left = reconstruct_105(preorder, inorder, left_prel, left_prer,
                                 left_inl, left_inr, umap);
    root->right = reconstruct_105(preorder, inorder, right_prel, right_prer,
                                  right_inl, right_inr, umap);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int r = preorder.size() - 1;
    unordered_map<int, int> map;
    for (int i = 0; i <= r; ++i) {
        map[inorder[i]] = i;
    }
    return reconstruct_105(preorder, inorder, 0, r, 0, r, map);
}

// 437
// 本质上是一个树上的两数之和，对前缀和配对
// 精彩的处理是采用了回溯的思想保证当前哈希表中的前缀和都是一条路径上的
// 递归函数的参数选择也很精彩
void dfs_437(TreeNode* root, unordered_map<ll, int>& umap, int& ans, ll pre,
             ll target) {
    ll now = pre + root->val;
    if (umap.contains(now - target)) {
        ans += umap[now - target];
    }
    umap[now]++;
    if (root->left) dfs_437(root->left, umap, ans, now, target);
    if (root->right) dfs_437(root->right, umap, ans, now, target);
    umap[now]--;
}

int pathSum(TreeNode* root, int targetSum) {
    if (!root) return 0;
    unordered_map<ll, int> umap;
    umap[0]++;
    ll pre = 0;
    int ans = 0;
    ll target = static_cast<ll>(targetSum);
    dfs_437(root, umap, ans, pre, target);
    return ans;
}

// 236
void save_path(TreeNode* root, TreeNode* target, vector<TreeNode*>& path,
               bool& find) {
    if (find) return;
    path.push_back(root);
    if (root == target) {
        find = true;
        return;
    }
    if (root->left) save_path(root->left, target, path, find);
    if (root->right) save_path(root->right, target, path, find);
    if (!find) path.pop_back();
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    vector<TreeNode*> pp;
    vector<TreeNode*> qq;
    bool findp = false;
    bool findq = false;
    save_path(root, p, pp, findp);
    save_path(root, q, qq, findq);
    unordered_set<TreeNode*> s(qq.begin(), qq.end());
    for (int i = pp.size() - 1; i >= 0; --i) {
        if (s.contains(pp[i])) return pp[i];
    }
    return nullptr;
}

// 124
// 树中的路径可以归结为从一个root出发，左路径和右路径连接
// 只需dfs每个节点左右路径的最大值即可
void dfs_124(TreeNode* root, unordered_map<TreeNode*, int>& lmap,
             unordered_map<TreeNode*, int>& rmap) {
    int v = root->val;
    if (root->left) dfs_124(root->left, lmap, rmap);
    if (root->right) dfs_124(root->right, lmap, rmap);
    lmap[root] = max(max(lmap[root->left], rmap[root->left]) + v, v);
    rmap[root] = max(max(lmap[root->right], rmap[root->right]) + v, v);
}

void get_ans(TreeNode* root, int& ans, unordered_map<TreeNode*, int>& lmap,
             unordered_map<TreeNode*, int>& rmap) {
    ans = max(ans, lmap[root] + rmap[root] - root->val);
    if (root->left) get_ans(root->left, ans, lmap, rmap);
    if (root->right) get_ans(root->right, ans, lmap, rmap);
}

int maxPathSum(TreeNode* root) {
    if (!root) return 0;
    unordered_map<TreeNode*, int> lmap;
    unordered_map<TreeNode*, int> rmap;
    lmap[nullptr] = 0;
    rmap[nullptr] = 0;
    dfs_124(root, lmap, rmap);
    int ans = INT_MIN;
    get_ans(root, ans, lmap, rmap);
    return ans;
}

// 200
bool check(int i, int j, int n, int m, vector<vector<char>>& grid,
           vector<vector<bool>>& vis) {
    return (i >= 0 && i < n && j >= 0 && j < m) && grid[i][j] == '1' &&
           !vis[i][j];
}

void dfs_200(int i, int j, int n, int m, vector<vector<char>>& grid,
             vector<vector<bool>>& vis) {
    vis[i][j] = true;
    if (check(i + 1, j, n, m, grid, vis)) dfs_200(i + 1, j, n, m, grid, vis);
    if (check(i - 1, j, n, m, grid, vis)) dfs_200(i - 1, j, n, m, grid, vis);
    if (check(i, j + 1, n, m, grid, vis)) dfs_200(i, j + 1, n, m, grid, vis);
    if (check(i, j - 1, n, m, grid, vis)) dfs_200(i, j - 1, n, m, grid, vis);
}

int numIslands(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m));
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '1' && !vis[i][j]) {
                ans++;
                dfs_200(i, j, n, m, grid, vis);
            }
        }
    }
    return ans;
}

// 994
struct badorange {
    int x;
    int y;
    int time;
};

int orangesRotting(vector<vector<int>>& grid) {
    int fresh = 0;
    int n = grid.size();
    int m = grid[0].size();
    queue<badorange> q;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 1)
                fresh++;
            else if (grid[i][j] == 2) {
                q.push({i, j, 0});
            }
        }
    }

    int now = 0;
    while (!q.empty() && fresh != 0) {
        auto bo = q.front();
        q.pop();
        if (bo.x + 1 < n && grid[bo.x + 1][bo.y] == 1) {
            q.push({bo.x + 1, bo.y, bo.time + 1});
            now = bo.time + 1;
            fresh--;
            grid[bo.x + 1][bo.y] = 2;
        }
        if (bo.x - 1 >= 0 && grid[bo.x - 1][bo.y] == 1) {
            q.push({bo.x - 1, bo.y, bo.time + 1});
            now = bo.time + 1;
            fresh--;
            grid[bo.x - 1][bo.y] = 2;
        }
        if (bo.y + 1 < m && grid[bo.x][bo.y + 1] == 1) {
            q.push({bo.x, bo.y + 1, bo.time + 1});
            now = bo.time + 1;
            fresh--;
            grid[bo.x][bo.y + 1] = 2;
        }
        if (bo.y - 1 >= 0 && grid[bo.x][bo.y - 1] == 1) {
            q.push({bo.x, bo.y - 1, bo.time + 1});
            now = bo.time + 1;
            fresh--;
            grid[bo.x][bo.y - 1] = 2;
        }
    }
    if (fresh == 0)
        return now;
    else
        return -1;
}

// 207
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> in(numCourses);
    vector<vector<int>> adj(numCourses);

    for (auto x : prerequisites) {
        in[x[1]]++;
        adj[x[0]].push_back(x[1]);
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (in[i] == 0) q.push(i);
    }
    int check = 0;

    while (!q.empty()) {
        auto x = q.front();
        q.pop();
        check++;
        for (auto y : adj[x]) {
            in[y]--;
            if (in[y] == 0) q.push(y);
        }
    }
    return check == numCourses;
}

// 208
struct Tnode {
    char val;
    bool isEnd;
    vector<Tnode*> child;
};

class Trie {
   private:
    Tnode* root;

    bool dfs(const string& word, int& idx, Tnode* root, Tnode*& last) {
        char target = word[idx];
        last = root;
        for (int i = 0; i < size(root->child); ++i) {
            if (root->child[i]->val == target) {
                if (idx == word.size() - 1) {
                    last = root->child[i];
                    return true;
                }
                return dfs(word, ++idx, root->child[i], last);
            }
        }
        return false;
    }

    void deleteT(Tnode*& root) {
        if (root) {
            for (int i = 0; i < root->child.size(); ++i) {
                deleteT(root->child[i]);
            }
        }
        delete root;
        root = nullptr;
    }

   public:
    Trie() { root = new Tnode(); }

    void insert(string word) {
        Tnode* last;
        int idx = 0;
        auto ans = dfs(word, idx, root, last);
        if (!ans)
            while (idx < word.size()) {
                Tnode* tn = new Tnode();
                tn->val = word[idx];
                last->child.push_back(tn);
                idx++;
                last = tn;
            }
        last->isEnd = true;
    }

    bool search(string word) {
        Tnode* last;
        int idx = 0;
        auto ans = dfs(word, idx, root, last);
        return ans && last->isEnd;
    }

    bool startsWith(string prefix) {
        Tnode* last;
        int idx = 0;
        return dfs(prefix, idx, root, last);
    }

    ~Trie() { deleteT(root); }
};

// 46
void backtrace_46(vector<bool>& vis, vector<int>& temp,
                  vector<vector<int>>& ans, vector<int>& nums) {
    if (temp.size() == nums.size()) {
        ans.push_back(temp);
        return;
    }

    for (int i = 0; i < nums.size(); ++i) {
        if (!vis[i]) {
            temp.push_back(nums[i]);
            vis[i] = true;
            backtrace_46(vis, temp, ans, nums);
            temp.pop_back();
            vis[i] = false;
        }
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<bool> vis(nums.size());
    vector<int> temp;
    vector<vector<int>> ans;
    backtrace_46(vis, temp, ans, nums);
    return ans;
}

// 78
// 和全排列不同之处在于不能有重复序列，因此可以考虑用顺序排除重复序列
// 增加枚举起始下标，确保每次枚举的数字都比之前大
void back_track_78(int n, vector<int>& nums, vector<int>& temp,
                   vector<vector<int>>& ans, vector<bool>& vis, int start) {
    if (temp.size() == n) {
        ans.push_back(temp);
        return;
    }
    for (int i = start; i < nums.size(); ++i) {
        if (!vis[i]) {
            temp.push_back(nums[i]);
            vis[i] = true;
            back_track_78(n, nums, temp, ans, vis, i + 1);
            temp.pop_back();
            vis[i] = false;
        }
    }
}

// vector<vector<int>> subsets(vector<int>& nums) {
//     vector<vector<int>> ans;
//     for (int i = 0; i <= nums.size(); ++i) {
//         vector<int> temp;
//         vector<bool> vis(nums.size());
//         back_track_78(i, nums, temp, ans, vis, 0);
//     }
//     return ans;
// }

// way2:注意到 0-2^n - 1 的二进制1的位置恰好对应所有选取方法
vector<vector<int>> subsets(vector<int>& nums) {
    int n = nums.size();
    vector<int> temp;
    vector<vector<int>> ans;
    for (int i = 0; i < (1 << n); ++i) {
        temp.clear();
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) temp.push_back(nums[j]);
        }
        ans.push_back(temp);
    }
    return ans;
}

// 17
void backtrack_17(vector<string>& ans, string& temp, string digits,
                  vector<string>& mp) {
    if (temp.size() == digits.size()) {
        ans.push_back(temp);
        return;
    }
    int num = digits[temp.size()] - '0';
    for (int i = 0; i < mp[num].size(); ++i) {
        temp.push_back(mp[num][i]);
        backtrack_17(ans, temp, digits, mp);
        temp.pop_back();
    }
}
vector<string> letterCombinations(string digits) {
    vector<string> mp{"",    "",    "abc",  "def", "ghi",
                      "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ans;
    string temp;
    backtrack_17(ans, temp, digits, mp);
    return ans;
}

// 39
struct Vsum {
    vector<int> v;
    int sum;
};

void backtrack_39(vector<int>& candidates, int target, vector<vector<int>>& ans,
                  Vsum& temp, int idx) {
    if (temp.sum == target) {
        ans.push_back(temp.v);
        return;
    }
    for (int i = idx; i < candidates.size(); ++i) {
        if (temp.sum + candidates[i] > target) continue;
        temp.v.push_back(candidates[i]);
        temp.sum += candidates[i];
        backtrack_39(candidates, target, ans, temp, i);
        temp.v.pop_back();
        temp.sum -= candidates[i];
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    Vsum temp{};  // init is important!
    backtrack_39(candidates, target, ans, temp, 0);
    return ans;
}

// 22
// 由组合识别为回溯模型，思考终止条件、当前可以dfs的路径
void back_track_22(vector<string>& ans, string& temp, int& left, int& right,
                   int n) {
    if (left == right && left == n) {
        ans.push_back(temp);
        return;
    }

    if (left > right) {
        temp += ')';
        right++;
        back_track_22(ans, temp, left, right, n);
        temp.pop_back();
        right--;
    }

    if (left < n) {
        temp += '(';
        left++;
        back_track_22(ans, temp, left, right, n);
        temp.pop_back();
        left--;
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> ans;
    string temp;
    int left = 0;
    int right = 0;
    back_track_22(ans, temp, left, right, n);
    return ans;
}

// 79
void dfs_79(int i, int j, vector<vector<char>>& board, string word,
            vector<vector<bool>>& vis, int idx, bool& find) {
    if (find) return;

    if (idx == word.size() - 1) {
        find = true;
        return;
    }

    int n = board.size();
    int m = board[0].size();
    idx++;
    if (i + 1 < n && !vis[i + 1][j] && board[i + 1][j] == word[idx]) {
        vis[i + 1][j] = true;
        dfs_79(i + 1, j, board, word, vis, idx, find);
        vis[i + 1][j] = false;
    }
    if (i - 1 >= 0 && !vis[i - 1][j] && board[i - 1][j] == word[idx]) {
        vis[i - 1][j] = true;
        dfs_79(i - 1, j, board, word, vis, idx, find);
        vis[i - 1][j] = false;
    }
    if (j + 1 < m && !vis[i][j + 1] && board[i][j + 1] == word[idx]) {
        vis[i][j + 1] = true;
        dfs_79(i, j + 1, board, word, vis, idx, find);
        vis[i][j + 1] = false;
    }
    if (j - 1 >= 0 && !vis[i][j - 1] && board[i][j - 1] == word[idx]) {
        vis[i][j - 1] = true;
        dfs_79(i, j - 1, board, word, vis, idx, find);
        vis[i][j - 1] = false;
    }
}

bool exist(vector<vector<char>>& board, string word) {
    int n = board.size();
    int m = board[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == word[0]) {
                bool find = false;
                vector<vector<bool>> vis(n, vector<bool>(m));
                // 操作依赖上一次递归时，注意考虑起始元素的处理
                vis[i][j] = true;
                dfs_79(i, j, board, word, vis, 0, find);
                if (find) return true;
            }
        }
    }
    return false;
}

// 131
struct PairHash {
    size_t operator()(const std::pair<int, int>& p) const {
        // 常用组合哈希算法（例如加权异或或 hash_combine）
        return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
    }
};

std::unordered_set<std::pair<int, int>, PairHash> pair_set;

bool check_131(const string& s, vector<int>& sep) {
    sep.push_back(s.size());
    for (int i = 0; i < sep.size() - 1; ++i) {
        if (!pair_set.contains({sep[i], sep[i + 1]})) {
            int len = sep[i + 1] - sep[i];
            for (int j = 0; j < len && sep[i] + j < sep[i + 1] - j - 1; ++j) {
                if (s[sep[i] + j] != s[sep[i + 1] - j - 1]) {
                    sep.pop_back();
                    return false;
                }
            }
            pair_set.insert({sep[i], sep[i + 1]});
        }
    }
    sep.pop_back();
    return true;
}

vector<string> getStr(vector<int>& sep, const string& s) {
    vector<string> S;
    string temp;
    sep.push_back(s.size());
    for (int i = 0; i < sep.size() - 1; ++i) {
        temp.clear();
        for (int j = sep[i]; j < sep[i + 1]; ++j) temp += s[j];
        S.push_back(temp);
    }
    sep.pop_back();
    return S;
}

void back_track_131(const string& s, vector<vector<string>>& ans,
                    vector<int>& sep, int idx) {
    if (check_131(s, sep)) {
        ans.push_back(getStr(sep, s));
    }
    for (int i = idx + 1; i < s.size(); ++i) {
        sep.push_back(i);
        back_track_131(s, ans, sep, i);
        sep.pop_back();
    }
}

vector<vector<string>> partition(string s) {
    vector<vector<string>> ans;
    vector<int> sep{0};
    back_track_131(s, ans, sep, 0);
    return ans;
}

// 51
void back_track_51(int x, vector<int>& temp, vector<bool>& vis,
                   unordered_set<int>& l1, unordered_set<int>& l2,
                   vector<vector<string>>& ans, int n) {
    if (x == n - 1) {
        vector<string> s;
        string ss;
        for (int i = 0; i < n; ++i) ss += '.';
        for (int i = 0; i < n; ++i) {
            ss[temp[i]] = 'Q';
            s.push_back(ss);
            ss[temp[i]] = '.';
        }
        ans.push_back(s);
        return;
    }

    //[x + 1][tobeselect]
    for (int i = 0; i < n; ++i) {
        if (!vis[i] && !l1.contains(x + 1 + i) && !l2.contains(x + 1 - i)) {
            vis[i] = true;
            l1.insert(x + 1 + i);
            l2.insert(x + 1 - i);
            temp[x + 1] = i;
            back_track_51(x + 1, temp, vis, l1, l2, ans, n);
            vis[i] = false;
            l1.erase(x + 1 + i);
            l2.erase(x + 1 - i);
            temp[x + 1] = -1;
        }
    }
}
vector<vector<string>> solveNQueens(int n) {
    unordered_set<int> l1;
    unordered_set<int> l2;
    vector<int> temp(n, -1);
    vector<bool> vis(n);
    vector<vector<string>> ans;
    int x = -1;
    for (int i = 0; i < n; ++i) {
        vis[i] = true;
        l1.insert(x + 1 + i);
        l2.insert(x + 1 - i);
        temp[x + 1] = i;
        back_track_51(x + 1, temp, vis, l1, l2, ans, n);
        vis[i] = false;
        l1.erase(x + 1 + i);
        l2.erase(x + 1 - i);
        temp[x + 1] = -1;
    }
    return ans;
}

// 35
int searchInsert(vector<int>& nums, int target) {
    auto ans = lower_bound(nums.begin(), nums.end(), target);
    if (ans == nums.end()) return nums.size();
    int res = 0;
    for (; res < nums.size(); ++res) {
        if (nums[res] == *ans) break;
    }
    return res;
}

// 74
int trans(vector<vector<int>>& matrix, int x) {
    int m = matrix[0].size();
    return matrix[x / m][x % m];
}

bool searchMatrix_(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();
    int m = matrix[0].size();
    int N = m * n;
    int left = 0;
    int right = N - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int M = trans(matrix, mid);
        if (M == target)
            return true;
        else if (M > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return false;
}

// 75
vector<int> searchRange(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    int low = -1;
    int high = -1;
    if (!nums.empty()) {
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] == target) {
                right = mid;
                if (left == right) {
                    low = mid;
                    break;
                }
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        left = 0;
        right = nums.size() - 1;
        while (left <= right) {
            int mid = (left + right + 1) / 2;
            if (nums[mid] == target) {
                left = mid;
                if (left == right) {
                    high = mid;
                    break;
                }
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }
    return {low, high};
}

// 33
int search(vector<int>& nums, int target) {
    int n = nums.size();
    int l = 0;
    int r = n - 1;
    int begin = 0;
    if (nums[l] > nums[r]) {
        while (l < r - 2) {
            int m1 = l + (r - l) / 3;
            int m2 = l + 2 * (r - l) / 3;
            if (nums[l] < nums[m1] && nums[m1] < nums[m2]) {
                l = m2;
            } else if (nums[l] < nums[m1] && nums[m1] > nums[m2]) {
                l = m1;
                r = m2;
            } else {
                r = m1;
            }
        }

        if (l == r - 1)
            begin = r;
        else if (l == r - 2) {
            if (nums[l] < nums[l + 1])
                begin = r;
            else
                begin = l + 1;
        }
    }
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int m = (left + right) / 2;
        int mid = (begin + m) % n;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] > target)
            right = m - 1;
        else
            left = m + 1;
    }
    return -1;
}

// 153
int findMin(vector<int>& nums) {
    int n = nums.size();
    int l = 0;
    int r = n - 1;
    int begin = 0;
    if (nums[l] > nums[r]) {
        while (l < r - 2) {
            int m1 = l + (r - l) / 3;
            int m2 = l + 2 * (r - l) / 3;
            if (nums[l] < nums[m1] && nums[m1] < nums[m2]) {
                l = m2;
            } else if (nums[l] < nums[m1] && nums[m1] > nums[m2]) {
                l = m1;
                r = m2;
            } else {
                r = m1;
            }
        }

        if (l == r - 1)
            begin = r;
        else if (l == r - 2) {
            if (nums[l] < nums[l + 1])
                begin = r;
            else
                begin = l + 1;
        }
    }
    return nums[begin];
}

// 4
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {}

// 20
bool isValid(string s) {
    stack<char> st;

    for (const auto& x : s) {
        if (x == '(' || x == '[' || x == '{') {
            st.push(x);
        }

        if (x == ')') {
            if (!st.empty() && st.top() == '(') {
                st.pop();
            } else {
                return false;
            }
        }

        if (x == ']') {
            if (!st.empty() && st.top() == '[') {
                st.pop();
            } else {
                return false;
            }
        }
        if (x == '}') {
            if (!st.empty() && st.top() == '{') {
                st.pop();
            } else {
                return false;
            }
        }
    }
    return st.empty();
}

// 155
// 使用辅助栈help记录当前元素入栈时的最小值
class MinStack {
   private:
    stack<int> st;
    stack<int> help;

   public:
    MinStack() {}

    void push(int val) {
        if (!st.empty()) {
            st.push(val);
            help.push(::min(val, help.top()));
        } else {
            st.push(val);
            help.push(val);
        }
    }

    void pop() {
        st.pop();
        help.pop();
    }

    int top() { return st.top(); }

    int getMin() { return help.top(); }
};

// 394
// 递归深入嵌套括号
// 遇到数字就进入解码递归，将本括号解码结果加入答案字符ans
// 递归的桥梁就是让临时ss作为子递归的ans
void decodes(string& ans, string& s, int& idx) {
    string num;
    while (isdigit(s[idx])) {
        num += s[idx];
        ++idx;
    }
    int n = stoi(num);
    string ss;
    ++idx;
    while (true) {
        if (s[idx] == ']') break;
        if (isdigit(s[idx])) {
            decodes(ss, s, idx);
        } else {
            ss += s[idx];
        }
        ++idx;
    }
    for (int j = 0; j < n; ++j) ans += ss;
}

string decodeString(string s) {
    string ans;
    int idx = 0;
    while (idx < s.size()) {
        if (isdigit(s[idx]))
            decodes(ans, s, idx);
        else
            ans += s[idx];
        // while 循环注意内部更新下标
        ++idx;
    }
    return ans;
}

// 739
vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    stack<pii> st;
    vector<int> ans(n);
    for (int i = 0; i < temperatures.size(); ++i) {
        while (!st.empty() && temperatures[i] > st.top().first) {
            ans[st.top().second] = i - st.top().second;
            st.pop();
        }
        st.push({temperatures[i], i});
    }
    return ans;
}

// 84
// 单调栈统计两侧第一个比自己低的柱子，结合起来得到最大面积
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    vector<int> left(n, -1);
    vector<int> right(n, n);
    stack<pii> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && heights[i] < st.top().first) {
            right[st.top().second] = i;
            st.pop();
        }
        st.push({heights[i], i});
    }

    while (!st.empty()) st.pop();

    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && heights[i] < st.top().first) {
            left[st.top().second] = i;
            st.pop();
        }
        st.push({heights[i], i});
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, heights[i] * (right[i] - left[i] - 1));
    }
    return ans;
}

// 215
int findKthLargest(vector<int>& nums, int k) {
    int idx = nums.size() - k;
    nth_element(nums.begin(), nums.begin() + idx, nums.end());
    return nums[idx];
}

// 347
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> ump;
    for (auto x : nums) {
        ump[x]++;
    }
    vector<pii> v;
    for (auto x : ump) {
        v.push_back(x);
    }

    nth_element(v.begin(), v.begin() + k, v.end(),
                [](pii a, pii b) { return a.second > b.second; });
    vector<int> ans;
    for (int i = 0; i < k; ++i) ans.push_back(v[i].first);
    return ans;
}

// 295
class MedianFinder {
   private:
    priority_queue<int, vector<int>,
                   decltype([](int a, int b) { return a < b; })>
        maxheap;

    priority_queue<int, vector<int>,
                   decltype([](int a, int b) { return a > b; })>
        minheap;

   public:
    MedianFinder() {}

    void addNum(int num) {
        // keep n1 >= n2
        int n1 = minheap.size();
        int n2 = maxheap.size();
        if (n1 == 0) {
            minheap.push(num);
            return;
        }
        if (n2 == 0) {
            if (num > minheap.top()) {
                minheap.push(num);
                int x = minheap.top();
                minheap.pop();
                maxheap.push(x);
            } else
                maxheap.push(num);
            return;
        }
        if (num >= minheap.top()) {
            if (n1 == n2)
                minheap.push(num);
            else {
                // n1 == n2 + 1
                minheap.push(num);
                int x = minheap.top();
                minheap.pop();
                maxheap.push(x);
            }
        } else {
            if (n1 == n2) {
                maxheap.push(num);
                int x = maxheap.top();
                maxheap.pop();
                minheap.push(x);
            } else {
                maxheap.push(num);
            }
        }
    }

    double findMedian() {
        int n1 = minheap.size();
        int n2 = maxheap.size();
        if (n2 == 0) return minheap.top();
        if (n1 == n2)
            return (minheap.top() + maxheap.top()) / 2.0;
        else
            return minheap.top();
    }
};

// 121
int maxProfit(vector<int>& prices) {
    int min = INT_MAX;
    int ans = 0;
    for (int i = 0; i < prices.size(); ++i) {
        ans = max(prices[i] - min, ans);
        min = ::min(min, prices[i]);
    }
    return ans;
}

// 55
bool canJump(vector<int>& nums) {
    int n = nums.size();
    int far = 0;
    for (int i = 0; i < n; ++i) {
        if (far < i) return false;
        far = max(far, i + nums[i]);
    }
    return true;
}

// 45
int jump(vector<int>& nums) {
    int idx = 0;
    int step = 0;
    if (nums.size() == 1) return 0;
    while (idx < nums.size()) {
        int far = 0;
        int next = 0;
        for (int i = 1; i <= nums[idx]; ++i) {
            if (idx + i >= nums.size() - 1) {
                next = nums.size();
                break;
            }
            if (far < idx + i + nums[idx + i]) {
                next = i + idx;
                far = idx + i + nums[idx + i];
            }
        }
        step++;
        idx = next;
    }
    return step;
}

// 763
vector<int> partitionLabels(string s) {
    // 记录每个字母最后出现的位置
    vector<int> v(26);
    for (int i = 0; i < s.size(); ++i) {
        v[s[i] - 'a'] = i;
    }
    int l = 0;
    int r = 0;
    vector<int> ans;
    while (l < s.size()) {
        int now = l;
        while (now <= r) {
            r = ::max(r, v[s[now] - 'a']);
            ++now;
        }
        ans.push_back(r - l + 1);
        l = now;
        r = now;
    }
    return ans;
}

int main() {
    vector<int> nums{4, 5, 6, 7, 0, 1, 2};
    auto ans = search(nums, 3);
    cout << ans;
    return 0;
}
