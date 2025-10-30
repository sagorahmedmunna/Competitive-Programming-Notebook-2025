struct DSU {
  vector<int> parent, sz;
  DSU(int n) {
    parent.resize(n + 1), sz.resize(n + 1, 1);
    iota(parent.begin(), parent.end(), 0);
  }
  int Find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = Find(parent[u]);
  }
  bool Is_connected(int u, int v) {
    return Find(u) == Find(v);
  }
  void Merge(int u, int v) {
    u = Find(u), v = Find(v);
    if (u != v) {
      if (sz[u] < sz[v]) swap(u, v);
      parent[v] = u;
      sz[u] += sz[v];
    }
  }
};