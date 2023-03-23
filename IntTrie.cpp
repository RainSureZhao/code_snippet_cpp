class trie {
	map<bool, trie> tries;
public:
	template<typename It>
	void insert(It it, It end_it) {
		if(it == end_it) return;
		tries[*it].insert(next(it), end_it);
	}
	void insert(const vector<int> &v) {
		insert(begin(v), end(v));
	}
	void insert(int x, int idx) {
		if(idx < 0) return;
		tries[x >> idx & 1].insert(x, idx - 1);
	}
	void insert(int x) {
		insert(x, 30);
	}
	template<typename It>
	int get_max_xor_val(It it, It end_it, int idx) {
		if(it == end_it) return 0;
		auto found1 (tries.find(!(*it))), found2(tries.find(*it));
		if(found1 == end(tries)) return found2->second.get_max_xor_val(next(it), end_it, idx - 1);
		return (1 << idx) + found1->second.get_max_xor_val(next(it), end_it, idx - 1);
	}
	int get_max_xor_val(int x) { // 查询trie树中与x异或值最大的数
		vector<int> v;
		for(int i = 30; i >= 0; i --) {
			v.push_back(x >> i & 1);
		}
		return get_max_xor_val(begin(v), end(v), 30);
	}
};