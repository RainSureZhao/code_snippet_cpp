struct BigInt {
    vector<int> a;
    int carry = 1e9;
    BigInt() = default;
    BigInt(const string &s) {
        for(int i = static_cast<int>(s.size() - 1); i >= 0; ) {
            int len = min(9ll, i + 1);
            string t = s.substr(i - len + 1, len);
            i -= len;
            a.push_back(stoll(t));
        }
    }
    BigInt(const vector<int> &b) {
        a = b;
    }
    BigInt(int x) {
        this->a = vector<int>(1, x);
    }

    BigInt& operator=(const BigInt& other) { // 重载赋值运算符 BigInt => BigInt a = b;
        if(this != &other) {
            this->a = other.a;
        }
        return *this;
    }
    BigInt& operator=(const int x) {  // 重载赋值运算符 int => BigInt a = 100;
        this->a = vector<int>(1, x);
        return *this;
    }
    BigInt& operator=(const string &s) { // 重载赋值运算符 string => BitInt a = "123456789987654321";
        BigInt temp(s);
        *this = temp;
        return *this;
    }
    BigInt& operator=(const vector<int> &b) { // 重载赋值运算符 vector<int> => BigInt a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        this->a = b;
        return *this;
    }
    // 加法 BigInt + BigInt
    BigInt operator+(const BigInt &b) const { // 重载加法运算符 BigInt + BigInt
        BigInt res;
        int t = 0;
        for(int i = 0; i < static_cast<int>(a.size()) || i < static_cast<int>(b.a.size()); i ++) {
            if(i < static_cast<int>(a.size())) t += a[i];
            if(i < static_cast<int>(b.a.size())) t += b.a[i];
            res.a.push_back(t % carry);
            t /= carry;
        }
        if(t) res.a.push_back(1);
        return res;
    }
    // 减法 BigInt - BigInt
    BigInt operator-(const BigInt &b) const {
        BigInt res;
        int t = 0;
        for(int i = 0; i < static_cast<int>(a.size()); i ++) {
            t = a[i] - t;
            if(i < static_cast<int>(b.a.size())) t -= b.a[i];
            res.a.push_back((t + carry) % carry);
            if(t < 0) t = 1;
            else t = 0;
        }
        while(res.a.size() > 1 && res.a.back() == 0) res.a.pop_back();
        return res;
    }
    // 乘法 BigInt * BigInt
    BigInt operator*(const BigInt &c) const {
        BigInt res;
        res.a = vector<int>(a.size() + c.a.size() + 5, 0);
        for(int i = 0; i < static_cast<int>(a.size()); i ++) {
            for(int j = 0; j < static_cast<int>(c.a.size()); j ++) {
                res.a[i + j] += a[i] * c.a[j];
                res.a[i + j + 1] += res.a[i + j] / carry;
                res.a[i + j] %= carry;
            }
        }
        while(res.a.size() > 1 && res.a.back() == 0) res.a.pop_back();
        return res;
    }
    // 乘法 BigInt * int
    BigInt operator*(const int x) const {
        BigInt res;
        int t = 0;
        for(int i = 0; i < static_cast<int>(a.size()) || t; i ++) {
            if(i < static_cast<int>(a.size())) t += a[i] * x;
            res.a.push_back(t % carry);
            t /= carry;
        }
        while(res.a.size() > 1 && res.a.back() == 0) res.a.pop_back();
        return res;
    }
    // 除法
    BigInt operator/(const BigInt &other) const {
        BigInt res, cur;
        for(int i = static_cast<int>(a.size()) - 1; i >= 0; i --) {
            cur.a.insert(cur.a.begin(), a[i]);
            int l = 0, r = carry - 1;
            while(l < r) {
                int mid = (l + r + 1) >> 1;
                if(other * mid <= cur) l = mid;
                else r = mid - 1;
            }
            res.a.insert(res.a.begin(), l);
            cur = cur - other * l;
        }
        while(res.a.size() > 1 && res.a.back() == 0) res.a.pop_back();
        return res;
    }
    // 求余
    BigInt operator%(const BigInt &other) const {
        BigInt quotient = *this / other;
        BigInt remainder = *this - quotient * other;
        return remainder;
    }
    // 重载加等于运算符
    BigInt& operator+=(const BigInt &other) {
        auto tmp = *this + other;
        *this = tmp;
        return *this;
    }

    BigInt& operator-=(const BigInt &other) {
        auto tmp = *this - other;
        *this = tmp;
        return *this;
    }

    BigInt& operator*=(const BigInt &other) {
        auto tmp = *this * other;
        *this = tmp;
        return *this;
    }
    BigInt& operator*=(const int x) {
        auto tmp = *this * x;
        *this = tmp;
        return *this;
    }
    BigInt& operator/=(const BigInt &other) {
        auto tmp = *this / other;
        *this = tmp;
        return *this;
    }
    BigInt& operator%=(const BigInt &other) {
        auto tmp = *this % other;
        *this = tmp;
        return *this;
    }
    // 重载输入运算符
    friend istream& operator>>(istream& is, BigInt& obj) {
        string input;
        is >> input;
        obj = BigInt(input);
        return is;
    }

    // 重载输出运算符
    friend ostream& operator<<(ostream& os, const BigInt& obj) {
        if (obj.a.empty()) {
            os << "0";
        } else {
            for (int i = obj.a.size() - 1; i >= 0; i --) {
                if (i == obj.a.size() - 1) {
                    os << obj.a[i];
                } else {
                    // 控制输出宽度为10，并用前导零填充
                    os << setw(9) << setfill('0') << obj.a[i];
                }
            }
        }
        return os;
    }
    
    bool operator!= (const BigInt &b) const { // 重载不等于运算符 BigInt != BigInt
        return this->a != b.a;
    }
    bool operator!= (const int x) const { // 重载不等于运算符 BigInt != int
        return this->a != vector<int>(1, x);
    }
    bool operator==(const BigInt &b) const { // 重载等于运算符 BigInt == BigInt
        return this->a == b.a;
    }
    bool operator==(const int x) const { // 重载等于运算符 BigInt == int
        return this->a == vector<int>(1, x);
    }
    bool operator<(const BigInt &b) const { // 重载小于运算符 BigInt < BigInt
        if(a.size() != b.a.size()) return a.size() < b.a.size();
        for(int i = a.size() - 1; i >= 0; i --) {
            if(a[i] != b.a[i]) return a[i] < b.a[i];
        }
        return false;
    }
    bool operator<(const int x) const { // 重载小于运算符 BigInt < int
        return a < vector<int>(1, x);
    }
    bool operator>(const BigInt &b) const { // 重载大于运算符 BigInt > BigInt
        if(a.size() != b.a.size()) return a.size() > b.a.size();
        for(int i = a.size() - 1; i >= 0; i --) {
            if(a[i] != b.a[i]) return a[i] > b.a[i];
        }
        return false;
    }
    bool operator>(const int x) const { // 重载大于运算符 BigInt > int
        return a > vector<int>(1, x);
    }
    bool operator<=(const BigInt &b) const { // 重载小于等于运算符 BigInt <= BigInt
        return *this < b || *this == b;
    }
    bool operator<=(const int x) const { // 重载小于等于运算符 BigInt <= int
        return *this < x || *this == x;
    }
    bool operator>=(const BigInt &b) const { // 重载大于等于运算符 BigInt >= BigInt
        return *this > b || *this == b;
    }
    bool operator>=(const int x) const { // 重载大于等于运算符 BigInt >= int
        return *this > x || *this == x;
    }
};