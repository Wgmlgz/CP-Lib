#pragma once
#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>

#include "Dsu.hpp"

#define in std::cin


struct edge { int a, b, w; };
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

// mst
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

// make dfs easier
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

// unweighted graph read
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

// weighted graph read
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

// top sort
void top_sort_dfs(const std::vector<std::vector<int>>& g, std::vector<int>& used, std::vector<int>& ans, int v) {
  if (used[v]) return;
  used[v] = 1;

  for (auto& i : g[v])
    top_sort_dfs(g, used, ans, i);

  ans.push_back(v);
}
std::vector<int> top_sort(const std::vector<std::vector<int>>& g) {
  int n = g.size();

  std::vector<int> used(n), ans;
  for (int i = 0; i < n; ++i)
    top_sort_dfs(g, used, ans, i);
  
  reverse(begin(ans), end(ans));
  return ans;
}

// strong components
void strong_comps_dfs(const std::vector<std::vector<int>>& g, std::vector<int>& used, int id, int v) {
  if (used[v]) return;
  used[v] = id;

  for (auto& i : g[v]) strong_comps_dfs(g, used, id, i);
}
std::pair<std::vector<int>, int> strong_comps(const std::vector<std::vector<int>>& g, const std::vector<int>& order) {
  int n = g.size();

  std::vector<int> ans(n);

  int id = 1;

  for (int i = 0; i < n; ++i) {
    if (ans[order[i]]) continue;
    strong_comps_dfs(g, ans, id, order[i]);
    ++id;
  }
  return {ans, id-1};
}

std::vector<std::vector<int>> makeg_by_comps(std::vector<int> comps, int n, const std::vector<std::pair<int, int>>& edges) {
  for (auto& i : comps) --i;

  std::vector<std::vector<int>> g(n);

  for (auto [a, b] : edges) {
    if (comps[a] == comps[b]) continue;
    g[comps[a]].push_back(comps[b]);
  }

  return g;
}

// cutpoints
struct cutpoints {
  std::vector<std::vector<int>> g;
  std::vector<int> used;
  std::vector<int> fup, tin;
  std::vector<int> cutpoints;
  int timer = 0;
  void find_cutpoints(int v, int p = -1) {
    used[v] = 1;
    tin[v] = fup[v] = timer++;
    int childs = 0;
    for (auto& i : g[v]) {
      if (i == p) continue;
      if (used[i]) {
        fup[v] = std::min(fup[v], tin[i]);
      } else {
        find_cutpoints(i, v);
        fup[v] = std::min(fup[v], fup[i]);
        if (fup[i] >= tin[v] and p != -1) {
          cutpoints.push_back(v);
        } 
        ++childs;
      }
    }

    if (p == -1 and childs > 1) {
      cutpoints.push_back(v);
    }
  }
};

// euler path
struct euler_path {
  std::vector<int> ans;
  std::vector<std::unordered_multiset<int>> g;
  void euler(int v) {
    while (g[v].size()) {
      int to = *begin(g[v]);
      g[v].erase(begin(g[v]));
      g[to].erase(g[to].find(v));

      euler(to);
    }
    ans.push_back(v + 1);
  }
};