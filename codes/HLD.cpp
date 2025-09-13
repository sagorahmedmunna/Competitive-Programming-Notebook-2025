struct HeavyLightDecomposition {
  int t = 0;
  vector<int> tin, depth, subtree_size, parent, heavy, head, euler;
  SegmentTreeIterative<int> sg;
  HeavyLightDecomposition(int root, vector<vector<int>>& adj, vector<int>& values) {
    int n = (int)adj.size() + 1;
    tin.resize(n), depth.resize(n), subtree_size.resize(n), parent.resize(n), heavy.assign(n, -1), head.resize(n), euler.resize(n);
    Dfs(root, root, adj);
    Decompose(root, root, adj, values);
    sg = SegmentTreeIterative<int> (euler);
  }
  void Dfs(int u, int p, vector<vector<int>>& adj) {
    subtree_size[u] = 1;
    parent[u] = p;
    for (auto& v : adj[u]) {
      if (v != p) {
        depth[v] = depth[u] + 1;
        Dfs(v, u, adj);
        subtree_size[u] += subtree_size[v];
        if (heavy[u] == -1 || subtree_size[heavy[u]] < subtree_size[v]) {
          heavy[u] = v;
        }
      }
    }
  }
  void Decompose(int u, int h, vector<vector<int>>& adj, vector<int>& values) {
    tin[u] = ++t;
    euler[t] = values[u];
    head[u] = h;
    if (heavy[u] != -1) {
      Decompose(heavy[u], h, adj, values);
    }
    for (auto& v : adj[u]) {
      if (v != parent[u] && v != heavy[u]) {
        Decompose(v, v, adj, values);
      }
    }
  }
  void Update(int u, int val) {
    sg.Update(tin[u], val);
  }
  int neutral = 0; #change
  int Merge(int a, int b) {
    return max(a, b); #change
  }
  int PathQuery(int a, int b) {
    int res = neutral;
    for (; head[a] != head[b]; b = parent[head[b]]) {
      if (depth[head[a]] > depth[head[b]]) {
        swap(a, b);
      }
      res = Merge(res, sg.Query(tin[head[b]], tin[b]));
    }
    if (depth[a] > depth[b]) {
      swap(a, b);
    }
    res = Merge(res, sg.Query(tin[a], tin[b]));
    return res;
  }
};
HeavyLightDecomposition hld(1, adj, a);
// add segment tree