int64_t sum[4 * N], lz[4 * N];
void Apply(int u, int v) {
  if (lz[v] != INF) lz[v] = (lz[v] * lz[u]) % mod;
  else lz[v] = lz[u];
}
void Push(int u, int l, int r) {
  if (lz[u] == INF) return;
  if (l != r) {
    Apply(u, 2 * u);
    Apply(u, 2 * u + 1);
  }
  sum[u] = (sum[u] * lz[u]) % mod;
  lz[u] = INF;
}
void Merge(int u, int v, int w) {
  sum[u] = (sum[v] + sum[w]) % mod;
}
void Build(int u = 1, int s = 0, int e = n) {
  if (s == e) {
    sum[u] = a[s]; // change
    lz[u] = INF;
    return;
  }
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  Build(v, s, m);
  Build(w, m + 1, e);
  Merge(u, v, w);
}
void Update(int l, int r, int64_t val, int u = 1, int s = 0, int e = n) {
  Push(u, s, e);
  if (e < l || r < s) return;
  if (l <= s && e <= r) { // change
    if (lz[u] != INF) lz[u] = (lz[u] * val) % mod;
    else lz[u] = val;
    Push(u, s, e);
    return;
  }
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  Update(l, r, val, v, s, m);
  Update(l, r, val, w, m + 1, e);
  Merge(u, v, w);
}
int64_t Query(int l, int r, int u = 1, int s = 0, int e = n) {
  Push(u, s, e);
  if (e < l || r < s) return 0;
  if (l <= s && e <= r) return sum[u]; // change
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  int64_t lSum = Query(l, r, v, s, m);
  int64_t rSum = Query(l, r, w, m + 1, e);
  return (lSum + rSum) % mod; // change
}
void BuildSeg() {
  for (int i = 0; i <= 4 * n; i++) {
    sum[i] = 0;
    lz[i] = INF;
  }
  Build();
}
int Idx_query(int l, int r, int u, int s, int e) {
  Push(u, s, e);
  if (e < l || r < s) return -1;
  if (s == e) return st[u].mn == 0 ? s : -1;
  int v = u << 1, w = v | 1, m = s + e >> 1;
  int lq = Idx_query(l, r, v, s, m);
  if (lq == -1) {
    return Idx_query(l, r, w, m + 1, e);
  }
  return lq;
}