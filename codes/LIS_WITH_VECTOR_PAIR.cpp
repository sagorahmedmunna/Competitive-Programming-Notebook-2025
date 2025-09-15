vector<int> lis(vector<int> a) {
  int n = a.size();
  if(n == 0) return {};
  vector<pair<int, int>> sorted;
  vector<int> prev(n);
  for (int i = 0; i < n; ++i) {
    auto it = lower_bound(sorted.begin(), sorted.end(), make_pair(a[i], 0));
    if (it == sorted.end()) {
      sorted.emplace_back();
      it = sorted.end()-1;
    }
    *it = {a[i], i};
    prev[i] = it == sorted.begin() ? 0 : (it-1)->second;
  }
  int l = sorted.size();
  int cur = sorted.back().second;
  vector<int> ret(l);
  while (l--){
    ret[l] = cur;
    cur = prev[cur];
  }
  return ret;
}