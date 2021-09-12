#pragma once
#include "debug.hpp"

signed main() {
  // ios_base::sync_with_stdio(0), in.tie(0), out.tie(0);
  freopen(R"(input.txt)", "r", stdin);
  presolve();
  if (getTests()) {
    int n;
    I n;
    for (int i = 1; i <= n; ++i) {
      o colors::YELLOW + "-- "+ to_string(i) + " --" + colors::RESET;
      solve(i);
    }
  } else solve(0);
  o colors::RED + "gg " + to_string(clock() * 1.0 / CLOCKS_PER_SEC) + " " + colors::RESET;
}