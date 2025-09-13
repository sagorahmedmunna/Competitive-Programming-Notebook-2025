vector<int> f(n), g(n);
for (int i = 1; i < N; i++) {
  for (int j = i; j < N; j += i) {
    f[i] += cnt[j];
  }
  f[i] = nC2(f[i]);
}
for (int i = N - 1; i > 0; i--) {
  g[i] = f[i];
  for (int j = i * 2; j < N; j += i) {
    g[i] -= g[j];
  }
}
// g[i] = how many pairs have gcd i