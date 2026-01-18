// 0 based, longest substring lenght starting at position i that is also a prefix
// String: a b c a b c b b
// Index:  0 1 2 3 4 5 6 7
// Z[]:    - 0 0 3 0 0 0 0
vector<int> get_z(string& s) {
  int n = s.size(), l = 0, r = 0;
  vector<int> z(n); z[0] = n;
  for (int i = 1; i < n; i++) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] > r) l = i, r = i + z[i];
  } return z;
}