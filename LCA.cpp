class LCA {
    // const int maxn = 100010, M = 2000010;
    // int h[maxn], e[M], ne[M], idx; 图存在全局变量中
    vector<int> depth;
    vector<vector<int>> fa;
public:
    LCA(int sz, int root) {
        depth.resize(sz + 1);
        fill(begin(depth), end(depth), inf);
        fa.resize(sz + 1);
        for(int i = 0; i <= sz; i ++) {
            fa[i].resize(20);
        }
        depth[0] = 0, depth[root] = 1;
        queue<int> q;
        q.push(root);
        while(q.size()) {
            auto t = q.front();
            q.pop();
            for(int i = h[t]; ~i; i = ne[i]) {
                int j = e[i];
                if(depth[j] > depth[t] + 1) {
                    depth[j] = depth[t] + 1;
                    q.push(j);
                    fa[j][0] = t;
                    for(int k = 1; k < 20; k ++) {
                        fa[j][k] = fa[fa[j][k - 1]][k - 1];
                    }
                }
            }
        }
    }
    int lca(int a, int b) {
        if(a == 0) return b; 
        if(b == 0) return a;
        if(depth[a] < depth[b]) swap(a, b);
        for(int k = 19; k >= 0; k -- ) {
            if(depth[fa[a][k]] >= depth[b]) {
                a = fa[a][k];
            }
        }
        if(a == b) return a;
        for(int k = 19; k >= 0; k --) {
            if(fa[a][k] != fa[b][k]) {
                a = fa[a][k];
                b = fa[b][k];
            }
        }
        return fa[a][0];
    }
    int query_depth(int x) {
        return depth[x];
    }
};