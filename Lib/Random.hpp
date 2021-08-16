#pragma once
#include <vector>
#include <algorithm>
#include <utility>
#include "Dsu.hpp"

struct edge {
  int a, b, w;
};
bool operator<(const edge& a, const edge& b) { return a.w < b.w; }

std::pair<int, std::vector<std::pair<edge, int>>> id_mst(const std::vector<edge>& edges, int n) {
  int cost = 0;
  std::vector<std::pair<edge, int>> result, id_edges;
  DSU dsu(n);

  for (int i = 0; i < n; ++i) dsu.make(i);
  for (int i = 0; i < edges.size(); ++i) id_edges.push_back({ edges[i], i });

  std::sort(id_edges.begin(), id_edges.end());
  for (auto& e : id_edges) if (dsu.find(e.first.a) != dsu.find(e.first.b)) {
    cost += e.first.w;
    result.push_back(e);
    dsu.merge(e.first.a, e.first.b);
  }
  return { cost, result };
}

std::pair<int, std::vector<edge>> mst(const std::vector<edge>& edges, int n) {
  int cost = 0;
  std::vector<edge> result, _edges = edges;
  DSU dsu(n);

  for (int i = 0; i < n; ++i) dsu.make(i);

  std::sort(_edges.begin(), _edges.end());
  for (auto& e : _edges) if (dsu.find(e.a) != dsu.find(e.b)) {
    cost += e.w;
    result.push_back(e);
    dsu.merge(e.a, e.b);
  }
  return { cost, result };
}