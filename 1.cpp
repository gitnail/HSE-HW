#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Polynomial {
    private:
        vector<T> data;
    public:
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

        bool operator == (const Polynomial& p) {
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
        
        bool operator != (const Polynomial& p) {
            return !(*this == p);
        }
        
        bool operator == (const T& d) {
            return  *this == new Polynomial<T>(d);
        }

        bool operator != (const T& d) {
            return !(*this == d);
        }
        
        Polynomial operator + (const Polynomial& p) {
            Polynomial<T> res;
            auto& a = p.data, b = this->data, c = res.data;
            if (a.size() > b.size()) c = a;
            else c = b;
            for (size_t i = 0; i != min(a.size(), b.size()); ++i) {
                c[i] = a[i] + b[i];
            }
            return res;
        }

        Polynomial operator * (const Polynomial& p) {
            Polynomial<T> res;
            auto& a = p.data, b = this->data, c = res.data;
            c.resize(a.size() + b.size() - 1, 0);
            for (size_t i = 0; i != a.size(); ++i) {
                for (size_t j = 0; j != b.size(); ++j) {
                    c[i + j] += a[i] * b[j];
                }
            }
            return res;
        }

        Polynomial operator - (Polynomial p) {
            for (auto& val : p.data) {
                p = -p;
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
        
        Polynomial operator + (const T& d) {    
            return *this + new Polynomial<T>(d);
        }
        
        Polynomial operator - (const T& d) {
            return *this - new Polynomial<T>(d);
        }

        Polynomial operator * (const T& d) {
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

        const T operator [] (size_t i) const {   
            if (i < this->data.size()) this->data[i];
            return 0;
        }
        
        int Degree(Polynomial& p) {
            for (int i = p.data.size() - 1; i >= 0; --i) {
                if (p[i] != 0) return i;
            }
            return -1;
        }



};

int main() {
    
}















