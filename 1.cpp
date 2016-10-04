#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Polynomial {
    private:
        vector<T> data;
        T pow(T a, int n) {
            T res = 1;
            while (n --> 0) {
                if (n & 1) {
                    res *= a;
                    --n;
                } else {
                    a *= a;
                    n /= 2;
                }
            }
            return res;
        }
    public:
        Polynomial() {}

        Polynomial(vector<T>& other) : data(other) {}

        Polynomial(int k) {
            data = {k};
        }

        template<typename It>
        Polynomial(It first, It last) {
            while (first != last) {
                data.push_back(*first);
                ++first;
            }
        }

        bool operator == (const Polynomial& p) const {
            auto& a = p.data, b = this->data;
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
            return  *this == new Polynomial<T>(d);
        }

        bool operator != (const T& d) const {
            return !(*this == d);
        }
        
        Polynomial operator + (const Polynomial& p) const {
            Polynomial<T> res;
            auto& a = p.data;
            auto& b = this->data;
            auto& c = res.data;
            if (a.size() > b.size()) c = a;
            else c = b;
            for (size_t i = 0; i != min(a.size(), b.size()); ++i) {
                c[i] = a[i] + b[i];
            }
            return res;
        }

        Polynomial operator * (const Polynomial& p) const {
            Polynomial<T> res;
            auto& a = p.data;
            auto& b = this->data;
            auto& c = res.data;
            c.resize(a.size() + b.size() - 1, 0);
            for (size_t i = 0; i != a.size(); ++i) {
                for (size_t j = 0; j != b.size(); ++j) {
                    c[i + j] += a[i] * b[j];
                }
            }
            return res;
        }

        Polynomial operator - (Polynomial p) const {
            for (auto& val : p.data) {
                val = -val;
            }
            return *this + p;
        }

        void operator += (const Polynomial& p) {
            *this = *this + p;
        }

        void operator -= (const Polynomial& p) {
            *this = *this - p;
        }

        void operator *= (const Polynomial& p) {
            *this = *this * p;
        }
        
        Polynomial operator + (const T& d) const {    
            return *this + new Polynomial<T>(d);
        }
        
        Polynomial operator - (const T& d) const {
            return *this - new Polynomial<T>(d);
        }

        Polynomial operator * (const T& d) const {
            return *this * new Polynomial<T>(d);
        }

        Polynomial operator += (const T& d) {
            *this = *this + d;
        }

        Polynomial operator -= (const T& d) {
            *this = *this - d;
        }

        Polynomial operator *= (const T& d) {
            *this = *this * d;
        }

        const T& operator [] (size_t i) const {   
            if (i < this->data.size()) return this->data[i];
            return 0;
        }
    
        T& operator [] (size_t i) {
            if (i < this->data.size()) return this->data[i];
            return 0;
        }
        
        int Degree() const {
            for (int i = this->data.size() - 1; i >= 0; --i) {
                if ((*this)[i] != 0) return i;
            }
            return -1;
        }
        
        const T operator () (const T& x) const {
            T res = 0;
            for (size_t i = 0; i != this->data.size(); ++i) {
                res += (*this)[i] * pow(x, i);
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
                    was = true;
                    os << "x^" << i;
                }
                if (k == -1) {
                    was = true;
                    os << "-x^" << i;
                }
                if (k < 0) {
                    was = true;
                    os << k << "x^" << i;
                }
                if (k > 0){
                    if (was) os << '+';
                    os << k << "x^" << i;
                    was = true;
                }
            }
            T k = p[0];
            if (k > 0 && was) os << '+';
            os << k;
            return os;
        }
        
        template<typename It>
        const It& begin() const {
            It first = this->data.begin();
            It last = this->data.end();
            while (first != last && *first == 0) ++first;
            return first;
        }

        template<typename It>
        const It& end() const {
            It first = this->data.begin();
            It last = this->data.end();
            --last;
            while (first != last) {
                if (*last != 0) return last;    
            }
            return this->data.end();
        }



};

int main() {
    vector<int> v = {1, 3, -1, 0, 4, -5};
    Polynomial<int> a(v), b(5);
}















