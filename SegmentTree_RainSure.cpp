// 不带懒标记的线段树，支持单点修改，区间查询操作 ——Rain Sure
template<class Info, class Merge = std::plus<Info>>
struct SegmentTree {
    const int n;
    const Merge merge;
    struct Node {
        int l, r;
        Info info;
    };
    vector<Node> tr;
    SegmentTree(const int n) : n(n), merge(Merge()), tr(4 * n + 10) {}
    SegmentTree(const vector<Info> &init) : SegmentTree(init.size() - 1) {
        function<void(int, int, int)> build([&](int u, int l, int r) {
            if(l == r) {
                tr[u] = {l, l, init[l]};
            } else {
                tr[u] = {l, r};
                int mid = (l + r) >> 1;
                build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
                pushup(u);
            }
        });
        build(1, 1, n);
    }
    void pushup(Node &u, Node &l, Node &r) {
        u.info = merge(l.info, r.info);
    }
    void pushup(int u) {
        pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
    }
    void modify(int u, int p, const Info &v) {
        if(tr[u].l == tr[u].r and tr[u].l == p) {
            tr[u].info = v;
        } else {
            int mid = (tr[u].l + tr[u].r) >> 1;
            if(p <= mid) modify(u << 1, p, v);
            else modify(u << 1 | 1, p, v);
            pushup(u);
        }
    }
    Info query(int u, int l, int r) {
        if(tr[u].l >= l and tr[u].r <= r) {
            return tr[u].info;
        } else {
            int mid = (tr[u].l + tr[u].r) >> 1;
            Info res;
            if(l <= mid) res = merge(res, query(u << 1, l, r));
            if(r > mid) res = merge(res, query(u << 1 | 1, l, r));
            return res;
        }
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
struct Sum {
    int x;
    Sum(int x = 0): x(x) {}
};
Sum operator+(const Sum &a, const Sum &b) {
    return Sum(a.x + b.x);
}

bool f(const Sum& v, const Sum& v1) {
    return v.x >= v1.x;
}

struct Max {
    int x;
    Max(int x = -1e9): x(x) {}
};
Max operator+(const Max &a, const Max &b) {
    return Max{max(a.x, b.x)};
}

struct Min {
    int x;
    Min(int x = 1e9): x(x) {}
};
Min operator+(const Min &a, const Min &b) {
    return Min{min(a.x, b.x)};
}

struct Gcd {
    int x;
    Gcd(int x = 1) : x(x) {}
};
Gcd operator+(const Gcd &a, const Gcd &b) {
    return Gcd(gcd(a.x, b.x));
}
