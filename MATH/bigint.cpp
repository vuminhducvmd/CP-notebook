#include <bits/stdc++.h>
using namespace std;
  
typedef long long ll;
typedef vector<ll> vll;

const int BASE_DIGITS = 9;
const int BASE = 1000000000;

struct BigInt {
    int sign;
    vector<int> a;

    // -------------------- Constructors -------------------- 
    BigInt() : sign(1) {}
	BigInt(long long v) { *this = v; }
    
    BigInt& operator = (long long v) {
        sign = 1;
        if (v < 0) {
            sign = -1;
            v = -v;
        }
        a.clear();
        for (; v > 0; v /= BASE) {
            a.push_back(v % BASE);
        }
        return *this;
    }

    BigInt(const string& s) { read(s); }

    // -------------------- Input / Output --------------------
    void read(const string& s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -sign;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            for (int j = max(pos, i - BASE_DIGITS + 1); j <= i; j++) {
                x = x * 10 + s[j] - '0';
            }
            a.push_back(x);
        }
        trim();
    }
    
    friend istream& operator>>(istream &stream, BigInt &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream& operator<<(ostream &stream, const BigInt &v) {
        if (v.sign == -1 && !v.isZero()) stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; --i) {
            stream << setw(BASE_DIGITS) << setfill('0') << v.a[i];
        }
        return stream;
    }

    // -------------------- Comparison --------------------
    bool operator<(const BigInt &v) const {
        if (sign != v.sign) return sign < v.sign;
        if (a.size() != v.a.size()) return a.size() * sign < v.a.size() * v.sign;
        for (int i = ((int) a.size()) - 1; i >= 0; i--) {
            if (a[i] != v.a[i]) return a[i] * sign < v.a[i] * sign;
		}
        return false;
    }

    bool operator>(const BigInt &v) const { return v < *this; }
    bool operator<=(const BigInt &v) const { return !(v < *this); }
    bool operator>=(const BigInt &v) const { return !(*this < v); }
    bool operator==(const BigInt &v) const { return !(*this < v) && !(v < *this); }
    bool operator!=(const BigInt &v) const { return *this < v || v < *this; }

    // Returns:
    // 0 if |x| == |y|
    // -1 if |x| < |y|
    // 1 if |x| > |y|
    friend int __compare_abs(const BigInt& x, const BigInt& y) {
        if (x.a.size() != y.a.size()) {
            return x.a.size() < y.a.size() ? -1 : 1;
        }

        for (int i = ((int) x.a.size()) - 1; i >= 0; --i) {
            if (x.a[i] != y.a[i]) {
                return x.a[i] < y.a[i] ? -1 : 1;
            }
        }
        return 0;
    }

    // -------------------- Unary operator - and operators +- --------------------
    BigInt operator-() const {
        BigInt res = *this;
        if (isZero()) return res;
        res.sign = -sign;
        return res;
    }

    // Note: sign ignored.
    void __internal_add(const BigInt& v) {
        if (a.size() < v.a.size()) a.resize(v.a.size(), 0);
        for (int i = 0, carry = 0; i < max(a.size(), v.a.size()) || carry; ++i) {
            if (i == (int) a.size()) a.push_back(0);
            a[i] += carry + (i < v.a.size() ? v.a[i] : 0);
            carry = a[i] >= BASE;
            if (carry) a[i] -= BASE;
        }
    }

    // Note: sign ignored.
    void __internal_sub(const BigInt& v) {
        for (int i = 0, carry = 0; i < v.a.size() || carry; ++i) {
            a[i] -= carry + (i < v.a.size() ? v.a[i] : 0);
            carry = a[i] < 0;
            if (carry) a[i] += BASE;
        }
        this->trim();
    }

    BigInt operator += (const BigInt& v) {
        if (sign == v.sign) __internal_add(v);
		else {
            if (__compare_abs(*this, v) >= 0) __internal_sub(v);
			else {
                BigInt vv = v;
                swap(*this, vv);
                __internal_sub(vv);
            }
        }
        return *this;
    }

    BigInt operator -= (const BigInt& v) {
        if (sign == v.sign) {
            if (__compare_abs(*this, v) >= 0) __internal_sub(v);
			else {
                BigInt vv = v;
                swap(*this, vv);
                __internal_sub(vv);
                this->sign = -this->sign;
            }
        } 
		else __internal_add(v);
        return *this;
    }
    
    BigInt operator + (const BigInt &v) {
    	BigInt res = *this;
    	res += v;
    	return res;
	}
	
	BigInt operator - (const BigInt &v) {
		BigInt res = *this;
		res -= v;
		return res;
	}

    // -------------------- Operators * / % --------------------
    friend pair<BigInt, BigInt> divmod(const BigInt& a1, const BigInt& b1) {
        assert(b1 > 0);  // divmod not well-defined for b < 0.

        long long norm = BASE / (b1.a.back() + 1);
        BigInt a = a1.abs() * norm;
        BigInt b = b1.abs() * norm;
        BigInt q = 0, r = 0;
        q.a.resize(a.a.size());

        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= BASE;
            r += a.a[i];
            long long s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            long long s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            long long d = ((long long) BASE * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0) {
                r += b, --d;
            }
            q.a[i] = d;
        }

        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        auto res = make_pair(q, r / norm);
        if (res.second < 0) res.second += b1;
        return res;
    }
    
    BigInt operator/(const BigInt &v) const { return divmod(*this, v).first; }
    BigInt operator%(const BigInt &v) const { return divmod(*this, v).second; }

    void operator/=(int v) {
        assert(v > 0);  // operator / not well-defined for v <= 0.
        if (llabs(v) >= BASE) {
            *this /= BigInt(v);
            return ;
        }
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
            long long cur = a[i] + rem * (long long) BASE;
            a[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
    }

    BigInt operator/(int v) const {
        assert(v > 0);  // operator / not well-defined for v <= 0.

        if (llabs(v) >= BASE) return *this / BigInt(v);
        BigInt res = *this;
        res /= v;
        return res;
    }
    
    void operator/=(const BigInt &v) { *this = *this / v; }

    long long operator%(long long v) const {
        assert(v > 0);  // operator / not well-defined for v <= 0.
        assert(v < BASE);
        int m = 0;
        for (int i = a.size() - 1; i >= 0; --i) {
            m = (a[i] + m * (long long) BASE) % v;
        }
        return m * sign;
    }

    void operator*=(int v) {
        if (llabs(v) >= BASE) {
            *this *= BigInt(v);
            return ;
        }
        if (v < 0) sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
            if (i == (int) a.size()) a.push_back(0);
            long long cur = a[i] * (long long) v + carry;
            carry = (int) (cur / BASE);
            a[i] = (int) (cur % BASE);
        }
        trim();
    }

    BigInt operator*(int v) const {
        if (llabs(v) >= BASE) return *this * BigInt(v);
        BigInt res = *this;
        res *= v;
        return res;
    }

    BigInt mul_simple(const BigInt &v) const {
        BigInt res;
        res.sign = sign * v.sign;
        res.a.resize(a.size() + v.a.size());
        for (int i = 0; i < (int) a.size(); ++i) {
            if (a[i]) {
                for (int j = 0, carry = 0; j < v.a.size() || carry; ++j) {
                    long long cur = res.a[i + j] + (long long) a[i] * (j < v.a.size() ? v.a[j] : 0) + carry;
                    carry = (int) (cur / BASE);
                    res.a[i + j] = (int) (cur % BASE);
                }
            }
        }
        res.trim();
        return res;
    }

    void operator*=(const BigInt &v) { *this = *this * v; }
    BigInt operator*(const BigInt &v) const { return mul_simple(v); }

    // -------------------- Misc --------------------
    BigInt abs() const {
        BigInt res = *this;
        res.sign *= res.sign;
        return res;
    }
    
    void trim() {
        while (!a.empty() && !a.back()) a.pop_back();
        if (a.empty()) sign = 1;
    }

    bool isZero() const { return a.empty() || (a.size() == 1 && !a[0]); }
};

signed main() {
	BigInt a(200), b(30);
	cout << a / b << " " << a * b << " " << a + b << " " << a - b;
}
