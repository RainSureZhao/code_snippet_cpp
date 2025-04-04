struct KMP { // 下标从1开始
    vector<int> ne;
    string s;
    int n;
    KMP(string S) : s(S), n(S.size()) {
        ne.resize(n + 1);
        s = ' ' + s;
        for(int i = 2, j = 0; i <= n; i ++) {
            while(j && s[i] != s[j + 1]) j = ne[j];
            if(s[i] == s[j + 1]) j ++;
            ne[i] = j;
        }
    }
    vector<int> match(string t) { // 返回t中所有s的出现位置，下标从1开始
        if(n == 0) {
            vector<int> res;
            for(int i = 0; i < t.size() + 1; i ++) res.push_back(i + 1);
            return res;
        }
        vector<int> res;
        t = ' ' + t;
        int m = t.size() - 1;
        for(int i = 1, j = 0; i <= m; i ++) {
            while(j && t[i] != s[j + 1]) j = ne[j];
            if(t[i] == s[j + 1]) j ++;
            if(j == n) {
                res.push_back(i - n + 1);
                j = ne[j];
            }
        }
        return res;
    }
};