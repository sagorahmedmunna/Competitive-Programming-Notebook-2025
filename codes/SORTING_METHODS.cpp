// choose two adjacent elements and swap them / inversions count
vector<int> a;
int64_t mergeSort(int l, int r) {
  if (l >= r) return 0;
  int m = (l + r) / 2;
  int64_t ret = mergeSort(l, m) + mergeSort(m + 1, r);
  int i = l, j = m + 1;
  while (i <= m or j <= r) {
    if (j > r or (i <= m and a[i] < a[j])) i++;
    else j++, ret += m - i + 1;
  }
  inplace_merge(a.begin() + l, a.begin() + m + 1, a.begin() + r + 1);
  return ret;
}
int invCnt = mergeSort(0, n - 1);
// choose any element and move it to another position: n - LIS.
int lis(vector<int> p) {
  int n = p.size();
  vector<int> sorted;
  for (int i = 0; i < n; ++i) {
    auto it = lower_bound(sorted.begin(), sorted.end(), p[i]);
    if (it == sorted.end()) sorted.push_back(p[i]);
    else *it = p[i];
  } return sorted.size();
}
// choose any two elements and swap them: n - number_of_cycles.
int cyclesInPermutation(vector<int>& p) {
  int n = p.size(), cnt = 0;
  vector<bool> vis(n + 1);
  for (int i = 0; i < n; ++i) {
    if (vis[i]) continue;
    int j = i; cnt++;
    while (!vis[j]) {
      vis[j] = 1, j = p[j];
    }
  } return cnt;
}
// choose any element and move it to the front of the array: n - suffix_length
int longestSortedSuffix(vector<int>& p) {
  int n = p.size(), cnt = 0, curr = n - 1;
  for (int i = n - 1; i >= 0; i--) {
    if (p[i] == curr) curr--, cnt++;
  } return cnt;
}