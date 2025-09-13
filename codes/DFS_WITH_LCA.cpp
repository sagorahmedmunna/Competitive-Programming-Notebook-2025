struct DFS {
  int n, k, t = 0;
  vector<int> tin, tout, depth, height, subtree_size, heavy;
  vector<bool> is_leaf;
  vector<vector<int>> parent;
  DFS() {}
  DFS(vector<vector<int>>& adj, int root = 1) {
    n = (int)adj.size() + 1;
    k = __lg(n) + 1;
    tin.resize(n), tout.resize(n), depth.resize(n), height.resize(n), subtree_size.resize(n), heavy.assign(n, - 1), is_leaf.assign(n, 1);
    parent = vector<vector<int>> (n, vector<int> (k));
    dfs(root, root, adj);
  }
  void dfs(int u, int p, vector<vector<int>>& adj) {
    tin[u] = ++t;
    subtree_size[u] = 1;
    parent[u][0] = p;
    for (int i = 1; i < k; i++) {
      if (parent[u][i - 1] != -1) parent[u][i] = parent[parent[u][i - 1]][i - 1];
      else parent[u][i] = -1;
    }
    for (auto& v : adj[u]) {
      if (v != p) {
        depth[v] = depth[u] + 1;
        is_leaf[u] = 0;
        dfs(v, u, adj);
        height[u] = max(height[u], height[v] + 1);
        subtree_size[u] += subtree_size[v];
        if (heavy[u] == -1 || subtree_size[heavy[u]] < subtree_size[v]) {
          heavy[u] = v;
        }
      }
    }
    tout[u] = ++t;
  }
  bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
  }
  int kth_parent(int u, int kth) {
    for (int i = k - 1; i >= 0; i--) {
      if (kth & (1 << i)) {
        u = parent[u][i];
        if (u == -1) return u;
      }
    }
    return u;
  }
  int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    for (int i = k - 1; i >= 0; i--) {
      if (!is_ancestor(parent[u][i], v)) {
        u = parent[u][i];
      }
    }
    return parent[u][0];
  }
  int dis(int u, int v)
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
};