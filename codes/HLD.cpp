// weight in the edges
int t = 0, a[N];
int tin[N], depth[N], par[N], head[N], heavy[N], sz[N], values[N];
vector<array<int, 2>> adj[N];
void dfs(int u, int p) {
  par[u] = p, sz[u] = 1;
  for (auto& [v, w] : adj[u]) {
    if (v != p) {
      depth[v] = depth[u] + 1;
      values[v] = w; // when weight in edges
      dfs(v, u);
      sz[u] += sz[v];
      if (heavy[u] == -1 || sz[heavy[u]] < sz[v]) {
        heavy[u] = v;
      }
    }
  }
}
void decompose(int u, int h) {
  head[u] = h;
  tin[u] = ++t;
  a[t] = values[u];
  if (heavy[u] != -1) decompose(heavy[u], h);
  for (auto& [v, w] : adj[u]) {
    if (v != par[u] && v != heavy[u]) {
      decompose(v, v);
    }
  }
}
// exclude LCA, then eLca = 1
// Update and Query are operations of segmentTree
void UpdatePath(int a, int b, int val, int eLca = 0) {
  for (; head[a] != head[b]; b = par[head[b]]) {
    if (depth[head[a]] > depth[head[b]]) swap(a, b);
    Update(tin[head[b]], tin[b], val);
  }
  if (depth[a] > depth[b]) swap(a, b);
  if (a != b) Update(tin[a] + eLca, tin[b], val);
}
int QueryPath(int a, int b, int eLca = 0) {
  int res = 0;
  for (; head[a] != head[b]; b = par[head[b]]) {
    if (depth[head[a]] > depth[head[b]]) swap(a, b);
    res = (res + Query(tin[head[b]], tin[b])) % mod;
  }
  if (depth[a] > depth[b]) swap(a, b);
  if (a != b) res = (res + Query(tin[a] + eLca, tin[b])) % mod;
  return res;
}
void BuildHLD() {
  t = 0;
  for (int i = 0; i <= n; i++) heavy[i] = -1;
  dfs(1, 1);
  decompose(1, 1);
  BuildSeg();
}