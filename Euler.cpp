vector<int> st(1e6 + 10);
vector<int> primes; // 质数
vector<int> p(1e6 + 10); // p[i] = i的最小质因子
vector<int> q(1e6 + 10); // q[i] = i的最小质因子的幂次
vector<int> d(1e6 + 10); // d[i] = i的约数个数
vector<int> phi(1e6 + 10);   // phi[i] = i的欧拉函数

auto init([&](int n) {
    st[1] = d[1] = 1;
    for(int i = 2; i <= n; i ++) {
        if(!st[i]) {
            primes.push_back(i);
            p[i] = i;
            d[i] = 2;
            q[i] = 1;
            phi[i] = i - 1;
        }
        for(int j = 0; j < primes.size() and primes[j] <= n / i; j ++) {
            st[primes[j] * i] = 1;
            p[i * primes[j]] = primes[j];
            if(i % primes[j] == 0) {
                d[i * primes[j]] = d[i] / (q[i] + 1) * (q[i] + 2);
                q[i * primes[j]] = q[i] + 1;
                phi[i * primes[j]] = primes[j] * phi[i];
                break;
            }
            d[i * primes[j]] = d[i] * d[primes[j]];
            q[i * primes[j]] = 1;
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
});


// 分解质因数求欧拉函数
auto get_euler([&](int x){
    int res = x;
    for(int i = 2; i <= x / i; i ++) {
        if(x % i == 0) {
            res = res / i * (i - 1);
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) res = res / x * (x - 1);
    return res;
});


// 欧拉降幂 // 求a^b % mod
class Solution {
public:
    int superPow(int a, vector<int>& b) {
        auto get_euler([&](int x){
            long long res = x;
            for(int i = 2; i <= x / i; i ++) {
                if(x % i == 0) {
                    res = res / i * (i - 1);
                    while(x % i == 0) x /= i;
                }
            }
            if(x > 1) res = res / x * (x - 1);
            return res;
        });
        auto qmi([&](long long a, long long b, int mod) {
            long long res = 1 % mod;
            while(b) {
                if(b & 1) res = res * a % mod;
                b >>= 1;
                a = a * a % mod;
            }
            return res;
        });
        auto phi = get_euler(1337);
        int r = 0;
        for(auto x : b) {
            r = (1ll * r * 10 + x) % phi;
        }
        return qmi(a, r + phi, 1337);
    }
};
