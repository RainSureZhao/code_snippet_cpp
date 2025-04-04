// 可持久化堆，支持懒删除
template<typename T, typename Compare = less<T>>
class LazyHeap {
    priority_queue<T, vector<T>, Compare> pq;
    unordered_map<T, int> remove_cnt; // 每个元素剩余需要删除的次数
    size_t sz = 0; // 实际大小
    long long s = 0; // 堆中元素总和

    // 正式执行删除操作
    void apply_remove() {
        while (!pq.empty() && remove_cnt[pq.top()] > 0) {
            remove_cnt[pq.top()]--;
            pq.pop();
        }
    }

public:
    size_t size() {
        return sz;
    }

    long long sum() {
        return s;
    }

    // 删除
    void remove(T x) {
        remove_cnt[x]++; // 懒删除
        sz--;
        s -= x;
    }

    // 查看堆顶
    T top() {
        apply_remove();
        return pq.top();
    }

    // 出堆
    T pop() {
        apply_remove();
        T x = pq.top();
        pq.pop();
        sz--;
        s -= x;
        return x;
    }

    // 入堆
    void push(T x) {
        if (remove_cnt[x] > 0) {
            remove_cnt[x]--; // 抵消之前的删除
        } else {
            pq.push(x);
        }
        sz++;
        s += x;
    }

    // push(x) 然后 pop()
    T push_pop(T x) {
        apply_remove();
        pq.push(x);
        s += x;
        x = pq.top();
        pq.pop();
        s -= x;
        return x;
    }
};

// examples 
LazyHeap<int> left; // 最大堆
LazyHeap<int, greater<int>> right; // 最小堆

// 通常可用于维护中位数

// 480. 滑动窗口中位数（有改动）
// 返回 nums 的所有长为 k 的子数组的（到子数组中位数的）距离和
vector<long long> medianSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> ans(n - k + 1);
    LazyHeap<int> left; // 最大堆
    LazyHeap<int, greater<int>> right; // 最小堆

    for (int i = 0; i < n; i++) {
        // 1. 进入窗口
        int in = nums[i];
        if (left.size() == right.size()) {
            left.push(right.push_pop(in));
        } else {
            right.push(left.push_pop(in));
        }

        int l = i + 1 - k;
        if (l < 0) { // 窗口大小不足 k
            continue;
        }

        // 2. 计算答案
        long long v = left.top();
        long long s1 = v * left.size() - left.sum();
        long long s2 = right.sum() - v * right.size();
        ans[l] = s1 + s2;

        // 3. 离开窗口
        int out = nums[l];
        if (out <= left.top()) {
            left.remove(out);
            if (left.size() < right.size()) {
                left.push(right.pop()); // 平衡两个堆的大小
            }
        } else {
            right.remove(out);
            if (left.size() > right.size() + 1) {
                right.push(left.pop()); // 平衡两个堆的大小
            }
        }
    }

    return ans;
}