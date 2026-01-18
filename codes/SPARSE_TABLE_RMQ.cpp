const int N = (int)2e5 + 9;
int lg[N];
void Preprocess() {
  for (int i = 2; i < N; ++i) lg[i] = lg[i / 2] + 1;
}
template <class T> struct RMQ {
  int n = 1, LOG = 1;
  vector<vector<T>> st;
  T Merge(T& a, T& b) {
    return min(a, b); #change
  }
  RMQ(vector<T>& a) {
    if (lg[2] == 0) Preprocess();
    n = (int)a.size(), LOG = __lg(n) + 1;
    st.assign(n, vector<T> (LOG));
    for (int j = 0; j < LOG; j++) {
      for (int i = 0; i + (1 << j) - 1 < n; i++) {
        if (j == 0) st[i][j] = a[i];
        else st[i][j] = Merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  T Query(int l, int r) {
    // if (l > r) return 0;
    int k = lg[r - l + 1];
    return Merge(st[l][k], st[r - (1 << k) + 1][k]);
  }
};