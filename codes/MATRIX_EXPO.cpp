// 0 based
typedef vector<int> row;
typedef vector<row> matrix;
inline int add(const int &a, const int &b) {
  int c = a + b;
  if (c >= MOD) c -= MOD;
  return c;
}
inline int mult(const int &a, const int &b) {
  return (long long)a * b % MOD;
}
matrix operator*(const matrix &m1, const matrix &m2) {
  int r = m1.size(), m = m1.back().size(), c = m2.back().size();
  matrix ret(r, row(c, 0));
  for (int i = 0; i < r; i++)
    for (int k = 0; k < m; k++)
      for (int j = 0; j < c; j++)
        ret[i][j] = add(ret[i][j], mult(m1[i][k], m2[k][j]));
  return ret;
}
matrix one(int dim) {
  matrix ret(dim, row(dim, 0));
  for (int i = 0; i < dim; i++)
    ret[i][i] = 1;
  return ret;
}
matrix operator^(const matrix &m, const int &e) {
  if (e == 0) return one(m.size());
  matrix sqrtm = m ^ (e / 2);
  matrix ret = sqrtm * sqrtm;
  if (e & 1) ret = ret * m;
  return ret;
}
// adj^k = number of walks of length k between nodes
int n, m, k; cin >> n >> m >> k; // nodes, edges, steps
matrix adj(n, row(n, 0));
for (int i = 0; i < m; i++) {
  int u, v; cin >> u >> v; u--; v--;
  adj[u][v] = add(adj[u][v], 1);
}
matrix ans = adj ^ k; // number of walks of length k
// print matrix of walks
for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j++)
    cout << ans[i][j] << " ";
  cout << "\n";
}