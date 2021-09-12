#pragma once
#include <bits/stdc++.h>

/* fast hash table */
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    /* http://xorshift.di.unimi.it/splitmix64.c */
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};
template <typename key, typename val>
using hmap = gp_hash_table<key, val, custom_hash>;
template <typename key>
using hset = gp_hash_table<key, null_type, custom_hash>;


/* python lol */
class range {
 private:
  struct II {
    int x;
    int operator*() { return x; }
    bool operator!=(II& lhs) { return x < lhs.x; }
    void operator++() { ++x; }
  };
  II i, n;

 public:
  range(int n) : i({0}), n({n}) {}
  range(int i, int n) : i({i}), n({n}) {}
  II& begin() { return i; }
  II& end() { return n; }
};

/* slow but fun */
#pragma region 
struct VCache {
  virtual void clear() {}
};
struct CacheHandler {
  std::vector<VCache*> caches;
  void add(VCache* new_cache) { caches.push_back(new_cache); }
  void clear() {
    for (const auto& i : caches) i->clear();
  }
};
CacheHandler cache_handler;
template <typename R, typename... A>
class Cache : public VCache {
  std::function<R(A...)> f_;
  std::map<std::tuple<A...>, R> map_;

 public:
  Cache(std::function<R(A...)> f) : f_(f) { cache_handler.add(this); }
  R operator()(A... a) {
    std::tuple<A...> key(a...);
    auto search = map_.find(key);
    if (search != map_.end()) return search->second;
    auto result = f_(a...);
    map_[key] = result;
    return result;
  }
  void clear() { map_.clear(); }
  void operator!() { clear(); }
};
#pragma endregion

/* some day... */
std::istream& operator>>(std::istream& istr, __int128_t& val) {
  std::string s;
  istr >> s;
  val = 0;
  for (char c : s) {
    val = 10 * val + (c - '0');
  }
  return istr;
}
std::ostream& operator<<(std::ostream& dest, __int128_t val) {
  std::ostream::sentry s(dest);
  if (s) {
    __uint128_t tmp = val < 0 ? -val : val;
    char buffer[128];
    char* d = std::end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
    if (val < 0) {
      --d;
      *d = '-';
    }
    int len = std::end(buffer) - d;
    if (dest.rdbuf()->sputn(d, len) != len) {
      dest.setstate(std::ios_base::badbit);
    }
  }
  return dest;
}