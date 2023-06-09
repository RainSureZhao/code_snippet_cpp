vector<int> dfn(n + 10), low(n + 10), stk(n + 10), in_stk(n + 10), id(n + 10), dout(n + 10), sz(n + 10);
int scc_cnt = 0, timestamp = 0, top = 0;
function<void(int)> tarjan([&](int u) {
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u, in_stk[u] = 1;
    for(auto j : adj[u]){
        if(!dfn[j]){
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }else if(in_stk[j]) low[u] = min(low[u], dfn[j]);
    }
    if(low[u] == dfn[u]){
        int y;
        ++ scc_cnt;
        do{
            y = stk[top --];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt] ++;
        }while(y != u);
    }
});
// for(int i = 0; i < n; i ++) {
//     if(!dfn[i]) tarjan(i);
// }