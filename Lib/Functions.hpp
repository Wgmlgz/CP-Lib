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
