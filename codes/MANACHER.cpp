struct Manacher { // 0 based
  int n;
  vector<int> p;
  Manacher(string& s) {
    n = s.size();
    p.resize(2 * n);
    build(s);
  }
  void build(string& s) {
    for (int i = 0, j = 0, k; i < n * 2; i += k, j = max(j - k, 0)) {
      while (i >= j && i + j + 1 < n * 2 && s[(i - j) / 2] == s[(i + j + 1) / 2]) ++j;
      p[i] = j;
      for (k = 1; i >= k && j >= k && p[i - k] != j - k; ++k) {
        p[i + k] = min(p[i - k], j - k);
      }
    }
  }
  bool is_palindrome(int l, int r) {
    int len = (r - l + 1), idx = -1;
    if (len & 1) idx = (l + len / 2) * 2;
    else idx = (l + len / 2 - 1) * 2 + 1;
    return p[idx] >= len;
  }
  int odd_length_of_center_i(int i) {return p[i * 2]; }
  int even_length_of_center_i(int i) { return p[i * 2 + 1]; }
};