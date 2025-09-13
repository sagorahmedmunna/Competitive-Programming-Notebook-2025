void CompressArray(vector<int>& a) {
  auto b = a;
  sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());
  for (auto& ai : a) {
    ai = lower_bound(b.begin(), b.end(), ai) - b.begin();
  }
}