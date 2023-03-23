const int base = 1e7 + 7;
struct hash_map {
  int head[base];
  vector<int> next;
  vector<long long> key;
  vector<long long> val;
  hash_map() {
    memset(head, -1, sizeof(head));
    next.reserve(1e7);
    key.reserve(1e7);
    val.reserve(1e7);
  }
  int hash(long long k) { return ((k % base) + base) % base; }
  long long &operator[](long long k) {
    int h = hash(k);
    for (int i = head[h]; ~i; i = next[i])
      if (key[i] == k) return val[i];
    next.push_back(head[h]);
    key.push_back(k);
    val.push_back(0);
    head[h] = next.size() - 1;
    return val.back();
  }
  bool has_key(long long k) {
    int h = hash(k);
    for (int i = head[h]; ~i; i = next[i])
      if (key[i] == k) return true;
    return false;
  }
};
hash_map val;
// 存储pair<int, int>时
// ll key = p.x << 32 | p.y;
// if(val.has_key(key)) return val[key];