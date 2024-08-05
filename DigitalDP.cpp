// 求[0,n]中的二进制表示中不包含连续1的个数
// 
int m = __lg(n);
vector f(m + 1, vector<vector<int>>(2, vector<int>(2, -1)));
function<int(int, int, int)> dfs([&](int u, int pre1, int isLimit) {
    if(u < 0) return 1;
    if(!isLimit and f[u][pre1][isLimit] != -1) {
        return f[u][pre1][isLimit];
    }
    int up = isLimit ? n >> u & 1 : 1;
    int res = dfs(u - 1, 0, isLimit && up == 0); // 填0
    if(!pre1 and up == 1) { // 可以填1
        res += dfs(u - 1, 1, isLimit); // 可以填0
    }
    f[u][pre1][isLimit] = res;
    return res;
});
return dfs(m, 0, 1);

// [1,n]中具有至少1位重复数字的个数
// https://leetcode.cn/problems/numbers-with-repeated-digits/description/
auto s = to_string(x);
int n = s.size();
vector memo(n, vector<int>(1 << 10, -1));
function<int(int, int, bool, bool)> dfs([&](int i, int mask, bool is_limit, bool is_num) -> int{
    if(i == n) return is_num;
    if(!is_limit and is_num and memo[i][mask] != -1) return memo[i][mask];
    int res = 0;
    if(!is_num) res = dfs(i + 1, mask, false, false);
    int up = is_limit ? s[i] - '0' : 9;
    for(int d = 1 - is_num; d <= up; d ++) {
        if(!(mask >> d & 1)) {
            res += dfs(i + 1, mask | (1 << d), is_limit and d == up, true);
        }
    }
    if(!is_limit and is_num) {
        memo[i][mask] = res;
    }
    return res;
});

return x - dfs(0, 0, true, false);

// [0,n]中数字2出现的次数
// https://leetcode.cn/problems/number-of-2s-in-range-lcci/description/
auto s = to_string(x);
int n = s.size();
vector f(n, vector<vector<int>>(n, vector<int>(2, -1)));
function<int(int, int, int)> dfs([&](int u, int cnt2, int isLimit) {
    if(u == n) return cnt2;
    if(f[u][cnt2][isLimit] != -1) {
        return f[u][cnt2][isLimit];
    }
    auto &res = f[u][cnt2][isLimit];
    res = 0;
    // 枚举这一位填入的数字
    for(int d = 0, up = isLimit ? s[u] - '0' : 9; d <= up; d ++) {
        res += dfs(u + 1, cnt2 + (d == 2), isLimit and d == up);
    }
    return res;
});
return dfs(0, 0, 1);

// [0, 10^n]中各位数字都不相同的个数
// https://leetcode.cn/problems/count-numbers-with-unique-digits/description/
vector f(n, vector<vector<vector<int>>>(1 << 10, vector<vector<int>>(2, vector<int>(2, -1))));
function<int(int, int, int, int)> dfs([&](int u, int mask, int isLimit, int isNum) {
    if(u == n) {
        return isNum;
    }
    if(f[u][mask][isLimit][isNum] != -1) {
        return f[u][mask][isLimit][isNum];
    }
    auto &res = f[u][mask][isLimit][isNum];
    res = 0;
    if(!isNum) res = dfs(u + 1, mask, 0, 0);
    for(int d = 1 - isNum, up = 9; d <= up; d ++) {
        if(mask >> d & 1) continue;
        res += dfs(u + 1, mask | (1 << d), isLimit and d == 9, 1);
    }
    return res;
});
return dfs(0, 0, 1, 0) + 1;