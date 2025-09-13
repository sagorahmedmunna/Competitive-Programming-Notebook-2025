// clear everything first, 1 based
// reverse scc for topological order
const int N = 5e5 + 10; 
vector<int> adj[N], trans[N], scc[N];
int col[N], vis[N], idx = 0, n, m; 
stack<int> st;
void dfs(int u) {
  vis[u] = 1;
  for (int v : adj[u]) if (!vis[v]) dfs(v);
  st.push(u);
}
void dfs2(int u) {
  col[u] = idx;
  scc[idx].push_back(u);
  for (int v : trans[u]) if (!col[v]) dfs2(v);
}
void findSCC() {
  for (int i = 1; i <= n; i++) 
    if(!vis[i]) dfs(i);
  for (int u = 1; u <= n; u++)
    for (int v : adj[u]) 
      trans[v].push_back(u);
  while (!st.empty()) {
    int u = st.top(); st.pop();
    if (col[u]) continue; 
    idx++; dfs2(u); 
  } 
}
// take input and call findSCC();