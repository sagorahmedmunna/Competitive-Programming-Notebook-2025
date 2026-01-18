// returns gcd(a, b) and sets x, y such that a*x + b*y = gcd(a,b)
ll extendedGCD(ll a, ll b, ll &x, ll &y) {
  if (b == 0) { x = 1, y = 0; return a; }
  ll x1, y1;
  ll d = extendedGCD(b, a % b, x1, y1);
  x = y1, y = x1 - (a / b) * y1;
  return d;
}
// a*x ≡ 1 (mod m) -> x is the modular inverse of a modulo m
ll modInv(ll a, ll m) {
  ll x, y;
  ll g = extendedGCD(a, m, x, y);
  if (g != 1) return -1;
  return (x % m + m) % m;
}
// returns all solutions to a*x ≡ b (mod m) -> (g should be small)
vector<ll> solveModEquation(ll a, ll b, ll m) {
  ll x, y;
  ll g = extendedGCD(a, m, x, y);
  vector<ll> sol;
  if (b % g != 0) return sol;
  ll x0 = (x * (b / g)) % m;
  if (x0 < 0) x0 += m;
  ll mod = m / g;
  for (int k = 0; k < g; k++) {
    sol.push_back((x0 + k * mod) % m);
  } return sol;
}
// Merge two congruences: x ≡ a1 mod m1, x ≡ a2 mod m2
pair<ll,ll> merge(ll a1, ll m1, ll a2, ll m2) {
  ll x, y;
  ll g = extendedGCD(m1, m2, x, y);
  if ((a2 - a1) % g != 0) return {-1,-1};
  ll lcm = m1 / g * m2;
  ll k = ((a2 - a1) / g % (m2 / g) + (m2 / g)) % (m2 / g);
  k = k * ((x % (m2 / g) + (m2 / g)) % (m2 / g)) % (m2 / g);
  ll res = (a1 + m1 * k) % lcm;
  if (res < 0) res += lcm;
  return {res, lcm};
}
// Returns {x, mod} or {-1,-1} if no solution
// ans.first = the smallest non-negative solution x
// ans.second = the modulus of the solution, i.e., the LCM of all input moduli
pair<ll,ll> CRT(const vector<ll> &a, const vector<ll> &m) {
  ll x = a[0], mod = m[0];
  for (int i = 1; i < a.size(); i++) {
    auto res = merge(x, mod, a[i], m[i]);
    if (res.first == -1) return {-1,-1};
    x = res.first;
    mod = res.second;
  } return {x, mod};
}
/*
  x ≡ a1 (mod m1)
  x ≡ a2 (mod m2)
  ...
  x ≡ an (mod mn)
*/
vector<long long> a = {2, 3, 2};
vector<long long> m = {3, 5, 8};
auto ans = CRT(a, m);