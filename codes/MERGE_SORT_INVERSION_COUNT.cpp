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