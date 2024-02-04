template<class Info, class Merge = std::plus<Info>>
struct sparse_table {
	const int n;
	const Merge merge;
	vector<vector<Info>> f;
	sparse_table(const vector<Info> &a) : n(a.size()), merge(Merge()) {
		f = vector<vector<Info>>(n, vector<Info>(__lg(n) + 1));
		for(int j = 0; j <= __lg(n); j ++) {
			for(int i = 0; i + (1 << j) - 1 < n; i ++) {
				if(!j) f[i][j] = a[i];
				else {
					f[i][j] = merge(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
				}
			}
		}
	} 
	Info query(const int l, const int r) {
		if(r < l) return Info();
		int k = __lg(r - l + 1);
		return merge(f[l][k], f[r - (1 << k) + 1][k]);
	}
};
struct Max {
	int x;
	Max(int x = 0) : x(x) {}
};
Max operator+(const Max &a, const Max &b) {
	return max(a.x, b.x);
}

struct Min {
	int x;
	Min(int x = 0) : x(x) {}
};
Min operator+(const Min &a, const Min &b) {
	return min(a.x, b.x);
}
struct Gcd {
	int x;
	Gcd(int x = 0) : x(x) {}
};
Gcd operator+(const Gcd &a, const Gcd &b) {
	return std::gcd(a.x, b.x);
}