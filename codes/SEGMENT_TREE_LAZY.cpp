const long long INF = 1.1e17;
struct node { #change
  long long sum, lazy_add;
  node() {
    sum = 0;
    lazy_add = INF;
  }
};
struct SegmentTreeLazy {
  int size = 1;
  vector<node> st;
  SegmentTreeLazy() {}
  SegmentTreeLazy(int n) { Initial(n); }
  SegmentTreeLazy(vector<int>& a) {
    Initial((int)a.size() - 1);
    Build(1, 0, size, a);
  }
  void Initial(int _n) {
    size = _n;
    int tree_size = 1;
    while (tree_size <= size) tree_size *= 2;
    st.resize(tree_size * 2);
  }
  node Make_node(long long val) { #change
    node res;
    res.sum = val;
    res.lazy_add = INF;
    return res;
  }
  node Merge(node& l, node& r) { #change
    node res;
    res.sum = l.sum + r.sum;
    return res;
  }
  void Push(int u, int l, int r) { #change
    if (st[u].lazy_add == INF) return;
    if (l != r) {
      int v = 2 * u, w = 2 * u + 1;
      if (st[v].lazy_add != INF) st[v].lazy_add += st[u].lazy_add;
      else st[v].lazy_add = st[u].lazy_add;
      if (st[w].lazy_add != INF) st[w].lazy_add += st[u].lazy_add;
      else st[w].lazy_add = st[u].lazy_add;
    }
    st[u].sum += (r - l + 1) * st[u].lazy_add;
    st[u].lazy_add = INF;
  }
  void Build(int u, int s, int e, vector<int>& a) {
    if (s == e) {
      st[u] = Make_node(a[s]);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    Build(v, s, m, a);
    Build(w, m + 1, e, a);
    st[u] = Merge(st[v], st[w]);
  }
  void Update(int u, int s, int e, int l, int r, long long val) {
    Push(u, s, e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) { #change
      if (st[u].lazy_add != INF) st[u].lazy_add += val;
      else st[u].lazy_add = val;
      Push(u, s, e);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    Update(v, s, m, l, r, val);
    Update(w, m + 1, e, l, r, val);
    st[u] = Merge(st[v], st[w]);
  }
  void Update(int l, int r, long long val) {
    Update(1, 0, size, l, r, val);
  }
  node Query(int u, int s, int e, int l, int r) {
    Push(u, s, e);
    if (e < l || r < s) { #change
      return node();
    }
    if (l <= s && e <= r) return st[u];
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    node lsum = Query(v, s, m, l, r);
    node rsum = Query(w, m + 1, e, l, r);
    return Merge(lsum, rsum);
  }
  node Query(int l, int r) {
    return Query(1, 0, size, l, r);
  }
  int Idx_query(int u, int s, int e, int l, int r) {
    Push(u, s, e);
    if (e < l || r < s) return -1;
    if (s == e) return st[u].mn == 0 ? s : -1;
    int v = u << 1, w = v | 1, m = s + e >> 1;
    int lq = Idx_query(v, s, m, l, r);
    if (lq == -1) {
      return Idx_query(w, m + 1, e, l, r);
    }
    return lq;
  }
  int Idx_query(int l, int r) {
    return Idx_query(1, 0, size, l, r);
  }
};