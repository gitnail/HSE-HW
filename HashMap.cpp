#include <algorithm>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

template<class KeyType, class ValueType, class Hash = std::hash<KeyType>>
class HashMap {
 private:
    std::vector<std::list<typename std::list<std::pair<const KeyType,
    ValueType>>::iterator>> table;
    std::list<std::pair<const KeyType, ValueType>> all;
    Hash hash_;
    const size_t beginner_size = 1;
    size_t buckets;

 public:
    typedef typename std::list<std::pair<const KeyType, ValueType>>::iterator iterator;
    typedef typename std::list<std::pair<const KeyType, ValueType>>::const_iterator const_iterator;

    HashMap(Hash new_hash = Hash()) : hash_(new_hash) {
        table.resize(beginner_size);
        buckets = 0;
    }

    template<typename It>
    HashMap(It begin, It end, Hash new_hash = Hash()) : hash_(new_hash) {
        buckets = 0;
        table.resize(beginner_size);
        while (begin != end) {
            insert(*begin);
            ++begin;
        }
    }

    HashMap(std::initializer_list<std::pair<KeyType, ValueType>> l, Hash new_hash = Hash()) :
    hash_(new_hash) {
        table.resize(beginner_size);
        buckets = 0;
        for (auto x : l) {
            insert(x);
        }
    }

    size_t size() const {
        return all.size();
    }

    bool empty() const {
        return all.empty();
    }

    Hash hash_function() const {
        return hash_;
    }

    void erase(KeyType key) {
        size_t id = hash_(key) % table.size();
        for (auto i = table[id].begin(); i != table[id].end(); ++i) {
            if ((*i)->first == key) {
                all.erase(*i);
                table[id].erase(i);
                if (table[id].empty()) {
                    --buckets;
                }
                return;
            }
        }
    }

    void grow_up() {
        buckets = 0;
        size_t prev_size = table.size();
        table.clear();
        table.resize(prev_size * 2);
        for (auto x = all.begin(); x != all.end(); ++x) {
            size_t id = hash_(x->first) % table.size();
            table[id].push_back(x);
            if (table[id].size() == 1) {
                ++buckets;
            }
        }
    }

    void clear() {
        buckets = 0;
        table.clear();
        table.resize(beginner_size);
        all.clear();
    }

    void insert(std::pair<KeyType, ValueType> x) {
        size_t id = hash_(x.first) % table.size();
        for (auto& it : table[id]) {
            if (it->first == x.first) {
                return;
            }
        }
        all.push_front(x);
        table[id].push_back(all.begin());
        if (table[id].size() == 1) {
            ++buckets;
        }
        if (buckets > table.size() / 2) {
            grow_up();
        }
    }

    const_iterator begin() const {
        return all.begin();
    }

    const_iterator end() const {
        return all.end();
    }

    iterator begin() {
        return all.begin();
    }

    iterator end() {
        return all.end();
    }

    iterator find(KeyType key) {
        size_t id = hash_(key) % table.size();
        for (auto& x : table[id]) {
            if (x->first == key) {
                return x;
            }
        }
        return all.end();
    }

    const_iterator find(KeyType key) const {
        size_t id = hash_(key) % table.size();
        for (auto& x : table[id]) {
            if (x->first == key) {
                return x;
            }
        }
        return all.end();
    }

    ValueType& operator[](KeyType key) {
        auto found = find(key);
        if (found == all.end()) {
            insert({key, ValueType()});
            auto found_again = find(key);
            return found_again->second;
        } else {
            return found->second;
        }
    }

    const ValueType& at(KeyType key) const {
        auto found = find(key);
        if (found == all.end()) {
            throw std::out_of_range("out of range");
        } else {
            return found->second;
        }
    }

    void swap(HashMap& other) throw() {
        all.swap(other.all);
        table.swap(other.table);
        std::swap(hash_, other.hash_);
        std::swap(buckets, other.buckets);
    }

    HashMap operator =(const HashMap& other) {
        HashMap temp(other);
        temp.swap(*this);
        return *this;
    }
};
