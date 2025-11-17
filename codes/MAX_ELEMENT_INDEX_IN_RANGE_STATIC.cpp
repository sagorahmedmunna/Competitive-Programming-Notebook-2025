const int N = 1e5 + 9;
const int LOG = 20;
int n, a[N], st[N][LOG], lg[N];
void Preprocess() {
  for (int i = 2; i < N; ++i) lg[i] = lg[i / 2] + 1;
}
// max element index in (l to r)
void build() {
  if (lg[2] == 0) Preprocess();
  for (int j = 0; j < LOG; j++) {
    for (int i = 0; i + (1 << j) - 1 <= n; i++) {
      if (j == 0) st[i][j] = i;
      else {
        if (a[st[i][j - 1]] > a[st[i + (1 << (j - 1))][j - 1]]) st[i][j] = st[i][j - 1];
        else st[i][j] = st[i + (1 << (j - 1))][j - 1];
      }
    }
  }
}
int query(int l, int r) {
  if (l > r) return -1;
  int k = lg[r - l + 1];
  if (a[st[l][k]] > a[st[r - (1 << k) + 1][k]]) return st[l][k];
  return st[r - (1 << k) + 1][k];
}