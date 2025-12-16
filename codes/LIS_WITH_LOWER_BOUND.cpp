int lis(vector<int> p) {
  int n = p.size();
  vector<int> sorted;
  for (int i = 0; i < n; ++i) {
    auto it = lower_bound(sorted.begin(), sorted.end(), p[i]);
    if (it == sorted.end()) sorted.push_back(p[i]);
    else *it = p[i];
  }
  return sorted.size();
}