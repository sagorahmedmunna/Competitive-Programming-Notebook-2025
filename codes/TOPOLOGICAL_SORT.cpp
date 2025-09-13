bool topological_sort(vector<vector<int>>& adj) {
  int n = adj.size();
  vector<int> in_degree(n + 1);
  for (int u = 1; u <= n; u++) {
    for (auto& v : adj[u]) in_degree[v]++;
  }
  // without sorting the order
  queue<int> q;
  // sort with lexicographically
  // priority_queue<int, vector<int>, greater<int>> q;
  for (int u = 1; u <= n; u++) {
    if (in_degree[u] == 0) {
      q.push(u);
    }
  }
  if (q.empty()) return 0;
  vector<int> order;
  while (!q.empty()) {
    # change the queue operation
    int u = q.front();
    q.pop();
    for (auto& v : adj[u]) {
      in_degree[v]--;
      if (in_degree[v] == 0) {
        q.push(v);
      }
    }
    order.push_back(u);
  }
  return (int)order.size() == n;
}