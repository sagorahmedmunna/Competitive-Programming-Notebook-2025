vector<int> adj[N];
int t = 0;
vector<int> tin(N, -1), low(N);
vector<array<int, 2>> ab;
void dfs (int u, int p) {
  tin[u] = low[u] = t++;
  for (int v: adj[u]) {
    if (v != p) {
      if (tin[v] != -1) {
        low[u] = min(low[u], tin[v]);
      } else {
        dfs(v, u);
        if (tin[u] < low[v]) {
          ab.push_back({u, v});
        }
        low[u] = min(low[u], low[v]);
      }
    }
  }
}