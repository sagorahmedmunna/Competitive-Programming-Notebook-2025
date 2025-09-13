struct FenWick2D {
  int n, m;
  vector<vector<long long>> ft;
  FenWick2D() {}
  FenWick2D(int _n, int _m) {
    n = _n, m = _m;
    ft.assign(n + 1, vector<long long> (m + 1));
  }
  void Add(int x, int y, long long val) {
    for(int i = x; i <= n; i += i & -i) {
      for(int j = y; j <= m; j += j & -j) {
        ft[i][j] += val;
      }
    }
  }
  long long Csum(int x, int y) {
    long long res = 0;
    for(int i = x; i > 0; i -= i & -i) {
      for(int j = y; j > 0; j -= j & -j) {
        res += ft[i][j];
      }
    }
    return res;
  }
  long long Rsum(int x1, int y1, int x2, int y2) {
    return Csum(x2, y2) - Csum(x1 - 1, y2) - Csum(x2, y1 - 1) + Csum(x1 - 1, y1 - 1);
  }
};