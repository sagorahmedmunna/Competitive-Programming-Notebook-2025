struct node { #change
  long long sum, pref, suff, ans;
  node() {
    sum = pref = suff = ans = 0;
  }
};
struct SegmentTree {
  int size = 1;
  vector<node> st;
  SegmentTree(vector<int>& a) {
    Initial((int)a.size() - 1);
    Build(1, 0, size, a);
  }
  void Initial(int _n) {
    size = _n;
    int tree_size = 1;
    while (tree_size <= size) tree_size *= 2;
    st.resize(tree_size * 2);
  }
  node Make_node(int val) { #change
    node res;
    res.sum = val;
    res.pref = res.suff = res.ans = max(0, val);
    return res;
  }
  node Merge(node& l, node& r) { #change
    node res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max(max(l.ans, r.ans), l.suff + r.pref);
    return res;
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
  void Update(int u, int s, int e, int k, long long val) {
    if (s == e) { #change
      st[u] = Make_node(val);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    if (k <= m) Update(v, s, m, k, val);
    else Update(w, m + 1, e, k, val);
    st[u] = Merge(st[v], st[w]);
  }
  void Update(int k, long long val) {
    Update(1, 0, size, k, val);
  }
  node Query(int u, int s, int e, int l, int r) {
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
};