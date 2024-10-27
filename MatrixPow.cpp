namespace Matrix_pow {
    int mod;
    using i64 = long long;
    int norm(int x) {
        if (x < 0) x += mod;
        if (x >= mod) x -= mod;
        return x;
    }

    template<class T>
    T qpow(T a, i64 b) {
        T res = 1;
        while (b) {
            if (b & 1) res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }

    struct Mint {
        int x;
        Mint(int x = 0) : x(norm(x)) {}
        Mint(i64 x) : x(norm(x % mod)) {}
        int val() const {
            return x;
        }
        Mint operator-() const {
            return Mint(norm(mod - x));
        }
        Mint inv() const {
            // assert(x != 0);
            return qpow(*this, mod - 2);
        }
        Mint &operator*=(const Mint &rhs) {
            x = i64(x) * rhs.x % mod;
            return *this;
        }
        Mint &operator+=(const Mint &rhs) {
            x = norm(x + rhs.x);
            return *this;
        }
        Mint &operator-=(const Mint &rhs) {
            x = norm(x - rhs.x);
            return *this;
        }
        Mint &operator/=(const Mint &rhs) {
            return *this *= rhs.inv();
        }
        friend Mint operator*(const Mint &lhs, const Mint &rhs) {
            Mint res = lhs;
            res *= rhs;
            return res;
        }
        friend Mint operator+(const Mint &lhs, const Mint &rhs) {
            Mint res = lhs;
            res += rhs;
            return res;
        }
        friend Mint operator-(const Mint &lhs, const Mint &rhs) {
            Mint res = lhs;
            res -= rhs;
            return res;
        }
        friend Mint operator/(const Mint &lhs, const Mint &rhs) {
            Mint res = lhs;
            res /= rhs;
            return res;
        }
        friend istream &operator>>(istream &is, Mint &a) {
            i64 v;
            is >> v;
            a = Mint(v);
            return is;
        }
        friend ostream &operator<<(ostream &os, const Mint &a) {
            return os << a.val();
        }
    };

    struct Matrix {
        vector<vector<Mint>> v;
        int size;
        Matrix (int size = 3, int t = 0) {
            this->size = size;
            v = vector<vector<Mint>>(size, vector<Mint>(size));
            for(int i = 0; i < size; i ++) v[i][i] = t;
        }
        Matrix operator*(const Matrix& b) const {
            Matrix res(this->size);
            for (int k = 0; k < size; k++)
                for (int i = 0; i < size; i++)
                    for (int j = 0; j < size; j++)
                        res.v[i][j] += this->v[i][k] * b.v[k][j];
            return res;
        }
        Matrix operator^(int b) {
            Matrix res(this->size, 1), a = *this;
            while (b) {
                if (b & 1) res = res * a;
                a = a * a;
                b >>= 1;
            }
            return res;
        }
    };
}

// example
Matrix_pow::mod = 1e9 + 7;
Matrix f(26), A(26);
for(int i = 0; i < 26; i ++) {
    f.v[0][i] = 1;
}
for(int i = 0; i < 26; i ++) {
    for(int j = 1; j <= nums[i]; j ++) {
        A.v[(i + j) % 26][i] = 1;
    }
}
auto ans = f * (A ^ t);
