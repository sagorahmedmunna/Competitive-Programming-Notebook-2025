template <class T> struct SegmentTreeIterative {
  int n = 1;
  vector<T> st;
  SegmentTreeIterative() {}
  SegmentTreeIterative(int n) { Initial(n); }
  SegmentTreeIterative(vector<int>& a) {
    Initial((int)a.size() - 1);
    Build(a);
  }
  void Initial(int _n) {
    n = _n;
    int tree_size = 1;
    while (tree_size <= n) tree_size *= 2;
    st.resize(tree_size * 2);
  }
  T neutral = INT_MAX; #change
  T Merge(T& a, T& b) { #change
    return min(a, b);
  }
  void Build(vector<int>& a) {
    for (int i = 1; i <= n; ++i) {
      st[n + i] = a[i];
    }
    for (int u = n - 1; u > 0; --u) {
      st[u] = Merge(st[u << 1], st[u << 1 | 1]);
    }
  }
  void Update(int idx, T val) {
    st[idx += n] = val;
    for (idx /= 2; idx; idx /= 2) {
      st[idx] = Merge(st[idx << 1], st[idx << 1 | 1]);
    }
  }
  T Query(int l, int r) {
    T res = neutral;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = Merge(res, st[l++]);
      if (r & 1) res = Merge(res, st[--r]);
    }
    return res;
  }
};