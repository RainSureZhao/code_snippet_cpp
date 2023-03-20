typedef pair<int, int> PII;
struct info{
    int l, r;
    mutable int v;
    bool operator <(const info &x)const{
        return l < x.l;
    }
};
#define It set<info>::iterator
set<info> tr;
// ODT定义
It split(int pos){ // split函数，找到包含pos的区间，将其分割为[l, pos - 1] 和 [pos, r]
    auto it = tr.lower_bound({pos, -1, 0});
    if(it != tr.end() && it->l == pos) return it;
    --it;
    int l = it->l;
    int r = it->r;
    int v = it->v;
    tr.erase(it);
    tr.insert({l, pos - 1, v});
    return tr.insert({pos, r, v}).first;
}
// 修改操作
void emerge_add(int l, int r, int x = 1){ // 给区间[l, r]中的每个数加上x
    auto itr = split(r + 1), itl = split(l);
    for(;itl != itr; itl ++) itl->v += x;
}
void emerge_bian(int l, int r, int x = 0){ // 把区间[l, r]中的每个数都变成x
    auto itr = split(r + 1), itl = split(l);
    tr.erase(itl, itr);
    tr.insert({l, r, x});
}

// 查询操作
int get_rank(int l, int r, int k){ // 查询区间[l, r]中第k小的数
    vector<PII>v;
    auto itr = split(r + 1), itl = split(l);
    for(;itl != itr; itl ++) v.push_back({itl->v, itl->r - itl->l + 1});
    sort(v.begin(), v.end());
    for(auto [vv, len] : v){
        k -= len;
        if(k <= 0) return vv;
    }
    return 0;
}
int qmi(int a, int b, int mod)
{
    int res = 1 % mod;
    a %= b;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int get_ans(int l, int r, int x, int mod){ // 查询区间[l, r]中每个数的x次方求和模mod的值
    int ans = 0;
    auto itr = split(r + 1), itl = split(l);
    for(;itl != itr; itl ++){
        ans = (ans + ((itl->r - itl->l + 1) * qmi(itl->v, x, mod)) % mod) % mod;
    }
    return ans;
}
int get_num(int l, int r, int x) { // 查询区间[l, r]中有多少个x
    int res = 0;
    auto itr = split(r + 1), itl = split(l);
    for(; itl != itr; itl ++) {
        if(itl->v == x) res += (itl->r - itl->l + 1);
    }
    return res;
}