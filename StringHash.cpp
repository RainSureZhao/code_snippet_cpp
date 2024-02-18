// #define mp make_pair
// typedef pair<int, int> hashv;
// const int mod1 = 1000000007;
// const int mod2 = 1000000009;

// hashv operator + (hashv a, hashv b) {
// 	int c1 = a.x + b.x, c2 = a.y + b.y;
// 	if (c1 >= mod1) c1 -= mod1;
// 	if (c2 >= mod2) c2 -= mod2;
// 	return mp(c1, c2);
// }
 
// hashv operator - (hashv a, hashv b) {
// 	int c1 = a.x - b.x, c2 = a.y - b.y;
// 	if (c1 < 0) c1 += mod1;
// 	if (c2 < 0) c2 += mod2;
// 	return mp(c1, c2);
// }
 
// hashv operator * (hashv a, hashv b) {
// 	return mp(1ll * a.x * b.x % mod1, 1ll *a.y * b.y % mod2);
// }

// hashv pw[maxn], h[maxn];
// string s;
// hashv get(int l, int r)
// {
//     return h[r] - h[l - 1] * pw[r - l + 1];
// }

// // 使用方法
// signed main()
// {
// 	hashv base = mp(13331,23333);
//     pw[0] = mp(1, 1);

//     for(int i = 1; i <= n; i ++) { // 生成h数组
// 	    pw[i] = pw[i - 1] * base;
// 	    h[i] = h[i - 1] * base + mp(s[i], s[i]);
// 	}
	
// }


class Hashv {
public:
    const static int mod1 = 1000000007;
    const static int mod2 = 1000000009;
    Hashv() = default;
    Hashv(int first, int second) : val(first, second) {}
    Hashv(const std::pair<int, int>& val) : val(val) {}

    bool operator==(const Hashv &rhs) const {
        return val == rhs.val;
    }

    bool operator!=(const Hashv &rhs) const {
        return val != rhs.val;
    }

    bool operator<(const Hashv &rhs) const {
        return val < rhs.val;
    }

    bool operator<=(const Hashv &rhs) const {
        return val <= rhs.val;
    }

    bool operator>(const Hashv &rhs) const {
        return val > rhs.val;
    }

    bool operator>=(const Hashv &rhs) const {
        return val >= rhs.val;
    }

    friend ostream& operator<<(ostream &os, const Hashv& v) {
        os << v.val.first << ' ' << v.val.second << "\n";
        return os; 
    }
    friend Hashv operator+(const Hashv &a, const Hashv& b) {
        int c1 = a.val.first + b.val.first, c2 = a.val.second + b.val.second;
        if (c1 >= Hashv::mod1) c1 -= Hashv::mod1;
        if (c2 >= Hashv::mod2) c2 -= Hashv::mod2;
        return Hashv(c1, c2);
    }

    friend Hashv operator-(const Hashv &a, const Hashv &b) {
        int c1 = a.val.first - b.val.first, c2 = a.val.second - b.val.second;
        if (c1 < 0) c1 += Hashv::mod1;
        if (c2 < 0) c2 += Hashv::mod2;
        return Hashv(c1, c2);
    }

    friend Hashv operator*(const Hashv &a, const Hashv& b) {
        return Hashv(1ll * a.val.first * b.val.first % Hashv::mod1, 1ll * a.val.second * b.val.second % Hashv::mod2);
    }

    int First() const {
        return val.first;
    }
    int Second() const {
        return val.second;
    }
private:
    std::pair<int, int> val;
};

namespace std {
    template<>
    struct hash<Hashv> {
        std::size_t operator()(const Hashv& h) const noexcept {
            std::size_t h1 = std::hash<int>{}(h.First());
            std::size_t h2 = std::hash<int>{}(h.Second());
            return h1 ^ (h2 << 1);
        }
    };
}



struct StringHash {
public:
    const Hashv base;
    StringHash(const string &s) : base(13331, 23333), s(s) {
        int n = s.size();
        h.resize(n + 1);
        p.resize(n + 1);
        p[0] = Hashv(1, 1);
        for(int i = 1; i <= n; i ++) {
            h[i] = h[i - 1] * base + Hashv(s[i - 1], s[i - 1]);
            p[i] = p[i - 1] * base;
        }
    }
    Hashv get(int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    }
private:
    std::string s;
    std::vector<Hashv> h, p;
};