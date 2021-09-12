#pragma once
#include <vector>
#include <utility>
#include <iostream>
#include <string>

// i will never use this
template<typename T1, typename T2>std::vector<std::pair<typename T1::value_type, typename T2::value_type>> zip(T1& a, T2& b) {
  vector<pair<typename T1::value_type, typename T2::value_type>> c(a.size());
  transform(a.begin(), a.end(), b.begin(), c.begin(),
    [](const auto& aa, const auto& bb) {
      return make_pair(aa, bb);
    });
  return c;
}

std::vector<int> zstr(std::string s) {
  int n = (int)s.length();
  std::vector<int> z(s.size());
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}
