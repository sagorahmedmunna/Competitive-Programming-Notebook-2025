void FloydWarshall(vector<vector<long long>>& adj) {
  int n = (int)adj.size();
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
        adj[i][i] = 0;
      }
    }
  }
}