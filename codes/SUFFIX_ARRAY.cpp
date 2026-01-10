/*
  for integer, just change string to vector<int> and minimum value of vector must be >= 1
  for integer, lim will be the maximum value of the array
  LCP of suffix (sa[i], sa[i + 1]) = lcp[i]
  O(nlogn)
*/
array<vector<int>, 2> get_sa(string& s, int lim = 128) {
  int n = s.size() + 1, k = 0, a, b;
  vector<int> x(begin(s), end(s) + 1), y(n), sa(n), lcp(n), ws(max(n, lim)), rank(n);
  x.back() = 0;
  iota(begin(sa), end(sa), 0);
  for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
    p = j, iota(begin(y), end(y), n - j);
    for (int i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
    fill(begin(ws), end(ws), 0);
    for (int i = 0; i < n; ++i) ws[x[i]]++;
    for (int i = 1; i < lim; ++i) ws[i] += ws[i - 1];
    for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
    swap(x, y), p = 1, x[sa[0]] = 0;
    for (int i = 1; i < n; ++i) a = sa[i - 1], b = sa[i],
      x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
  }
  for (int i = 1; i < n; ++i) rank[sa[i]] = i;
  for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
    for (k && k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++);
  sa.erase(sa.begin()), lcp.erase(lcp.begin());
  lcp.push_back(lcp[0]), lcp.erase(lcp.begin());
  return {sa, lcp};
}

/*
  O(|S| + |alphabet|) Suffix Array
  LIM := max{s[i]} + 2
  LCP of suffix (sa[i], sa[i + 1]) = lcp[i]
*/
void inducedSort(const vector<int>& vec, int val_range, vector<int>& SA, const vector<int>& sl, const vector<int>& lms_idx) {
  vector<int> l(val_range, 0), r(val_range, 0);
  for (int c : vec) {
    ++r[c]; if (c + 1 < val_range) ++l[c + 1];
  }
  partial_sum(l.begin(), l.end(), l.begin());
  partial_sum(r.begin(), r.end(), r.begin());
  fill(SA.begin(), SA.end(), -1);
  for (int i = lms_idx.size() - 1; i >= 0; --i) SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
  for (int i : SA) if (i > 0 and sl[i - 1]) SA[l[vec[i - 1]]++] = i - 1;
  fill(r.begin(), r.end(), 0);
  for (int c : vec) ++r[c];
  partial_sum(r.begin(), r.end(), r.begin());
  for (int k = SA.size() - 1, i = SA[k]; k; --k, i = SA[k]) {
    if (i and !sl[i - 1]) SA[--r[vec[i - 1]]] = i - 1;
  }
}
vector<int> suffixArray(const vector<int>& vec, int val_range) {
  const int n = vec.size();
  vector<int> sl(n), SA(n), lms_idx;
  for (int i = n - 2; i >= 0; --i) {
    sl[i] = vec[i] > vec[i + 1] or (vec[i] == vec[i + 1] and sl[i + 1]);
    if (sl[i] and !sl[i + 1]) lms_idx.emplace_back(i + 1);
  }
  reverse(lms_idx.begin(), lms_idx.end());
  inducedSort(vec, val_range, SA, sl, lms_idx);
  vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
  for (int i = 0, k = 0; i < n; ++i) {
    if (SA[i] > 0 and !sl[SA[i]] and sl[SA[i] - 1]) new_lms_idx[k++] = SA[i];
  }
  int cur = 0; SA[n - 1] = 0;
  for (int k = 1; k < new_lms_idx.size(); ++k) {
    int i = new_lms_idx[k - 1], j = new_lms_idx[k];
    if (vec[i] ^ vec[j]) {
      SA[j] = ++cur; continue;
    }
    bool flag = 0;
    for (int a = i + 1, b = j + 1; ; ++a, ++b) {
      if (vec[a] ^ vec[b]) {
        flag = 1; break;
      }
      if ((!sl[a] and sl[a - 1]) or (!sl[b] and sl[b - 1])) {
        flag = !(!sl[a] and sl[a - 1] and !sl[b] and sl[b - 1]); break;
      }
    }
    SA[j] = flag ? ++cur : cur;
  }
  for (int i = 0; i < lms_idx.size(); ++i) lms_vec[i] = SA[lms_idx[i]];
  if (cur + 1 < lms_idx.size()) {
    auto lms_SA = suffixArray(lms_vec, cur + 1);
    for (int i = 0; i < lms_idx.size(); ++i) new_lms_idx[i] = lms_idx[lms_SA[i]];
  }
  inducedSort(vec, val_range, SA, sl, new_lms_idx); return SA;
}
vector<int> getSuffixArray(const string& s, const int LIM = 128) { // change limit for integer array, (integer > 0)
  vector<int> vec(s.size() + 1);
  copy(begin(s), end(s), begin(vec)); vec.back() = '!';
  auto ret = suffixArray(vec, LIM);
  ret.erase(ret.begin()); return ret;
}
// build RMQ on it to get LCP of any two suffix
vector<int> getLCParray(const string& s, const vector<int>& SA) {
  int n = s.size(), k = 0;
  vector<int> lcp(n), rank(n);
  for (int i = 0; i < n; ++i) rank[SA[i]] = i;
  for (int i = 0; i < n; ++i, k ? --k : 0) {
    if (rank[i] == n - 1) {
      k = 0; continue;
    }
    int j = SA[rank[i] + 1];
    while (i + k < n and j + k < n and s[i + k] == s[j + k]) ++k;
    lcp[rank[i]] = k;
  }
  lcp[n - 1] = 0; return lcp;
}
int lower_bound(string& s, string& t, vector<int>& sa) {
  int n = s.size(), m = t.size(), lo = 0, hi = n - 1;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (s.substr(sa[mid], m) < t) lo = mid + 1;
    else hi = mid - 1;
  }
  return lo;
}
int upper_bound(string& s, string& t, vector<int>& sa) {
  int n = s.size(), m = t.size(), lo = 0, hi = n - 1;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (s.substr(sa[mid], m) <= t) lo = mid + 1;
    else hi = mid - 1;
  }
  return lo;
}
int find_occurrence(string& s, string& t, vector<int>& sa) {
  return upper_bound(s, t, sa) - lower_bound(s, t, sa);
}
const int N = 1e6 + 9;
int64_t distPref[N];
void kthSubstringDistinctPreprocess(vector<int>& sa, vector<int>& lcp) {
  int last = 0, n = sa.size();
  for (int i = 0; i < n; i++) {
    distPref[i] = n - sa[i] - last;
    if (i) distPref[i] += distPref[i - 1];
    last = lcp[i];
  }
}
array<int, 2> kthSubstringDistinctPos(string& s, int64_t k, vector<int>& sa, vector<int>& lcp) {
  int n = s.size(); k--;
  int i = upper_bound(distPref, distPref + n, k) - distPref;
  int len = k - (i == 0 ? 0 : distPref[i - 1]) + (i == 0 ? 0 : lcp[i - 1]) + 1;
  return {i, len};
}
string kthSubstringDistinct(string& s, int64_t k, vector<int>& sa, vector<int>& lcp) {
  auto [i, len] = kthSubstringDistinctPos(s, k, sa, lcp);
  return s.substr(sa[i], len);
}
int64_t pref[N];
void kthSubstringPreprocess(vector<int>& sa) {
  int n = sa.size();
  for (int i = 0; i < n; i++) {
    pref[i] = n - sa[i];
    if (i) pref[i] += pref[i - 1];
  }
}
string kthSubstring(string& s, int64_t k, vector<int>& sa, vector<int>& lcp) {
  int n = s.size();
  int64_t lo = 1, hi = distPref[n - 1];
  while (lo <= hi) {
    int64_t mid = (lo + hi) >> 1;
    auto [i, len] = kthSubstringDistinctPos(s, mid, sa, lcp);
    int64_t totCnt = (i == 0 ? 0 : pref[i - 1]) + len;
    int mn = len;
    for (int j = i; j < n; j++) {
      mn = min(mn, lcp[j]);
      if (mn == 0) break;
      totCnt += mn;
    }
    if (totCnt < k) lo = mid + 1;
    else hi = mid - 1;
  }
  return kthSubstringDistinct(s, lo, sa, lcp);
}
int main() {
  string s;
  auto sa = getSuffixArray(s);
  auto lcp = getLCParray(s, sa);
  kthSubstringDistinctPreprocess(sa, lcp);
  kthSubstringPreprocess(sa);
}