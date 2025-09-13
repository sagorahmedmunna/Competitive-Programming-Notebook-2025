struct CentroidDecomposition {
  using T = vector<vector<int>>;
  int n;
  vector<int> sz, is_cen, cpar, cdep;
  CentroidDecomposition(T& adj, int root = 1) {
    n = (int)adj.size() + 1;
    sz.resize(n), is_cen.resize(n), cpar.resize(n), cdep.resize(n);
    Decompose(root, -1, 0, adj);
  }
  void Cal_sz(int u, int p, T& adj) {
    sz[u] = 1;
    for (auto& v : adj[u]) {
      if (v != p && !is_cen[v]) {
        Cal_sz(v, u, adj);
        sz[u] += sz[v];
      }
    }
  }
  int Get_cen(int u, int p, int csz, T& adj) {
    for (auto& v : adj[u]) {
      if (v != p && !is_cen[v] && (2 * sz[v] > csz)) {
        return Get_cen(v, u, csz, adj);
      }
    }
    return u;
  }
  void Decompose(int u, int p,  int d, T& adj) {
    Cal_sz(u, p, adj);
    int c = Get_cen(u, p, sz[u], adj);
    is_cen[c] = 1, cpar[c] = p, cdep[c] = d;
    for (auto& v : adj[c]) {
      if (!is_cen[v]) {
        Decompose(v, c, d + 1, adj);
      }
    }
  }
};