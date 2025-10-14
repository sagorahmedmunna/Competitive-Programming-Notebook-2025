// 0 based
// farthest index where each element is distinct
array<vector<int>, 2> farthestDistinctElementIndex(vector<int>& a) {
  int n = a.size(), mxIdx = -1;
  map<int, int> mp;
  vector<int> l(n);
  for (int i = 0; i < n; i++) {
    if (mp.count(a[i])) mxIdx = max(mxIdx, mp[a[i]]);
    mp[a[i]] = i, l[i] = mxIdx + 1;
  }
  mp.clear(), mxIdx = n;
  vector<int> r(n);
  for (int i = n - 1; i >= 0; i--) {
    if (mp.count(a[i])) mxIdx = min(mxIdx, mp[a[i]]);
    mp[a[i]] = i, r[i] = mxIdx - 1;
  }
  return {l, r};
}