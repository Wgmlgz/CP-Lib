#pragma once
#include <bits/stdc++.h>

std::mt19937 rope_rng;


template<typename T>
struct rope {
  /* by Wgmlgz */
  struct node {
    node* lhs = nullptr;
    node* rhs = nullptr;
    int priority;
    int size = 1;
    T val;
    node(const T& _val) : val(_val) { priority = rope_rng(); };
    ~node(){
      if (lhs) delete lhs;
      if (rhs) delete rhs;
    }
  };

  int node_size(node* nd) {
    return nd ? nd->size : 0;
  }
  void recalc(node* nd) {
    if (nd)
      nd->size = node_size(nd->lhs) + node_size(nd->rhs) + 1;
  }

  void merge(node*& res, node* lhs, node* rhs) {
    if (!lhs || !rhs)
      res = lhs ? lhs : rhs;
    else if (lhs->priority < rhs->priority)
      merge(rhs->lhs, lhs, rhs->lhs), res = rhs;
    else
      merge(lhs->rhs, lhs->rhs, rhs), res = lhs;

    recalc(res);
  }

  void split(node* nd, node*& lhs, node*& rhs, int pos, int add = 0) {
    if (!nd) lhs = rhs = nullptr;
    else {
      int cur = add + node_size(nd->lhs);
      if (cur < pos) {
        split(nd->rhs, nd->rhs, rhs, pos, cur + 1), lhs = nd;
      } else {
        split(nd->lhs, lhs, nd->lhs, pos, add), rhs = nd;
      }
      recalc(nd);
    }
    
  }

  node* root = nullptr;

  void node_to_vec(std::vector<T>& v, node* nd) {
    if (!nd) return;

    node_to_vec(v, nd->lhs);
    v.push_back(nd->val);
    node_to_vec(v, nd->rhs);
  }

public:
  size_t size() {
    return node_size(root);
  }
  void push_front(const T& val) {
    auto nd = new node(val);
    merge(root, nd, root);
  }
  void push_back(const T& val) {
    auto nd = new node(val);
    merge(root, root, nd);
  }

  /* borrowing ownership */
  void push_front(rope& bro) {
    merge(root, bro.root, root);
    bro.root = nullptr;
  }
  /* borrowing ownership */
  void push_back(rope& bro) {
    merge(root, root, bro.root);
    bro.root = nullptr;
  }
  /* borrowing ownership */
  void operator+=(rope& bro) {
    push_back(bro);
  }
  /* borrowing ownership */
  void operator=(rope& bro) {
    delete root;
    root = bro.root;
    bro.root = nullptr;
  }
  T insert(int pos, const T& val) {
    auto nd = new node(val);
    node* tmp;

    split(root, root, tmp, pos);
    merge(tmp, nd, tmp);
    merge(root, root, tmp);

    return val;
  }

  T pop_front() {
    node* cutted;
    split(root, cutted, root, 1);
    T res = cutted->val;
    delete cutted;
    return res;
  }
  T pop_back() {
    node* cutted;
    split(root, cutted, root, size() - 1);
    T res = cutted->val;
    delete cutted;
    return res;
  }

  std::vector<T> to_vec() {
    std::vector<T> v;
    node_to_vec(v, root);
    return v;
  }

  rope cut(int pos) {
    rope res;
    split(root, root, res.root, pos);
    return res;
  }

  rope cut(int l, int r) {
    if (r >= size()) return cut(l);
    assert(l < r);

    rope res;

    node* a, * b, * c;

    split(root, a, b, l);
    split(b, b, c, r - l);
    
    merge(root, a, c);
    res.root = b;

    return res;
  }

  T erase(int pos) {
    auto cutted = cut(pos, pos + 1);
    return cutted.to_vec().front();
  }

  void clear() {
    delete root;
  }

  /* broken maybe fix later */
  ~rope() {
    // delete root;
  }
};
