struct Node{
    int son[26] = {0}; // 26个字母
    int end = 0; // 字符串结尾标记，同时用于统计个数
    int fail = 0; // fail指针
};
vector<Node> tr(n * 26 + 10); // AC自动机, n是字符串的数量
int idx = 0;
auto insert([&](const string& s) { // 插入字符串s
    int now = 0;
    for(int i = 0; i < s.size(); i ++) {
        int ch = s[i] - 'a';
        if(tr[now].son[ch] == 0) {
            tr[now].son[ch] = ++ idx;
        }
        now = tr[now].son[ch];
    }
    tr[now].end ++;
});
auto getFail([&]() { // 用BFS构建每个节点的Fail指针
    queue<int> q;
    for(int i = 0; i < 26; i ++) { // 把第一层入队，即root的子节点
        if(tr[0].son[i]) { // 如果这个位置有字符
            q.push(tr[0].son[i]);
        }
    }
    while(q.size()) {
        auto now = q.front();
        q.pop();
        for(int i = 0; i < 26; i ++) {
            if(tr[now].son[i]) {
                tr[tr[now].son[i]].fail = tr[tr[now].fail].son[i]; // 这个孩子的Fail = 父节点的Fail指针所指向的节点的与x相同字符的子节点
                q.push(tr[now].son[i]);
            }else {
                tr[now].son[i] = tr[tr[now].fail].son[i];
            }
        }
    }
});
auto query([&](const string& s) { // 查询字符串s中存在多少个模式串
    int res = 0;
    int now = 0;
    for(int i = 0; i < s.size(); i ++) {
        int ch = s[i] - 'a';
        now = tr[now].son[ch];
        int tmp = now;
        while(tmp and tr[tmp].end != -1) {
            res += tr[tmp].end;
            tr[tmp].end = -1;
            tmp = tr[tmp].fail;
        }
    }
    return res;
});
for(int i = 0; i < n; i ++) { // 插入字符串
    string s;
    cin >> s;
    insert(s);
}
getFail();