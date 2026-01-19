struct bitVec {
  vector<pair<ll, int>> b;
  bitVec(const vector<bool> &a): b((int)(a).size() / 64 + 1) {
    for (int i = 0; i < (int)(a).size(); ++i)
      b[i >> 6].first |= (ll)(a[i]) << (i & 63);
    for (int i = 0; i < (int)(b).size()-1; ++i)
      b[i + 1].second = __builtin_popcountll(b[i].first) + b[i].second;
  }
  int cnt0(int r) {
    pair<ll, int> p = b[r >> 6];
    ll x = p.first;
    int y = p.second;
    return r - y - __builtin_popcountll(x & ((1ULL << (r & 63)) - 1));
  }
};
struct WaveletMatrix {
  int n; vector<bitVec> bv;
  vector<vector<ll>> pref;
  WaveletMatrix(vector<ll> a, ll max_val): n((int)(a).size()), bv(1 + __lg(max_val), {{}}), pref(1 + __lg(max_val)) {
    vector<ll> nxt(n);
    for (int h = (int)(bv).size(); h--;) {
      vector<bool> b(n);
      for (int i = 0; i < n; ++i) b[i] = ((a[i] >> h) & 1);
      bv[h] = b;
      int cnt0 = bv[h].cnt0(n);
      ll* it[2] = {nxt.data(), nxt.data() + cnt0};
      for (int i = 0; i < n; ++i) *it[b[i]]++ = a[i];
      pref[h].resize(n + 1);
      pref[h][0] = 0;
      for (int i = 0; i < n; ++i) pref[h][i + 1] = pref[h][i] + nxt[i];
      swap(a, nxt);
    }
  }
  // count i s.t. (l <= i < r) && (v[i] == x)
  int rank(int l, int r, ll x) {
    for (int h = (int)(bv).size(); h--;) {
      int l0 = bv[h].cnt0(l), r0 = bv[h].cnt0(r);
      if ((x >> h) & 1) {
        l += bv[h].cnt0(n) - l0;
        r += bv[h].cnt0(n) - r0;
      } else {
        l = l0, r = r0;
      }
    }
    return r - l;
  }
  // k-th (0-indexed) largest number in a[l, r)
  ll kthSmallest(int l, int r, int k) {
    ll res = 0;
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
  int rangeFreq(int l, int r, ll ub) {
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
  int rangeFreq(int l, int r, ll lower, ll upper) {
    if (lower > upper) swap(lower, upper);
    return rangeFreq(l, r, upper) - rangeFreq(l, r, lower);
  }
  // sum of v[i] s.t. (l <= i < r) && (v[i] <= k)
  ll sumLTE(int l, int r, ll k) {
    ll res = 0;
    for (int h = (int)(bv).size(); h--;) {
      int l0 = bv[h].cnt0(l), r0 = bv[h].cnt0(r);
      if ((k >> h) & 1) {
        res += pref[h][r0] - pref[h][l0];
        l += bv[h].cnt0(n) - l0;
        r += bv[h].cnt0(n) - r0;
      } else {
        l = l0, r = r0;
      }
    }
    if (l < r) res += pref[0][r] - pref[0][l];
    return res;
  }
  // sum of v[i] s.t. (l <= i < r) && (lower <= v[i] <= upper)
  ll sumBetween(int l, int r, ll lower, ll upper) {
    return sumLTE(l, r, upper) - sumLTE(l, r, lower - 1);
  }
  // max v[i] s.t. (l <= i < r) && (v[i] < upper)
  ll prevValue(int l, int r, ll upper) {
    int cnt = rangeFreq(l, r, upper);
    return cnt == 0 ? -1 : kthSmallest(l, r, cnt - 1);
  }
  // min v[i] s.t. (l <= i < r) && (lower <= v[i])
  ll nextValue(int l, int r, ll lower) {
    int cnt = rangeFreq(l, r, lower);
    return cnt == r - l ? -1 : kthSmallest(l, r, cnt);
  }
};