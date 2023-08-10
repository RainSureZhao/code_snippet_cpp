vector<vector<PII>> adj(n);
vector<PII> edges;
for(int i = 0; i < m; i ++) {
    int a, b;
    cin >> a >> b;
    a --, b --;
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
    edges.push_back({a, b});
}
vector<int> dfn(n), low(n), bel(n), bridge; // bel是双连通分量的编号, bridge存桥
vector<vector<int>> bs; // bs存每个双连通分量的点
int idx = 0;
stack<int> stk;
function<void(int, int)> tarjan([&](int u, int id) {
    dfn[u] = low[u] = ++idx;
    stk.push(u);
    for(auto &[v, id2] : adj[u]){
        if(id == id2) continue;
        if(!dfn[v]){
            tarjan(v, id2);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u]){
        if(id != -1) bridge.push_back(id);
        vector<int> cc;
        while(1){
            int v = stk.top();
            stk.pop();
            cc.push_back(v);
            bel[v] = bs.size();
            if(v == u) break;
        }
        bs.push_back(cc);
    }
});
tarjan(0, -1);

// 根据双连通分量建新图
vector<vector<int>> v(n + 1);
int root = -1;
for(auto id : bridge) {
    auto [x, y] = edges[id];
    x = bel[x], y = bel[y];
    v[x].push_back(y);
    v[y].push_back(x);
    root = x;
}