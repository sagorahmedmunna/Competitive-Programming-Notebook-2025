struct FenWickTree {
  int n;
  vector<ll> ft;
  FenWickTree(vector<int>& a) {
    Initial((int)a.size());
    Build(a);
  }
  void Initial(int _n) {
    n = _n;
    ft.assign(n + 1, 0);
  }
  void Build(vector<int>& a) {
    for (int i = 0; i < (int)a.size(); i++) Add(i, i, a[i]); #change
  }
  void Add(int idx, ll val) {
    for (int i = idx; i <= n; i += i & -i) ft[i] += val;
  }
  void Add(int l, int r, ll val) {
    Add(l, val);
    Add(r + 1, -val);
  }
  ll Csum(int idx) {
    ll res = 0;
    for (int i = idx; i > 0; i -= i & -i) res += ft[i];
    return res;
  }
  ll Rsum(int l, int r) {
    return Csum(r) - Csum(l - 1);
  }
};