// length of longest proper prefix of P[0...i] that is also a suffix of P[0...i]
// Pattern: a b a b a c a
// Index:   0 1 2 3 4 5 6
// LPS[]:   0 0 1 2 3 0 1
vector<int> get_pi(string& s) {
  int n = s.size();
  vector<int> pi(n);
  for (int i = 1, j = 0; i < n; i++) {
    if (s[i] == s[j]) pi[i] = ++j;
    else if (j == 0) pi[i] = 0;
    else j = pi[j - 1], i--;
  }
  return pi;
}
// count the number of p occurs in s
string s, p;
s = p + "#" + s;
vector<int> pi = get_pi(s);
int ans = 0;
for (auto& i : pi) ans += (i == p.size());