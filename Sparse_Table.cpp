struct sparse_table {
	int n;
	vector<vector<int>> f, g;
	sparse_table(const vector<int> &a) : n(a.size()) {
		f = vector<vector<int>>(n, vector<int>(__lg(n) + 1));
		g = vector<vector<int>>(n, vector<int>(__lg(n) + 1));
		for(int j = 0; j <= __lg(n); j ++) {
			for(int i = 0; i + (1 << j) - 1 < n; i ++) {
				if(!j) f[i][j] = g[i][j] = a[i];
				else {
					f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
					g[i][j] = min(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
				}
			}
		}
	} 
	int query_max(const int l, const int r) {
		int k = __lg(r - l + 1);
		return max(f[l][k], f[r - (1 << k) + 1][k]);
	}
	int query_min(const int l, const int r) {
		int k = __lg(r - l + 1);
		return min(g[l][k], g[r - (1 << k) + 1][k]);
	}
};