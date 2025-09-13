using ll = long long;
const ll INF = 1.1e17;
vector<ll> Dijkstra(vector<vector<array<ll, 2>>>& adj, int source = 1) {
  int n = (int)adj.size();
  vector<ll> dis(n, INF);
  vector<bool> vis(n);
  dis[source] = 0;
  priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq;
  pq.push({0, source});
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (auto& [v, c] : adj[u]) {
      if (dis[v] > d + c) {
        dis[v] = d + c;
        pq.push({dis[v], v});
      }
    }
  }
  return dis;
}