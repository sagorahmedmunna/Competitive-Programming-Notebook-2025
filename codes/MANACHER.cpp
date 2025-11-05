struct Manacher { // 0 based
  int n; vector<int> p;
  Manacher(string& s) {
    n = s.size(); p.resize(2 * n);
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
  int odd_length_of_center_i(int i) { return p[i * 2]; }
  int even_length_of_center_i(int i) { return p[i * 2 + 1]; }
  vector<int> mxR, mxL;
  void longestPalindromeEndingAtEachPosition() {
    mxR.assign(n, 1);
    for (int i = 0; i < n; i++) {
      int l = p[i * 2];
      mxR[i + l / 2] = max(mxR[i + l / 2], l);
      l = p[i * 2 + 1];
      mxR[i + l / 2] = max(mxR[i + l / 2], l);
    }
    for (int i = n - 2; i >= 0; i--)
      mxR[i] = max(mxR[i], mxR[i + 1] - 2);
  }
  void longestPalindromeStartingAtEachPosition() {
    mxL.assign(n, 1); 
    for (int i = n - 1; i >= 0; i--) { 
      int l = p[i * 2];
      mxL[i - l / 2] = max(mxL[i - l / 2], l);
      l = p[i * 2 + 1];
      int idx = min(n - 1, i - l / 2 + 1);
      mxL[idx] = max(mxL[idx], l);
    }
    for (int i = 1; i < n; i++)
      mxL[i] = max(mxL[i], mxL[i - 1] - 2); 
  }
};