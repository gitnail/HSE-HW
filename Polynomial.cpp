#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
class Polynomial {
 private:
    vector<T> data;

    static void relax(Polynomial& p) {
        while (!p.data.empty() && *p.data.rbegin() == 0) p.data.pop_back();
    }

 public:
    Polynomial() {}

    Polynomial(const vector<T>& other) : data(other) {
        relax(*this);
    }

    Polynomial(const T& k) {
        if (k != 0) data = {k};
    }

    template<typename It>
    Polynomial(It first, It last) {
        copy(first, last, back_inserter(data));
        relax(*this);
    }

    bool operator == (const Polynomial& p) const {
        return data == p.data;
    }

    bool operator != (const Polynomial& p) const {
        return !(*this == p);
    }

    bool operator == (const T& d) const {
        return  *this == Polynomial<T>(d);
    }

    bool operator != (const T& d) const {
        return !(*this == d);
    }

    Polynomial& operator += (const Polynomial& p) {
        auto& a = data;
        auto& b = p.data;
        while (a.size() < b.size()) a.push_back(0);
        for (size_t i = 0; i != min(a.size(), b.size()); ++i) {
            a[i] += b[i];
        }
        relax(*this);
        return *this;
    }

    Polynomial operator + (const Polynomial& p) const {
        auto res = *this;
        return res += p;
    }

    Polynomial& operator += (const T& d) {
        return *this += Polynomial<T>(d);
    }

    Polynomial operator + (const T& d) const {
        auto res = *this;
        return res += d;
    }

    Polynomial operator - (Polynomial p) const {
        for (auto& val : p.data) {
            val = -val;
        }
        return *this + p;
    }

    Polynomial& operator -= (const Polynomial& p) {
        return *this = *this - p;
    }

    Polynomial operator - (const T& d) const {
        return *this - Polynomial<T>(d);
    }

    Polynomial& operator -= (const T& d) {
        return *this = *this - d;
    }

    Polynomial operator * (const Polynomial& p) const {
        Polynomial<T> res;
        auto& a = p.data;
        auto& b = data;
        auto& c = res.data;
        c.resize(a.size() + b.size(), 0);
        for (size_t i = 0; i != a.size(); ++i) {
            for (size_t j = 0; j != b.size(); ++j) {
                c[i + j] += a[i] * b[j];
            }
        }
        relax(res);
        return res;
    }

    Polynomial& operator *= (const Polynomial& p) {
        return *this = *this * p;
    }

    Polynomial operator * (const T& d) const {
        return *this * Polynomial<T>(d);
    }

    Polynomial& operator *= (const T& d) {
        return *this = *this * d;
    }

    const T operator[] (size_t i) const {
        if (i < data.size()) return data[i];
        return 0;
    }

    T operator[] (size_t i) {
        if (i < data.size()) return data[i];
        return 0;
    }

    int Degree() const {
        return data.size() - 1;
    }

    T operator () (const T& x) const {
        T res = 0;
        for (int i = data.size() - 1; i >= 0; --i) {
            res += data[i];
            if (i > 0) res *= x;
        }
        return res;
    }

    friend ostream& operator << (ostream& os, const Polynomial& p) {
        if (p.data.empty()) {
            os << 0;
            return os;
        }
        bool was = false;
        for (size_t i = p.data.size() - 1; i != 0; --i) {
            T k = p[i];
            if (k == 0) continue;
            if (k == 1) {
                if (was) os << "+";
                os << "x";
                if (i != 1) os << "^" << i;
                was = true;
                continue;
            }
            if (k == -1) {
                was = true;
                os << "-x";
                if (i != 1) os << "^" << i;
                continue;
            }
            if (k < 0) {
                was = true;
                os << k << "*" << "x";
                if (i != 1) os << "^" << i;
            }
            if (k > 0)  {
                if (was) os << "+";
                os << k << "*" << "x";
                if (i != 1) os << "^" << i;
                was = true;
            }
        }
        T k = p[0];
        if (k == 0) return os;
        if (k > 0 && was) os << '+';
        os << k;
        return os;
    }

    typename vector<T>::const_iterator begin() const {
        return data.begin();
    }

    typename vector<T>::const_iterator end() const {
        return data.end();
    }

    pair<Polynomial, Polynomial> divide(Polynomial a, Polynomial b) const {
        Polynomial<T> res;
        auto cp = b;
        res.data.resize(a.data.size() + b.data.size() + 2, 0);
        while (a.Degree() >= b.Degree()) {
            auto& tmp = b.data;
            reverse(tmp.begin(), tmp.end());
            while (b.Degree() < a.Degree()) tmp.push_back(0);
            reverse(tmp.begin(), tmp.end());
            T k = a[a.Degree()] / b[b.Degree()];
            res.data[a.Degree() - cp.Degree()] = k;
            a -= b * k;
            b = cp;
        }
        relax(res);
        return {res, a};
    }

    Polynomial operator / (const Polynomial& p) const {
        return divide(*this, p).first;
    }

    Polynomial operator % (const Polynomial& p) const {
        return divide(*this, p).second;
    }

    Polynomial operator , (Polynomial p) const {
        auto q = *this;
        while (!p.data.empty()) {
            q = q % p;
            auto t = q;
            q = p;
            p = t;
        }
        return q / *(new Polynomial<T> (q[q.Degree()]));
    }
};
