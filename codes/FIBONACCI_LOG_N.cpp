pair<ll, ll> fib_pair(ll n) {
  if (n == 0) return {0, 1};
  auto p = fib_pair(n >> 1);
  ll c = p.first * ((2 * p.second - p.first + mod) % mod) % mod;
  ll d = (p.first * p.first % mod + p.second * p.second % mod) % mod;
  if (n & 1) return {d, (c + d) % mod};
  return {c, d};
}
ll fibonacci(ll n) {
  return fib_pair(n).first;
}