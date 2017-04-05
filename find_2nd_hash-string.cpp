#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include <unordered_map>
#include <utility>
using namespace std;

using ll = long long;
using ld = long double;

const int n = 7;
const size_t lim = 1e6 + 2e5;
unordered_map<ll, string> half_hash;
ll module, p, p_power[n * 2];
string Alpha = "_";

int myrand(int i) {
    return rand() % i;
}

ll hash_calc(string& s) {
    ll result = 0;
    for (int i = 0; i < s.size(); ++i) {
        result = (result + p_power[s.size() - i - 1] * s[i]) % module;
    }
    return result;
}

void init() {
    for (char c = 'a'; c <= 'z'; ++c) {
        Alpha += c;
        Alpha += toupper(c);
    }
    for (char c = '0'; c <= '9'; ++c) {
        Alpha += c;
    }
    p_power[0] = 1;
    for (int i = 1; i < n * 2; ++i) {
        p_power[i] = (p_power[i - 1] * p) % module;
    }
}

pair<string, ll> get_str() {
    pair<string, ll> result;
    for (int i = 0; i < n; ++i) {
        result.first += Alpha[rand() % Alpha.size()];
        result.second += p_power[n - i - 1] * result.first[result.first.size() - 1];
        result.second %= module;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    srand(time(NULL));
    string initial_string;
    cin >> initial_string >> module >> p;
    init();
    ll initial_hash = hash_calc(initial_string);
    while (half_hash.size() < min(static_cast<ll>(lim), module)) {
        auto tmp = get_str();
        half_hash[tmp.second] = tmp.first;
    }
    while (true) {
        auto tmp = get_str();
        for (int i = 0; i < n; ++i) {
            tmp.second = (tmp.second * p) % module;
        }
        ll need = (initial_hash - tmp.second) % module;
        need += module;
        need %= module;
        if (half_hash.find(need) != half_hash.end()) {
            string answer = tmp.first + half_hash[need];
            if (answer == initial_string) continue;
            cout << answer << '\n';
            return 0;
        }
    }
}

