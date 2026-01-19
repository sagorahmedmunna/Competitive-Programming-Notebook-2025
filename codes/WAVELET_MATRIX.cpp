struct bitVec {
  vector<pair<int64_t, int>> b;
  bitVec(const vector<bool> &a): b((int)(a).size() / 64 + 1) {
    for (int i = 0; i < (int)(a).size(); ++i)
      b[i >> 6].first |= (int64_t)(a[i]) << (i & 63);
    for (int i = 0; i < (int)(b).size()-1; ++i)
      b[i + 1].second = __builtin_popcountll(b[i].first) + b[i].second;
  }
  int cnt0(int r) {
    auto [x, y] = b[r >> 6];
    return r - y - __builtin_popcountll(x & ((1ULL << (r & 63)) - 1));
  }
};
struct WaveletMatrix {
  int n; vector<bitVec> bv;
  WaveletMatrix(vector<int64_t> a, int64_t max_val): n((int)(a).size()), bv(1 + __lg(max_val), {{}}) {
    vector<int64_t> nxt(n);
    for (int h = (int)(bv).size(); h--;) {
      vector<bool> b(n);
      for (int i = 0; i < n; ++i) b[i] = ((a[i] >> h) & 1);
      bv[h] = b;
      array it{begin(nxt), begin(nxt) + bv[h].cnt0(n)};
      for (int i = 0; i < n; ++i) *it[b[i]]++ = a[i];
      swap(a, nxt);
    }
  }
  // k-th (0-indexed) largest number in a[l, r)
  int64_t kthSmallest(int l, int r, int k) {
    int64_t res = 0;
    for (int h = (int)(bv).size(); h--;) {
      int l0 = bv[h].cnt0(l), r0 = bv[h].cnt0(r);
      if (k < r0 - l0) l = l0, r = r0;
      else
        k -= r0 - l0, res |= 1ULL << h,
          l += bv[h].cnt0(n) - l0, r += bv[h].cnt0(n) - r0;
    }
    return res;
  }
  int kthLargest(int l, int r, int k) {
    return kthSmallest(l, r, r - l - k - 1);
  }
  // count i s.t. (l <= i < r) && (v[i] < upper)
  int rangeFreq(int l, int r, int64_t ub) {
    int res = 0;
    for (int h = (int)(bv).size(); h--;) {
      int l0 = bv[h].cnt0(l), r0 = bv[h].cnt0(r);
      if ((~ub >> h) & 1) l = l0, r = r0;
      else
        res += r0 - l0, l += bv[h].cnt0(n) - l0,
          r += bv[h].cnt0(n) - r0;
    }
    return res;
  }
  // count i s.t. (l <= i < r) && (lower <= v[i] < upper)
  int rangeFreq(int l, int r, int64_t lower, int64_t upper) {
    if (lower > upper) swap(lower, upper);
    return rangeFreq(l, r, upper) - rangeFreq(l, r, lower);
  }
  // max v[i] s.t. (l <= i < r) && (v[i] < upper)
  int64_t prevValue(int l, int r, int64_t upper) {
    int cnt = rangeFreq(l, r, upper);
    return cnt == 0 ? -1 : kthSmallest(l, r, cnt - 1);
  }
  // min v[i] s.t. (l <= i < r) && (lower <= v[i])
  int64_t nextValue(int l, int r, int64_t lower) {
    int cnt = rangeFreq(l, r, lower);
    return cnt == r - l ? -1 : kthSmallest(l, r, cnt);
  }
};