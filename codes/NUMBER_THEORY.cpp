using ll = long long;
const int N = 1e6 + 9;
vector<int> lpf(N), gpf(N);
vector<array<int, 2>> factors[N];

// sieve for finding lowest prime and highest prime upto N
for (int i = 2; i < N; i++) {
  if (lpf[i] == 0) {
    for (int j = i; j < N; j += i) {
      gpf[j] = i;
      if (!lpf[j]) lpf[j] = i;
    }
  }
}
// find all factors upto N
for (int i = 2; i < N; i++) {
  int num = i;
  while (num > 1) {
    int p = lpf[num], cnt = 0;
    while (num > 1 && num % p == 0) {
      cnt++;
      num /= p;
    }
    factors[i].push_back({p, cnt});
  }
}
int num = 10;
int total_divisors = 1;
ll sum_of_divisors = 1;
for (auto& [p, c] : factors[num]) {
  total_divisors *= (c + 1);
  sum_of_divisors *= (pow(p, c + 1) - 1) / (p - 1);
}

// (a ^ b) % p   (Binary Exponentiation)
int BinExp(ll a, ll b, int mod) {
  a %= mod;
  int res = 1;
  while (b) {
    if (b & 1) res = (res * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return res;
}
// (a * b) % p   (Binary Multiplication)
int BinMul(ll a, ll b, int mod) {
  a %= mod;
  int res = 0;
  while (b) {
    if (b & 1) res = (res + a) % mod;
    a = (a + a) % mod;
    b >>= 1;
  }
  return res;
}

// (a ^ -1) % mod (inverse of a number)
BinExp(a, mod - 2);
// (a / b) % mod
BinMul(a, BinExp(b, mod - 2, mod), mod);
// (a ^ (b ^ c)) % mod
BinExp(a, BinExp(b, c, mod - 1), mod);
// a^(b^(c^d)) % mod
ll e1 = BinExp(c, d, mod - 1);
ll e2 = BinExp(b, e1, mod - 1);
ll ans = BinExp(a, e2, mod);


// Permutations and Combinations
struct Combinatorics {
  vector<ll> fact, inv, ifact;
  Combinatorics(int n) {
    fact.assign(n + 1, 1), inv.assign(n + 1, 1), ifact.assign(n + 1, 1);
    inv[0] = 0;
    for (int i = 2; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;
    for (int i = 2; i <= n; i++) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    for (int i = 2; i <= n; i++) ifact[i] = (ifact[i - 1] * inv[i]) % mod;
  }
  int nPr(int n, int r) { // Permutations
    if (n < r) return 0;
    return (fact[n] * ifact[n - r]) % mod;
  }
  int nCr(int n, int r) { // Combinations
    return (nPr(n, r) * ifact[r]) % mod;
  }
  int nCRr(int n, int r) { // Combinations with repetition
    return (nPr(n + r - 1, r) * ifact[r]) % mod;
  }
} comb(N);

// Pascal's Triangle -> 0 based
// 0)	           1	   
// 1)	         1   1	   
// 2)	       1   2   1	   
// 3)	     1   3   3   1	   
// 4)	   1   4   6   4   1	  
// 5)  1   5   10  10  5   1  
int PascalsTriangle(int r, int c) {
  return comb.nCr(r, c);
}
// 0)	           1	   
// 1)	         1   1	   
// 2)	       1   2   [1]	   
// 3)	     1   3   [3]   1	   
// 4)	   1   4   [6]   4   1	  
// 5)  1   5   10  (10)  5   1  
// sum of (0Cr, 1Cr, 2Cr, 3Cr, 4Cr) -> 5C(r + 1)
int HockeyStickIdentity(int n, int r) {
  return comb.nCr(n + 1, r + 1);
}

// phi of single integer
int n = 10;
ll num = n;
ll phi_of_n = n;
for (ll i = 2; i * i <= num; i++) {
  if (num % i == 0) {
    while (num % i == 0) num /= i;
    phi_of_n -= phi_of_n / i;
  }
}
if (num > 1) phi_of_n -= phi_of_n / num;

// phi upto N
vector<int> phi(N);
// initial 0 to N
iota(phi.begin(), phi.end(), 0);
for (int i = 2; i < N; i++) {
  if (phi[i] == i) {
    for (int j = i; j < N; j += i) {
      phi[j] -= phi[j] / i;
    }
  }
}

// gcd sum -> ∑ gcd(i, n) for 1 <= i <= n; (n <= 1e9)
// gcd(1, n) + gcd(2, n) + .. + gcd(n, n)
ll sum = 0;
for (int i = 1; 1LL * i * i <= n; i++) {
  if (n % i == 0) {
    sum += i * phi(n / i);
    if (n / i != i) sum += (n / i) * phi(n / (n / i));
  }
}
// all pair gcd sum from 1 to N (N <= 4e6)
// ∑ i to n - 1, ∑ j + 1 to n [gcd(i, j)]
for (int i = 1; i < N; i++) {
  for (int j = i; j < N; j += i) sum[j] += i * phi[j / i];
}
for (int i = 1; i < N; i++) sum[i] += sum[i - 1] - i;


// lcm sum -> ∑ lcm(i, n) for 1 <= i <= n; (n <= 1e6)
// lcm(1, n) + lcm(2, n) + .. + lcm(n, n)
phi[1] = 2; // phi[1] should be 2 for this algorithm
for (int i = 1; i < N; i++) {
  for (int j = i; j < N; j += i) lcm_sum[j] += 1LL * j * phi[i] * i / 2;
}
// all pair lcm sum from 1 to N (N <= 1e6)
// ∑ i to n - 1, ∑ j + 1 to n [lcm(i, j)]
phi[1] = 2; // phi[1] should be 2 for this algorithm
for (int i = 1; i < N; i++) {
  for (int j = i; j < N; j += i) lcm_sum[j] += (ll) j * (1LL * i * phi[i] / 2);
}
for (int i = 1; i < N; i++) lcm_sum[i] += lcm_sum[i - 1] - i;