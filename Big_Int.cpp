struct Big_Int
{
    vector<int> a;
    int carry = 1e10;
    void init(string s){  // 传入字符串初始化
        for(int i = s.size() - 1; i >= 0; ) {
            int len = min(10ll, i + 1);
            string t = s.substr(i - len + 1, len);
            i -= len;
            a.push_back(stoll(t));
        }
    }
    void init(vector<int> b) // 赋值
    {
        a = b;
    }
    void init(int b)
    {
        vector<int> B; B.push_back(b);
        init(B);
    }
    vector<int> add(vector<int> B)  // 加一个大数
    {
        int t = 0;
        vector<int> res;
        for(int i = 0; i < a.size() || i < B.size(); i ++){
            if(i < a.size()) t += a[i];
            if(i < B.size()) t += B[i];
            res.push_back(t % carry);
            t /= carry;
        }
        if(t) res.push_back(1);
        a = res;
        return res;
    }
    vector<int> addc(int b)  // 加一个小数
    {
        int t = 0;
        vector<int> res;
        vector<int> B; B.push_back(b);
        for(int i = 0; i < a.size() || i < B.size(); i ++){
            if(i < a.size()) t += a[i];
            if(i < B.size()) t += B[i];
            res.push_back(t % carry);
            t /= carry;
        }
        if(t) res.push_back(1);
        return a = res;
    }
    vector<int> sub(vector<int> B)  // 减一个大数
    {   
        int t = 0;
        vector<int> res;
        for(int i = 0; i < a.size(); i ++){
            t = a[i] - t;
            if(i < B.size()) t -= B[i];
            res.push_back((t + carry) % carry);
            if(t < 0) t = 1;
            else t = 0;
        }
        while(res.size() > 1 && res.back() == 0) res.pop_back();
        return a = res;
    }
    vector<int> subc(int b) // 减一个小数
    {
        int t = 0;
        vector<int> B; B.push_back(b);
        vector<int> res;
        for(int i = 0; i < a.size(); i ++){
            t = a[i] - t;
            if(i < B.size()) t -= B[i];
            res.push_back((t + carry) % carry);
            if(t < 0) t = 1;
            else t = 0;
        }
        while(res.size() > 1 && res.back() == 0) res.pop_back();
        return a = res;
    }
    vector<int> mulc(int b) // 乘一个小数
    {
        int t = 0;
        vector<int> res;
        for(int i = 0; i < a.size() || t; i ++){
            if(i < a.size()) t += a[i] * b;
            res.push_back(t % carry);
            t /= carry;
        }
        while(res.size() > 1 && res.back() == 0) res.pop_back();
        return a = res;
    }
    vector<int> mul(vector<int> B) // 乘一个大数，可以用fft
    {
        vector<int> res(a.size() + B.size() + 5, 0);
        for(int i = 0; i < a.size(); i ++){
            for(int j = 0; j < B.size(); j ++){
                res[i + j] += a[i] * B[j];
                res[i + j + 1] += res[i + j] / carry;
                res[i + j] %= carry;
            }
        }
        while(res.size() > 1 && res.back() == 0) res.pop_back();
        return a = res;
    }
    vector<int> div(int b) // 除一个小数，不要余数
    {
        vector<int> res;
        int r = 0;
        for(int i = a.size() - 1; i >= 0; i --) {
            r = r * carry + a[i];
            res.push_back(r / b);
            r %= b;
        }
        reverse(res.begin(), res.end());
        while(res.size() > 1 && res.back() == 0) res.pop_back();
        return a = res;
    }
    vector<int> divr(int b, int &r) // 除一个小数，要余数
    {
        vector<int> res;
        r = 0;
        for(int i = a.size() - 1; i >= 0; i --) {
            r = r * carry + a[i];
            res.push_back(r / b);
            r %= b;
        }
        reverse(res.begin(), res.end());
        while(res.size() > 1 && res.back() == 0) res.pop_back();
        return a = res;
    }
    bool cmp(vector<int> &B) // 比较大小
    {
        if(a.size() != B.size()) return a.size() > B.size();
        for(int i = a.size() - 1; i >= 0; i --){
            if(a[i] != B[i]) return a[i] > B[i];
        }
        return true;
    }
    void output()
    {
        printf("%lld", a[a.size() - 1]);
        for(int i = a.size() - 2; i >= 0; i --) {
            printf("%010lld", a[i]);
        }
        puts(""); // 输出一个回车
    }
};