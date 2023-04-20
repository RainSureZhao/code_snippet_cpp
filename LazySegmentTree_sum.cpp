// 线段树求区间和模板，区间修改(区间加一个数)，区间查询
const int maxn = 100010;
typedef struct node
{
    int l, r;
    int sum, lazy;
}Node;
Node tr[maxn * 4];
void pushup(Node &u, Node &l, Node &r)
{
    u.sum = l.sum + r.sum;
}
void pushup(int u)
{
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}
void build(int u, int l, int r)
{
    if(l == r) {
        tr[u] = {l, l, 0, 0};
    } else {
        tr[u] = {l, r};
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
void pushdown(Node &u, Node &l, Node &r)
{
    if(u.lazy) {
        l.sum += (l.r - l.l + 1) * u.lazy, l.lazy += u.lazy;
        r.sum += (r.r - r.l + 1) * u.lazy, r.lazy += u.lazy;
        u.lazy = 0;
    }
}
void pushdown(int u)
{
    pushdown(tr[u], tr[u << 1], tr[u << 1 | 1]);
}
void modify(int u, int l, int r, int v)
{
    if(tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum += (tr[u].r - tr[u].l + 1) * v;
        tr[u].lazy += v;
    } else {
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(r <= mid) modify(u << 1, l, r, v);
        else if(l > mid) modify(u << 1 | 1, l, r, v);
        else {
            modify(u << 1, l, r, v);
            modify(u << 1 | 1, l, r, v);
        }
        pushup(u);
    }
}
int query(int u, int l, int r)
{
    if(tr[u].l >= l and tr[u].r <= r) return tr[u].sum;
    else {
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(r <= mid) return query(u << 1, l, r);
        else if(l > mid) return query(u << 1 | 1, l, r);
        else{
            int res = 0;
            res += query(u << 1, l, r);
            res += query(u << 1 | 1, l, r);
            return res;
        }
    }
}