vector<int> in(n), out(n);
int cur = 1;
vector<vector<int>> adj(n);
for(const auto& p : leadership) {
    int a = p[0], b = p[1];
    a --, b --;
    adj[a].push_back(b);
}
function<void(int)> dfs([&](int u) {
    in[u] = cur ++;
    for(auto x : adj[u]) {
        dfs(x);
    }
    out[u] = cur;
});
dfs(0);

// 某个子树u所代表的区间：in[u], out[u] - 1;
// 某个点自己：in[u], in[u]
// 用线段树或者树状数组维护区间操作