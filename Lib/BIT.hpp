// -> https://cp-algorithms.com/data_structures/fenwick.html

#include <bits/stdc++.h>

/**
 * point update [l, r)
 * range query
 */
struct BITsum {
  std::vector<int> bit;
  int n;

  BITsum(int n) {
    this->n = n + 1;
    bit.assign(n + 1, 0);
  }

  BITsum(std::vector<int> a) : BITsum(a.size()) {
    for (size_t i = 0; i < a.size(); i++) add(i, a[i]);
  }

  int sum(int idx) {
    int res = 0;
    for (++idx; idx > 0; idx -= idx & -idx) res += bit[idx];
    return res;
  }

  int sum(int l, int r) { return sum(r - 1) - sum(l - 1); }

  void add(int idx, int delta) {
    for (++idx; idx < n; idx += idx & -idx) bit[idx] += delta;
  }
};

/** 
 * range update 
 * point query
*/
struct BITrange_add {
  std::vector<int> bit;
  int n;

  BITrange_add(int n) {
    this->n = n + 1;
    bit.assign(n + 1, 0);
  }

  void add(int idx, int val) {
    for (++idx; idx < n; idx += idx & -idx) bit[idx] += val;
  }

  void range_add(int l, int r, int val) {
    add(l, val);
    add(r, -val);
  }

  int operator[](int idx) {
    int res = 0;
    for (++idx; idx > 0; idx -= idx & -idx) res += bit[idx];
    return res;
  }

  BITrange_add(std::vector<int> a) : BITrange_add(a.size()) {
    for (size_t i = 0; i < a.size(); i++) {
      range_add(i, i + 1, a[i]);
    }
  }
};

/**
 * min
 */
struct BITmin {
  std::vector<int> bit;
  int n;
  const int INF = (int)1e9;

  BITmin(int n) {
    this->n = n;
    bit.assign(n, INF);
  }

  BITmin(std::vector<int> a) : BITmin(a.size()) {
    for (size_t i = 0; i < a.size(); i++) update(i, a[i]);
  }

  int getmin(int r) {
    int res = INF;
    for (; r >= 0; r = (r & (r + 1)) - 1) res = std::min(res, bit[r]);
    return res;
  }

  void update(int idx, int val) {
    for (; idx < n; idx = idx | (idx + 1)) bit[idx] = std::min(bit[idx], val);
  }
};

/**
 * max
 */
struct BITmax {
  std::vector<int> bit;
  int n;
  const int INF = (int)1e9;

  BITmax(int n) {
    this->n = n;
    bit.assign(n, -INF);
  }

  BITmax(std::vector<int> a) : BITmax(a.size()) {
    for (size_t i = 0; i < a.size(); i++) update(i, a[i]);
  }

  int getmin(int r) {
    int res = -INF;
    for (; r >= 0; r = (r & (r + 1)) - 1) res = std::max(res, bit[r]);
    return res;
  }

  void update(int idx, int val) {
    for (; idx < n; idx = idx | (idx + 1)) bit[idx] = std::max(bit[idx], val);
  }
};