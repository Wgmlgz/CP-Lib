#pragma once
#include <vector>

struct DSU {
  std::vector<int> parent, rank;
  void make(int v) {
    parent[v] = v;
    rank[v] = 0;
  }

  int find(int v) {
    if (v == parent[v])
      return v;
    return parent[v] = this->find(parent[v]);
  }

  void merge(int a, int b) {
    a = this->find(a);
    b = this->find(b);
    if (a != b) {
      if (rank[a] < rank[b])
        std::swap(a, b);
      parent[b] = a;
      if (rank[a] == rank[b])
        rank[a]++;
    }
  }
  DSU(int n) {
    parent.resize(n);
    rank.resize(n);
  }
};
