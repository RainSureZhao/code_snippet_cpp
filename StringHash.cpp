#define mp make_pair
typedef pair<int, int> hashv;
const int mod1 = 1000000007;
const int mod2 = 1000000009;

hashv operator + (hashv a, hashv b) {
	int c1 = a.x + b.x, c2 = a.y + b.y;
	if (c1 >= mod1) c1 -= mod1;
	if (c2 >= mod2) c2 -= mod2;
	return mp(c1, c2);
}
 
hashv operator - (hashv a, hashv b) {
	int c1 = a.x - b.x, c2 = a.y - b.y;
	if (c1 < 0) c1 += mod1;
	if (c2 < 0) c2 += mod2;
	return mp(c1, c2);
}
 
hashv operator * (hashv a, hashv b) {
	return mp(1ll * a.x * b.x % mod1, 1ll *a.y * b.y % mod2);
}

hashv pw[maxn], h[maxn];
string s;
hashv get(int l, int r)
{
    return h[r] - h[l - 1] * pw[r - l + 1];
}

// 使用方法
signed main()
{
	hashv base = mp(13331,23333);
    pw[0] = mp(1, 1);

    for(int i = 1; i <= n; i ++) { // 生成h数组
	    pw[i] = pw[i - 1] * base;
	    h[i] = h[i - 1] * base + mp(s[i], s[i]);
	}
	
}