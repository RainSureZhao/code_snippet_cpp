// // 不带懒标记的线段树，支持单点修改，区间查询操作 ——Rain Sure
template<class Info, class Merge = std::plus<Info>>
struct SegmentTree {
	const int n;
	const Merge merge;
	struct Node {
		int l, r;
		Info info;
	};
	vector<Node> tr;
	SegmentTree(const int n) : n(n + 1), merge(Merge()), tr(4 * n + 10) {}
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
};
struct Sum {
    int x;
    Sum(int x = 0): x(x) {}
};
Sum operator+(const Sum &a, const Sum &b) {
    return Sum(a.x + b.x);
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