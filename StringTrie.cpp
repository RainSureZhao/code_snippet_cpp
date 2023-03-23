template <typename T> // 字符串trie，支持插入字符串，查询字符串个数，打印trie树，查询子树
class trie {
    map<T, trie> tries;
    map<T, int> cnt;
public:
    template<typename It>
    void insert(It it, It end_it) {
        if(it == end_it) return;
        if(next(it) == end_it) cnt[*it] ++;
        tries[*it].insert(next(it), end_it);
    }
    template<typename C>
    void insert(const C& container) { // 插入字符串tr.insert(begin(s), end(s));
        insert(begin(container), end(container));
    }
    void insert(const initializer_list<T>& il) { // tr.insert({'a', 'b', 'c'});
        insert(begin(il), end(il));
    }
    void print(vector<T> &v) const {
        if(tries.empty()) {
            copy(begin(v), end(v), ostream_iterator<T>(cout, " "));
            cout << "\n";
        }
        for(auto [key, val] : tries) {
            v.push_back(key);
            val.print(v);
            v.pop_back();
        }
    }
    void print() const {
        vector<T> v;
        print(v);
    }
    template<typename It>
    optional<reference_wrapper<const trie>> subtrie(It it, It end_it) const { // 查询trie树是否存在以某个字符串为前缀的字符串
        if(it == end_it) return ref(*this);
        auto found (tries.find(*it));
        if(found == end(tries)) return nullopt;

        return found->second.subtrie(next(it), end_it);
    }
    template<typename C>
    auto subtrie(const C &c) {
        return subtrie(begin(c), end(c));
    }
    int get_count(const T& key) const {
        auto found (cnt.find(key));
        if(found == end(cnt)) return 0;
        return found->second;
    }
    template<typename It>
    int get_count(It it, It end_it) const { // 查询某个字符串个数 tr.get_count(begin(s), end(s));
        if(it == end_it) return 0;
        if(next(it) == end_it) return get_count(*it);
        auto found (tries.find(*it));
        if(found == end(tries)) return 0;
        return found->second.get_count(next(it), end_it);
    }
};
