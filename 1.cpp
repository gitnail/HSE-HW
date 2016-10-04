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
            Polynomial<T> a(d);
            return a == *this;
        }

        bool operator != (const T& d) {
            return !(*this == d);
        }
        
        Polynomial operator + (const Polynomial& p) {
            Polynomial<T> res;
            auto& a = p.data, b = this->data, c = res.data;
            c.resize(max(a.size(), b.size()), 0);
            for (size_t i = 0; i < )
            //adasd
        }
};

int main() {
    
}















