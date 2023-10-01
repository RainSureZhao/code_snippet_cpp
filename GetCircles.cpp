// 有向图找出所有环

auto get_circles([&]() {
    vector<int> st(n);
    vector<int> v;
    vector<vector<int>> res;
    function<void(int)> dfs([&](int u) {
        st[u] = 1;
        v.push_back(u);
        for(auto x : adj[u]) {
            if(!st[x]) dfs(x);
            else {
                auto it = find(begin(v), end(v), x);
                if(it != v.end()) {
                    vector<int> tmp;
                    for(auto i = it; i != v.end(); i ++) {
                        tmp.push_back(*i);
                    }
                    res.push_back(tmp);
                }
            }
        }
        v.pop_back();
    });
    for(int i = 0; i < n; i ++) {
        if(!st[i]) dfs(i);
    }
    return res;
});