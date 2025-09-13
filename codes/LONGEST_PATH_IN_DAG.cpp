vector<int> adj[N];
int dp[N], vis[N], n; 
int dfs (int u) {
	vis[u] = dp[u] = 1;
	for (int v : adj[u]) {
		if (!vis[v]) dfs(v);
		dp[u] = max(dp[u], dp[v] + 1);  
	} return dp[u]; 
}
int longestpath() {
	int ans = 0;
	for (int i = 1; i <= n; i++) 
		if (!vis[i]) ans = max(ans, dfs(i));
	return ans; 
}