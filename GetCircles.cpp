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

// 无向图找出所有环
    
auto get_circles([&]() {
    vector<int> st(n, 0);
    vector<int> v;
    set<vector<int>> uniqueCycles; // 使用集合来避免重复的环
    vector<vector<int>> res;

    function<void(int, int)> dfs = [&](int u, int parent) {
        st[u] = 1;
        v.push_back(u);
        for(auto [x, _] : adj[u]) {
            if(x == parent) continue; // 跳过父节点
            if(!st[x]) {
                dfs(x, u);
            } else {
                auto it = find(begin(v), end(v), x);
                if(it != v.end()) {
                    vector<int> cycle(it, end(v));
                    sort(begin(cycle), end(cycle)); // 对环进行排序
                    uniqueCycles.insert(cycle); // 添加到集合中以去重
                }
            }
        }
        v.pop_back();
        st[u] = 0; // 重置访问标记
    };

    for(int i = 0; i < n; i++) {
        if(!st[i]) {
            dfs(i, -1);
        }
    }

    for(const auto& cycle : uniqueCycles) {
        res.push_back(cycle);
    }
    return res;
});

