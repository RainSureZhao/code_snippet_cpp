const int MOD = 10; // 对10求mod，10不是质数，需要用欧拉定理算出来 x^{phi(mod) - 1}
const int MX = 100'000;
array<int, MX + 1> f, inv_f, p2, p5;

int qpow(int x, int n) {
    int res = 1;
    while (n > 0) {
        if (n % 2 > 0) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
        n /= 2;
    }
    return res;
}

auto init = []() {
    f[0] = 1;
    for (int i = 1; i <= MX; i++) {
        int x = i;
        // 计算 2 的幂次
        int e2 = countr_zero((unsigned) x);
        x >>= e2;
        // 计算 5 的幂次
        int e5 = 0;
        while (x % 5 == 0) {
            e5++;
            x /= 5;
        }
        f[i] = f[i - 1] * x % MOD;
        p2[i] = p2[i - 1] + e2;
        p5[i] = p5[i - 1] + e5;
    }

    inv_f[MX] = qpow(f[MX], 3); // 欧拉定理求逆元
    for (int i = MX; i > 0; i--) {
        int x = i;
        x >>= countr_zero((unsigned) x);
        while (x % 5 == 0) {
            x /= 5;
        }
        inv_f[i - 1] = inv_f[i] * x % MOD;
    }
    return 0;
}();

int comb(int n, int k) {
    // 由于每项都 < 10，所以无需中途取模
    return f[n] * inv_f[k] * inv_f[n - k] *
           qpow(2, p2[n] - p2[k] - p2[n - k]) *
           qpow(5, p5[n] - p5[k] - p5[n - k]) % MOD;
}

// https://leetcode.cn/problems/check-if-digits-are-equal-in-string-after-operations-ii/