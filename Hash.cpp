typedef long long ll;
const int base = 1e8 + 7;
struct hash_map {
  int head[base];
  vector<int> next;
  vector<ll> key;
  vector<ll> val;
  hash_map() {
    memset(head, -1, sizeof(head));
    next.reserve(1e7);
    key.reserve(1e7);
    val.reserve(1e7);
  }
  int hash(ll k) { return k % base; }
  ll &operator[](ll k) {
    int h = hash(k);
    for (int i = head[h]; ~i; i = next[i])
      if (key[i] == k) return val[i];
    next.push_back(head[h]);
    key.push_back(k);
    val.push_back(0);
    head[h] = next.size() - 1;
    return val.back();
  }
  ll has_key(ll k) {
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