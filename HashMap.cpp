#include <algorithm>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

template<class KeyType, class ValueType, class Hash = std::hash<KeyType>>
class HashMap {
 private:
    std::vector<std::list<typename std::list<std::pair<const KeyType,
    ValueType>>::iterator>> table_;
    std::list<std::pair<const KeyType, ValueType>> all_;
    Hash hash_;
    const size_t beginner_size_ = 1, times_ = 2;
    size_t buckets_;
    void grow_up() {
        buckets_ = 0;
        const size_t next_size = table_.size() * times_;
        table_.clear();
        table_.resize(next_size);
        for (auto x = all_.begin(); x != all_.end(); ++x) {
            size_t id = hash_(x->first) % table_.size();
            table_[id].push_back(x);
            if (table_[id].size() == 1) {
                ++buckets_;
            }
        }
    }

 public:
    typedef typename std::list<std::pair<const KeyType, ValueType>>::iterator iterator;
    typedef typename std::list<std::pair<const KeyType, ValueType>>::const_iterator const_iterator;

    HashMap(Hash new_hash = Hash()) : hash_(new_hash) {
        table_.resize(beginner_size_);
        buckets_ = 0;
    }

    template<typename It>
    HashMap(It begin, It end, Hash new_hash = Hash()) : HashMap(new_hash) {
        while (begin != end) {
            insert(*begin);
            ++begin;
        }
    }

    HashMap(std::initializer_list<std::pair<KeyType, ValueType>> l, Hash new_hash = Hash()) :
    HashMap(l.begin(), l.end(), new_hash) {}

    size_t size() const {
        return all_.size();
    }

    bool empty() const {
        return all_.empty();
    }

    Hash hash_function() const {
        return hash_;
    }

    void erase(KeyType key) {
        size_t id = hash_(key) % table_.size();
        for (auto i = table_[id].begin(); i != table_[id].end(); ++i) {
            if ((*i)->first == key) {
                all_.erase(*i);
                table_[id].erase(i);
                if (table_[id].empty()) {
                    --buckets_;
                }
                return;
            }
        }
    }

    void clear() {
        buckets_ = 0;
        table_.clear();
        table_.resize(beginner_size_);
        all_.clear();
    }

    void insert(const std::pair<KeyType, ValueType> x) {
        size_t id = hash_(x.first) % table_.size();
        for (const auto& it : table_[id]) {
            if (it->first == x.first) {
                return;
            }
        }
        all_.push_front(x);
        table_[id].push_back(all_.begin());
        if (table_[id].size() == 1) {
            ++buckets_;
        }
        const size_t free_space = table_.size() / times_;
        if (buckets_ > free_space) {
            grow_up();
        }
    }

    const_iterator begin() const {
        return all_.begin();
    }

    const_iterator end() const {
        return all_.end();
    }

    iterator begin() {
        return all_.begin();
    }

    iterator end() {
        return all_.end();
    }

    iterator find(KeyType key) {
        size_t id = hash_(key) % table_.size();
        for (const auto& x : table_[id]) {
            if (x->first == key) {
                return x;
            }
        }
        return all_.end();
    }

    const_iterator find(KeyType key) const {
        size_t id = hash_(key) % table_.size();
        for (const auto& x : table_[id]) {
            if (x->first == key) {
                return x;
            }
        }
        return all_.end();
    }

    ValueType& operator[](KeyType key) {
        auto found = find(key);
        if (found == all_.end()) {
            insert({key, ValueType()});
            auto found_again = find(key);
            return found_again->second;
        } else {
            return found->second;
        }
    }

    const ValueType& at(KeyType key) const {
        auto found = find(key);
        if (found == all_.end()) {
            throw std::out_of_range("out of range");
        } else {
            return found->second;
        }
    }

    void swap(HashMap& other) throw() {
        all_.swap(other.all_);
        table_.swap(other.table_);
        std::swap(hash_, other.hash_);
        std::swap(buckets_, other.buckets_);
    }

    HashMap operator =(const HashMap& other) {
        HashMap temp(other);
        temp.swap(*this);
        return *this;
    }
};
