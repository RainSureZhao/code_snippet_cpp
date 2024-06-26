typedef struct node
{
    int l, r;
    int cnt;
}Node;
vector<Node> tr(n * 24); // 根据实际情况设置大小
vector<int> root(n + 1);
int idx = 0;
function<int(int, int)> build([&](int l, int r) {
    int p = ++ idx;
    if(l == r) return p;
    int mid = (l + r) >> 1;
    tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
    return p;
});
function<int(int, int, int, int)> insert([&](int p, int l, int r, int x) {
    int q = ++ idx;
    tr[q] = tr[p];
    if(l == r)
    {
        tr[q].cnt ++;
        return q;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) tr[q].l = insert(tr[p].l, l, mid, x);
    else tr[q].r = insert(tr[p].r, mid + 1, r, x);
    tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;
    return q;
});
function<int(int, int, int, int, int)> query([&](int p, int q, int l, int r, int k) { // 查询下标位于区间[p, q]之间，k出现的次数
    if(l == r) return tr[q].cnt - tr[p].cnt;
    int mid = (l + r) >> 1;
    if(k <= mid) return query(tr[p].l, tr[q].l, l, mid, k);
    else return query(tr[p].r, tr[q].r, mid + 1, r, k);
});
function<int(int, int, int, int, int)> query([&](int p, int q, int l, int r, int k) { // 查询区间k小数
    if(l == r) return r;
    int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;
    int mid = (l + r) >> 1;
    if(k <= cnt) return query(tr[p].l, tr[q].l, l, mid, k);
    else return query(tr[p].r, tr[q].r, mid + 1, r, k - cnt);
});
function<int(int, int, int, int, int, int)> query([&](int u, int v, int l, int r, int x, int y) { // 查询在下标位于[u, v]中位于区间[x, y]的个数
    if(x <= l && r <= y) return tr[v].cnt - tr[u].cnt;
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid) res += query(tr[u].l, tr[v].l, l, mid, x, y);
    if(y > mid) res += query(tr[u].r, tr[v].r, mid + 1, r, x, y);
    return res;
});
// query(root[l - 1], root[r], 1, n, x, y);
vector<int> a(n + 1);
// 离散化写法
vector<int> nums;
for(int i = 1; i <= n; i ++) nums.push_back(a[i]);
sort(begin(nums), end(nums));
nums.erase(unique(nums.begin(), nums.end()), nums.end());
auto find([&](int x) {
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
});
root[0] = build(0, nums.size() - 1);
for(int i = 1; i <= n; i ++){
    root[i] = insert(root[i - 1], 0, nums.size() - 1, find(a[i]));
}
// 非离散化写法
for(int i = 1; i <= n; i ++) {
    root[i] = insert(root[i - 1], 1, n, a[i]);
}
// 查询区间[l, r]的第k小值
int v = query(root[l - 1], root[r], 1, n, k);