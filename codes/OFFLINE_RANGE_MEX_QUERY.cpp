struct SegmentTree {
  int n; vector<int> st;
  SegmentTree(int sz) {
    n = 1;
    while (n < sz) n *= 2;
    st.assign(n * 2, 0);
  }
  void update(int idx, int val) {
    st[idx += n] = val;
    for (idx /= 2; idx; idx /= 2) {
      st[idx] = min(st[idx << 1], st[idx << 1 | 1]);
    }
  }
  int mex(int l) {
    int u = 1;
    while (u < n) {
      int lc = u << 1;
      if (st[lc] < l) u = lc;
      else u = lc + 1;
    }
    return u - n;
  }
};
// update last occurence of each value with index of array 
// find the lowest segmentree index which is less then current range "L"
const int N = 2e5 + 9;
vector<array<int, 2>> queries[N];
int n, a[N], res[N];
void getMex() {
  SegmentTree sg(N);
  for (int i = 1; i <= n; i++) {
    sg.update(a[i], i);
    for (auto& [l, idx] : queries[i]) {
      res[idx] = sg.mex(l);
    }
  }
}