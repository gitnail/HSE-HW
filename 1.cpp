#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Polynomial {
 private:
    vector<T> data;

    void relax(Polynomial& p) const {
        while (!p.data.empty() && *p.data.rbegin() == 0) p.data.pop_back();
    }

 public:
    Polynomial() {}

    Polynomial(vector<T>& other) : data(other) {
        relax(*this);
    }

    Polynomial(int k) {
        if (k != 0) data = {k};
    }

    template<typename It>
    Polynomial(It first, It last) {
        while (first != last) {
            data.push_back(*first);
            ++first;
        }
        relax(*this);
    }

    Polynomial& operator = (const Polynomial& p) {
        data = p.data;
        return *this;
    }

    bool operator == (const Polynomial& p) const {
        auto& a = p.data;
        auto& b = data;
        if (a.size() == b.size())
            return a == b;
        if (a.size() < b.size()) {
            for (size_t i = 0; i != a.size(); ++i) {
                if (a[i] != b[i]) return false;
            }
            for (size_t i = a.size(); i != b.size(); ++i) {
                if (b[i] != 0) return false;
            }
            return true;
        }
        for (size_t i = 0; i != b.size(); ++i) {
            if (b[i] != a[i]) return false;
        }
        for (size_t i = b.size(); i != a.size(); ++i) {
            if (a[i] != 0) return false;
        }
        return true;
    }

    bool operator != (const Polynomial& p) const {
        return !(*this == p);
    }

    bool operator == (const T& d) const {
        return  *this == *(new Polynomial<T>(d));
    }

    bool operator != (const T& d) const {
        return !(*this == d);
    }

    Polynomial operator + (const Polynomial& p) const {
        Polynomial<T> res;
        auto& a = p.data;
        auto& b = data;
        auto& c = res.data;
        if (a.size() > b.size()) {
            c = a;
        } else  {
            c = b;
        }
        for (size_t i = 0; i != min(a.size(), b.size()); ++i) {
            c[i] = a[i] + b[i];
        }
        relax(res);
        return res;
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

    Polynomial operator - (Polynomial p) const {
        for (auto& val : p.data) {
            val = -val;
        }
        return *this + p;
    }

    Polynomial& operator += (const Polynomial& p) {
        return (*this = *this + p);
    }

    Polynomial& operator -= (const Polynomial& p) {
        return *this = *this - p;
    }

    Polynomial& operator *= (const Polynomial& p) {
        return *this = *this * p;
    }

    Polynomial operator + (const T& d) const {
        return *this + *(new Polynomial<T>(d));
    }

    Polynomial operator - (const T& d) const {
        return *this - *(new Polynomial<T>(d));
    }

    Polynomial operator * (const T& d) const {
        return *this * *(new Polynomial<T>(d));
    }

    Polynomial operator += (const T& d) {
        return *this = *this + d;
    }

    Polynomial operator -= (const T& d) {
        return *this = *this - d;
    }

    Polynomial operator *= (const T& d) {
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
        T res = 0, x1 = 1;
        for (size_t i = 0; i != data.size(); ++i) {
            res += (*this)[i] * x1;
            x1 *= x;
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
};

/*int main() {
    vector<int> v = {1, -1, 4, 5, 3, -6}, v1 = {4, 3, 2, 0, -1, 1};
    Polynomial<int> a(v), b(v1);
    a += b;
    cout << a;
}*/



