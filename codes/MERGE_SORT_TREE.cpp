// add ordered multiset
struct MergeSortTree {
  int size = 1;
  vector<ordered_multiset<int>> st; #change
  MergeSortTree(vector<int>& a) {
    Initial((int)a.size() - 1);
    Build(1, 1, size, a);
  }
  void Initial(int _n) {
    size = _n;
    int tree_size = 1;
    while (tree_size < _n) tree_size *= 2;
    st.resize(tree_size * 2);
  }
  void Build(int u, int s, int e, vector<int>& a) {
    if (s == e) { #change
      st[u].insert(a[s]);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    Build(v, s, m, a);
    Build(w, m + 1, e, a);
    for (int i = s; i <= e; i++) st[u].insert(a[i]);
  }
  void Update(int u, int s, int e, int k, int prev, int curr) {
    if (s == e) { #change
      st[u].erase(st[u].find_by_order(st[u].order_of_key(prev)));
      st[u].insert(curr);
      return;
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    if (k <= m) Update(v, s, m, k, prev, curr);
    else Update(w, m + 1, e, k, prev, curr);
    #change
    st[u].erase(st[u].find_by_order(st[u].order_of_key(prev)));
    st[u].insert(curr);
  }
  void Update(int k, int prev, int curr) {
    Update(1, 1, size, k, prev, curr);
  }
  int Query(int u, int s, int e, int l, int r, int val) {
    if (e < l || r < s) { #change
      return 0;
    }
    if (l <= s && e <= r) { #change
      return st[u].order_of_key(val);
    }
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    int lsum = Query(v, s, m, l, r, val);
    int rsum = Query(w, m + 1, e, l, r, val);
    return lsum + rsum; #change
  }
  int Query(int l, int r, int val) {
    return Query(1, 1, size, l, r, val);
  }
};