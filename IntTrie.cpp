class trie {
    int son[3200010][2];
    int cnt[3200010];
    int id;
public:
    trie() {
        memset(son, 0, sizeof son);
        memset(cnt, 0, sizeof cnt);
        id = 0;
    }
    void insert(int x, int c) {
        int p = 0;
        for(int i = 30; i >= 0; i --) {
            int v = x >> i & 1;
            if(!son[p][v]) son[p][v] = ++ id;
            p = son[p][v];
            cnt[p] += c;
        }
    }
    int get_max_xor_val(int x) {
        int p = 0;
        int res = 0;
        for(int i = 30; i >= 0; i --) {
            int v = x >> i & 1;
            if(cnt[son[p][!v]]) {
                res += 1 << i;
                p = son[p][!v];
            }else p = son[p][v];
        }
        return res;
    }
};

vector<vector<int>> son(n * 32 + 10, vector<int>(2));
vector<int> cnt(n * 32 + 10);
int id;

// 多组测试数据时记得清空
son[0][0] = son[0][1] = 0;


auto insert([&](int x, int c) {
    int p = 0;
    for(int i = 30; i >= 0; i --) {
        int v = x >> i & 1;
        if(!son[p][v]) {
            son[p][v] = ++ id;
            cnt[son[p][v]] = 0;
            // son[idx][0] = son[idx][1] = 0;
            // val[idx] = 0;
        }
        p = son[p][v];
        cnt[p] += c;
    }
});

auto qry_max([&](int x) {
    int res = 0;
    int p = 0;
    for(int i = 19; i >= 0; i --) {
        int y = x >> i & 1;
        if(son[p][!y]) {
            res += (1 << i);
            p = son[p][!y];
        } else if(son[p][y]) {
            p = son[p][y];
        } else break;
    }
    return res;
});
auto qry_min([&](int x) {
    int res = 0;
    int p = 0;
    for(int i = 19; i >= 0; i --) {
        int y = x >> i & 1;
        if(son[p][y]) {
            p = son[p][y];
        } else if(son[p][!y]) {
            res += (1 << i);
            p = son[p][!y];
        } else break;
    }
    return res;
});