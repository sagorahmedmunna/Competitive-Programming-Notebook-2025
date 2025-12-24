// LIS
const int N = 1001;
int n, m, a[N], b[N], dp[N][N];
int f(int i, int j) {
  if (i >= n || j >= m) return 0;
  auto& ret = dp[i][j];
  if (~ret) return ret;
  if (a[i] == b[j]) {
    ret = f(i + 1, j + 1) + 1;
  } else {
    ret = max(ret, f(i + 1, j));
    ret = max(ret, f(i, j + 1));
  }
  return ret;
}
void g(int i, int j, int len) {
  if (len == 0 || i >= n || j >= n) return;
  if (a[i] == b[j]) {
    cout << a[i] << ' ';
    g(i + 1, j + 1, len - 1);
  } else {
    if (f(i + 1, j) >= f(i, j + 1)) g(i + 1, j, len);
    else g(i, j + 1, len);
  }
}
f(0, 0);
g(0, 0, len);