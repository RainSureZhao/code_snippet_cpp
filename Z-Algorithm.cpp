// 下标从0开始
auto get_z([&](const string& s) {
    int n = s.size();
    vector<int> z(n);
    int box_l = 0, box_r = 0;
    for(int i = 1; i < n; i ++) {
        if(i <= box_r) {
            z[i] = min(z[i - box_l], box_r - i + 1);
        }
        while(i + z[i] < n and s[z[i]] == s[i + z[i]]) {
            box_l = i;
            box_r = i + z[i];
            z[i] ++;
        }
    }
    return z;
});