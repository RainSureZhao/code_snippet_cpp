vector<vector<PII>> adj(m);
vector<int> st(cur + 10);
vector<int> res;
function<void(int)> dfs([&](int u) {
    for(auto &[x, id] : adj[u]) {
        if(st[id]) continue;
        st[id] = true;
        dfs(x);
    }
    res.push_back(u);
});
dfs(0);
cout << "Yes" << "\n";
for(auto x : res) {
    cout << x + 1 << ' ';
}
cout << "\n";