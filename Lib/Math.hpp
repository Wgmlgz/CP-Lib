#include <vector>

int MOD = 1e9 + 7;

/* same as ceil(a/(b+0.0)), but better */
template <typename T>
inline T ceildiv(T a, T b) {
  return a / b + (a % b ? 1 : 0);
}

/* number factorization */
template <typename T>
inline std::vector<T> fc(T n) {
  std::vector<T> res;
  for (T d = 2; d * d <= n; d++)
    while (n % d == 0) {
      res.push_back(d);
      n /= d;
    }
  if (n > 1) res.push_back(n);
  return res;
}

/* unique factorization */
template <typename T>
inline std::vector<T> ufc(T n) {
  std::vector<T> res;
  for (T d = 2; d * d <= n; d++) {
    if (n % d == 0) res.push_back(d);
    while (n % d == 0) n /= d;
  }
  if (n > 1) res.push_back(n);
  return res;
}

/* number divisors */
template <typename T>
inline std::vector<T> divs(T n) {
  std::vector<T> res;
  for (T d = 1; d * d <= n; d++)
    if (n % d == 0) {
      res.push_back(d);
      res.push_back(n / d);
    }
  sort(res);
  unq(res);
  return res;
}
/* factorial */
template <typename T>
inline T mfact(T n, T m = MOD) {
  T result = 1;
  for (T i = 2; i <= n; i++) {
    result *= i;
    result %= m;
  }
  return result;
}

/* modpow */
template <typename T>
inline T mpow(T base, T exp, T modulus = MOD) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

/* mod div */
template <typename T>
inline T mdiv(T a, T b, T m = MOD) {
  return (a * mpow(b, m - 2, m)) % m;
}
