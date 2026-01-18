/*
	Hungarian Algorithm: max weight assignment (rows → distinct columns)
	Input: cost matrix a[i][j] (0-based)
	Output: {max_sum, ans}, where ans[i] = column assigned to row i
	To get minimum assignment, negate the matrix values
*/
template<typename T>
pair<T, vector<int> > hungarian(const vector<vector<T> > &a) {
	if (a.empty()) return {0, {}};
	int n = a.size() + 1, m = a[0].size() + 1;
	vector<int> p(m), ans(n - 1);
	vector<T> u(n), v(m);
	for (int i = 1; i < n; i++) {
		p[0] = i;
		int now = 0;
		vector<int> pre(m, -1), vis(m + 1);
		vector<T> dis(m, numeric_limits<T>::max());
		do {
			vis[now] = true;
			int t = p[now], nxt;
			T d = numeric_limits<T>::max();
			for (int j = 1; j < m; j++)
				if (!vis[j]) {
					T cur = -a[t - 1][j - 1] - u[t] - v[j];
					if (cur < dis[j]) dis[j] = cur, pre[j] = now;
					if (dis[j] < d) d = dis[j], nxt = j;
				}
			for (int j = 0; j < m; j++) {
				if (vis[j]) u[p[j]] += d, v[j] -= d;
				else dis[j] -= d;
			}
			now = nxt;
		} while (p[now]);
		while (now) {
			int t = pre[now];
			p[now] = p[t], now = t;
		}
	}
	for (int i = 1; i < m; i++)
		if (p[i]) ans[p[i] - 1] = i - 1;
	return {v[0], ans};
}