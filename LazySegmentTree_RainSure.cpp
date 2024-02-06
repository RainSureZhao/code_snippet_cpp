template<typename Info, typename Tag>
struct LazySegmentTree {
    struct Node {
        int l, r;
        Info info;
        Tag tag;
    };
    const int n;
    vector<Node> tr;
    LazySegmentTree(const int n) : n(n), tr(4 * n + 10) {}
    LazySegmentTree(const vector<Info> &init) : LazySegmentTree(init.size() - 1) {
        function<void(int, int, int)> build([&](int u, int l, int r) {
            if(l == r) {
                tr[u].l = l, tr[u].r = r, tr[u].info = init[l];
            } else {
                tr[u].l = l, tr[u].r = r;
                int mid = (l + r) >> 1;
                build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
                pushup(u);
            }
        });
        build(1, 1, n);
    }
    void pushup(int u) {
        pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
    }
    void pushup(Node &u, Node &l, Node &r) {
        u.info = l.info + r.info;
    }
    void pushdown(int u) {
        pushdown(tr[u], tr[u << 1], tr[u << 1 | 1]);
    }
    void apply(Node &u, const Tag &v) {
        u.info.apply(v);
        u.tag.apply(v);
    }
    void pushdown(Node &u, Node &l, Node &r) {
        apply(l, u.tag);
        apply(r, u.tag);
        u.tag = Tag();
    }
    // 修改一个区间为某个值
    void modify(int u, int l, int r, const Info &v) {
        if(tr[u].l == tr[u].r) {
            tr[u].info = v;
            return;
        }
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(l <= mid) modify(u << 1, l, r, v);
        if(r > mid) modify(u << 1 | 1, l, r, v);
        pushup(u);
    }
    // 对区间[l, r]操作v
    void modify(int u, int l, int r, const Tag &v) {
        if(tr[u].l >= l && tr[u].r <= r) {
            apply(tr[u], v);
            return;
        }
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(l <= mid) modify(u << 1, l, r, v);
        if(r > mid) modify(u << 1 | 1, l, r, v);
        pushup(u);
    }
    // 区间查询
    Info query(int u, int l, int r) {
        if(tr[u].l >= l and tr[u].r <= r) {
            return tr[u].info;
        }
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        Info res = Info();
        if(l <= mid) res = res + query(u << 1, l, r);
        if(r > mid) res = res + query(u << 1 | 1, l, r);
        return res;
    }
    int query_first(int u, int l, int r, const Info& v, const function<bool(const Info& a, const Info& b)>& f, Info cur = Info()) {
        if(tr[u].l == tr[u].r) { // 如果是叶子节点，直接判断
            auto tmp = cur + tr[u].info;
            return f(tmp, v) ? tr[u].l : -1; // 如果满足条件返回位置，否则返回-1
        }
        int mid = (tr[u].l + tr[u].r) >> 1;
        auto left_info = cur;
        if(l <= mid) { // 如果左子树有满足条件的节点
            auto tmp = cur + tr[u << 1].info;
            if(f(tmp, v)) {
                return query_first(u << 1, l, r, v, f, left_info);
            }
        }
        if(r > mid) { // 如果右子树有满足条件的节点
            cur = cur + tr[u << 1].info;
            return query_first(u << 1 | 1, l, r, v, f, cur);
        }
        return -1; // 没有找到满足条件的位置
    }   
    int query_last(int u, int l, int r, const Info& v, const function<bool(const Info& a, const Info &b)>& f, Info cur = Info()) {
        if(tr[u].l == tr[u].r) { // 如果是叶子节点，直接判断
            auto tmp = cur + tr[u].info;
            return f(tmp, v) ? tr[u].l : -1; // 如果满足条件返回位置，否则返回-1
        }
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(r > mid) { // 如果右子树有满足条件的节点
            auto tmp = cur + tr[u << 1].info;
            if(f(tmp, v)) {
                return query_last(u << 1 | 1, l, r, v, f, tmp);
            }
        }
        if(l <= mid) { // 如果左子树有满足条件的节点
            return query_last(u << 1, l, r, v, f, cur);
        }
        return -1; // 没有找到满足条件的位置
    }
};

struct Tag {
    int x = 0;
    Tag(int x = 0) : x(x) {}
    void apply(const Tag &other) { // 懒标记与懒标记的合并
        x += other.x;
    }
};

struct Info {
    int x = 0;
    int len = 0;
    Info() = default;
    Info(int x, int len) : x(x), len(len) {}
    void apply(const Tag &tag) { // 信息与懒标记的合并
        x += tag.x * len;
    }
};
Info operator+ (const Info &a, const Info &b) { // 信息与信息的合并
    return Info(a.x + b.x, a.len + b.len);
}


bool f(const Info& v, const Info& v1) {
    return v.x >= v1.x;
}