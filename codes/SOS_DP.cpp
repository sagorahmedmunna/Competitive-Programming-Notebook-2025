const int mod = 1e9 + 7;
const int B = 20, N = (1 << B) + 9;
int f[N], g[N], pairF[N], pairG[N], subseqF[N], subseqG[N], Pow2[N];
void sub(int& a, int& b) { // a = a - b
  a -= b;
  if (a < 0) a += mod;
}
int nC2(int n) {
  return (n * 1LL * (n - 1) / 2) % mod;
}
void forward1() { // sum over subset
  for (int bit = 0; bit < B; bit++) {
    for (int i = 0; i < N; i++) {
      if (i & (1 << bit)) f[i] += f[i ^ (1 << bit)];
    }
  }
}
void backward1() { // exclude sebset sum
  for (int bit = 0; bit < B; bit++) {
    for (int i = N - 1; i >= 0; i--) {
      if (i & (1 << bit)) {
        // f[i] -= f[i ^ (1 << bit)];
        sub(pairF[i], pairF[i ^ (1 << bit)]);
        sub(subseqF[i], subseqF[i ^ (1 << bit)]);
      }
    }
  }
}
void forward2() { // sum over superset
  for (int bit = 0; bit < B; bit++) {
    for (int i = N - 1; i >= 0; i--) {
      if (i & (1 << bit)) g[i ^ (1 << bit)] += g[i];
    }
  }
}
void backward2() { // exclude superset sum
  for (int bit = 0; bit < B; bit++) {
    for (int i = 0; i < N; i++) {
      if (i & (1 << bit)) {
        // g[i ^ (1 << bit)] -= g[i];
        sub(pairG[i ^ (1 << bit)], pairG[i]);
        sub(subseqG[i ^ (1 << bit)], subseqG[i]);
      }
    }
  }
}
void sosDP(vector<int>& a) {
  Pow2[0] = 1;
  for (int i = 1; i < N; i++) Pow2[i] = (Pow2[i - 1] * 2) % mod;
  for (auto& ai : a) f[ai]++, g[ai]++;
  forward1(); forward2();
  for (int i = 0; i < N; i++) {
    // all pair (i < j)
    pairF[i] = nC2(f[i]), pairG[i] = nC2(g[i]);
    // subsequence
    subseqF[i] = Pow2[f[i]] - 1, subseqG[i] = Pow2[g[i]] - 1;
  }
  backward1(); backward2();
}
// x | y = x
int subMaskOf(int x) return f[x];
// x & y = x
int superMaskOf(int x) return g[x];
// y & z = x (i < j)
int countPairsWithAnd(int x) return pairG[x];
// y | z = x (i < j)
int countPairsWithOr(int x) return pairF[x];
int countSubseqWithAnd(int x) return subseqG[x];
int countSubseqWithOr(int x) return subseqF[x];

sosDP(a); // clear everything before use