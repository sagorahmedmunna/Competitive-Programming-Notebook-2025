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

int KMPSearch(string& text, string& pattern) {
  int n = text.size(), m = pattern.size();
  auto lps = get_pi(pattern);
  int total = 0;
  for (int i = 0, j = 0; i < n; ) {
    if (pattern[j] == text[i]) j++, i++;
    if (j == m) {
      total++, j = lps[j - 1];
    } else if (i < n && pattern[j] != text[i]) {
      if (j != 0) j = lps[j - 1];
      else i = i + 1;
    }
  }
  return total;
}
const int N = 1e5 + 9;
int aut[N][26];
void compute_automaton(const string& s) {
  string t = s + '#';
  int n = t.size();
  auto pi = get_pi(t);
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < 26; c++) {
      if (i > 0 && 'a' + c != t[i])
        aut[i][c] = aut[pi[i - 1]][c];
      else
        aut[i][c] = i + ('a' + c == t[i]);
    }
  }
}