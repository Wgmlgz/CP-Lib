#pragma once
#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "Dsu.hpp"

#define in std::cin


struct edge {
  int a, b, w;
};
bool operator<(const edge& a, const edge& b) { return a.w < b.w; }

std::pair<int, std::vector<std::pair<edge, int>>> id_mst(
    const std::vector<edge>& edges, int n) {
  int cost = 0;
  std::vector<std::pair<edge, int>> result, id_edges;
  DSU dsu(n);

  for (int i = 0; i < n; ++i) dsu.make(i);
  for (int i = 0; i < edges.size(); ++i) id_edges.push_back({edges[i], i});

  std::sort(id_edges.begin(), id_edges.end());
  for (auto& e : id_edges)
    if (dsu.find(e.first.a) != dsu.find(e.first.b)) {
      cost += e.first.w;
      result.push_back(e);
      dsu.merge(e.first.a, e.first.b);
    }
  return {cost, result};
}

std::pair<int, std::vector<edge>> mst(const std::vector<edge>& edges, int n) {
  int cost = 0;
  std::vector<edge> result, _edges = edges;
  DSU dsu(n);

  for (int i = 0; i < n; ++i) dsu.make(i);

  std::sort(_edges.begin(), _edges.end());
  for (auto& e : _edges)
    if (dsu.find(e.a) != dsu.find(e.b)) {
      cost += e.w;
      result.push_back(e);
      dsu.merge(e.a, e.b);
    }
  return {cost, result};
}

void reduceTree(std::vector<std::vector<int>>& g, int v = -1) {
  static std::vector<int8_t> used;

  if (v == -1) {
    used = std::vector<int8_t>(g.size());
    reduceTree(g, 0);
    return;
  }

  used[v] = 1;
  std::vector<int> t;

  for (auto i : g[v]) {
    if (used[i]) continue;
    t.push_back(i);
    reduceTree(g, i);
  }

  g[v] = t;
}

std::vector<std::vector<int>> readG(int n, int m) {
  std::vector<std::vector<int>> graph(n);

  for (int i = 0; i < m; ++i) {
    int a, b;
    in >> a >> b; 
    --a, --b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  return graph;
}

std::vector<std::vector<std::pair<int, int>>> readGW(int n, int m) {
  std::vector<std::vector<std::pair<int, int>>> graph(n);

  for (int i = 0; i < m; ++i) {
    int a, b, w;
    in >> a >> b >> w;
    --a, --b;
    graph[a].emplace_back(b, w);
    graph[b].emplace_back(a, w);
  }

  return graph;
}
