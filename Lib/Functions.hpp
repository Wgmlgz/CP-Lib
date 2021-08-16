#pragma once
#include <vector>
#include <utility>
#include <iostream>
#include <string>


// not perfect number factorization
std::vector<int> fc(int n) {
  std::vector<int> res;
  for (int d = 2; d * d <= n; d++)
    while (n % d == 0) {
      res.push_back(d);
      n /= d;
    }
  if (n > 1)
    res.push_back(n);
  return res;
}

// factorial
int fact(int n) {
  int result = 1;
  for (int i = 1; i <= n; i++)
    result *= i;
  return result;
}

// modpow
template <typename T>
T mpow(T base, T exp, T modulus = 1e9 + 7) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

// i will never use this
template<typename T1, typename T2>std::vector<std::pair<typename T1::value_type, typename T2::value_type>> zip(T1& a, T2& b) {
  vector<pair<typename T1::value_type, typename T2::value_type>> c(a.size());
  transform(a.begin(), a.end(), b.begin(), c.begin(),
    [](const auto& aa, const auto& bb) {
      return make_pair(aa, bb);
    });
  return c;
}

// same as ceil(a/(b+0.0)), but better (saved my life once)
inline int ceildiv(int a, int b) { return a / b + (a % b ? 1 : 0); }

// cache
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

// some day...
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