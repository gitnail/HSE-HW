#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include <unordered_map>
#include <utility>
#include <vector>

using ll = long long;
using ld = long double;

const size_t n = 7;
const size_t lim = 1e6 + 2e5;

ll hash_calc(const std::string& s, const std::vector<ll>& p_power,
    const ll& module, const ll& p) {
    ll result = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        result = (result + p_power[s.size() - i - 1] * s[i]) % module;
    }
    return result;
}

void init_alpha(std::string& Alpha) {
    for (char c = 'a'; c <= 'z'; ++c) {
        Alpha += c;
        Alpha += toupper(c);
    }
    for (char c = '0'; c <= '9'; ++c) {
        Alpha += c;
    }
}

void init_pw(std::vector<ll>& p_power, const ll& p, const ll& module) {
    p_power[0] = 1;
    for (size_t i = 1; i < n * 2; ++i) {
        p_power[i] = (p_power[i - 1] * p) % module;
    }
}

std::pair<std::string, ll> get_str(const std::string& Alpha,
    const std::vector<ll>& p_power, const ll& module) {
    std::pair<std::string, ll> result;
    for (size_t i = 0; i < n; ++i) {
        result.first += Alpha[rand() % Alpha.size()];
        result.second += p_power[n - i - 1] * result.first[result.first.size() - 1];
        result.second %= module;
    }
    return result;
}

std::string find_collision(const std::string& initial_string, const std::string& Alpha,
    const std::vector<ll>& p_power, const ll& module, const ll& p) {
    std::unordered_map<ll, std::string> half_hash;
    while (half_hash.size() < std::min(static_cast<ll>(lim), module)) {
        auto tmp = get_str(Alpha, p_power, module);
        half_hash[tmp.second] = tmp.first;
    }
    ll initial_hash = hash_calc(initial_string, p_power, module, p);
    while (1) {
        auto tmp = get_str(Alpha, p_power, module);
        for (size_t i = 0; i < n; ++i) {
            tmp.second = (tmp.second * p) % module;
        }
        ll need = (initial_hash - tmp.second) % module;
        need += module;
        need %= module;
        if (half_hash.find(need) != half_hash.end()) {
            std::string answer = tmp.first + half_hash[need];
            if (answer == initial_string) continue;
            return answer;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(nullptr);
    srand(time(NULL));
    std::string initial_string, Alpha = "_";;
    std::unordered_map<ll, std::string> half_hash;
    ll p, module;
    std::cin >> initial_string >> module >> p;
    std::vector<ll> p_power(n * 2);
    init_alpha(Alpha);
    init_pw(p_power, p, module);
    std::cout << find_collision(initial_string, Alpha,
    p_power, module, p) << '\n';
}
