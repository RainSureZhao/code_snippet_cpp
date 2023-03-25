namespace BM
{
    const int N = 1e3+5;
    long long res[N], base[N], _c[N], _md[N];
    vector<int> Md;
    void mul(long long *a, long long *b, int k)
    {
        for (int i = 0; i < k + k; i++) _c[i] = 0;
        for (int i = 0; i < k; i++) if (a[i])
            for (int j = 0; j < k; j++)
                _c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
        for (int i = k + k - 1; i >= k; i --) if (_c[i])
            for (int j = 0; j < Md.size(); j++)
                _c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
        for (int i = 0; i < k; i++)
            a[i] = _c[i];
    }
    int solve(long long n, vector<int> a, vector<int> b) // a 系数 b 初值 b[n+1]=a[0]*b[n]+...
    {
        long long ans = 0, pnt = 0;
        int k = a.size();
        for (int i = 0; i < k; i ++) _md[k - 1 - i] = -a[i];
        _md[k] = 1;
        Md.clear();
        for (int i = 0; i < k; i++) if (_md[i] != 0)
            Md.push_back(i);
        for (int i = 0; i < k; i++) res[i] = base[i] = 0;
        res[0] = 1;
        while((1ll << pnt) <= n) pnt++;
        for (int p = pnt; p >= 0; p--)
        {
            mul(res, res, k);
            if ((n >> p) & 1)
            {
                for (int i = k - 1; i >= 0; i--)
                    res[i+1] = res[i]; 
                res[0] = 0;
                for (int j = 0; j < Md.size(); j++)
                    res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
            }
        }
        for (int i = 0; i < k; i++) ans = (ans + res[i] * b[i]) % mod;
        if (ans < 0) ans += mod;
        return ans;
    }
    vector<int> CalBM(vector<int> s)
    {
        vector<int> C(1, 1), B(1, 1);
        int L = 0, m = 1, b = 1;
        for (int n = 0; n < s.size(); n++)
        {
            long long d = 0;
            for (int i = 0; i <= L; i++)
                d = (d + 1ll * C[i] * s[n-i]) % mod;
            if (d == 0) m ++;
            else if (L<<1 <= n)
            {
                vector<int> T = C;
                long long c = mod - d * qmi(b, mod - 2) % mod;
                while(C.size() < B.size() + m) C.push_back(0);
                for (int i = 0; i < B.size(); i++)
                    C[i + m] = (C[i + m] + c * B[i]) % mod;
                L = n + 1 - L; B = T; b = d; m = 1;
            }
            else
            {
                long long c = mod - d * qmi(b, mod - 2) % mod;
                while(C.size() < B.size() + m) C.push_back(0);
                for (int i = 0; i < B.size(); i++)
                    C[i + m] = (C[i + m] + c * B[i]) % mod;
                m ++;
            }
        }
        return C;
    }
    int giao(vector<int> a, long long n) // 一般a传入前阶数 * 2 + 1项，然后求出线性递推式的第n项
    {
        vector<int> c = CalBM(a);
        c.erase(c.begin());
        for (int i = 0; i < c.size(); i ++) c[i] = (mod - c[i]) % mod;
        return solve(n, c, vector<int>(a.begin(), a.begin() + c.size()));
    }
}
// cout << BM::giao(a, n - 1) << "\n";