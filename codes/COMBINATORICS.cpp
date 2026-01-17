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
int modInv(ll a) {
  return BinExp(a, mod - 2);
}
// (a / b) % mod
BinMul(a, modInv(b), mod);
// (a ^ (b ^ c)) % mod
BinExp(a, BinExp(b, c, mod - 1), mod);
// a^(b^(c^d)) % mod
ll e1 = BinExp(c, d, mod - 1);
ll e2 = BinExp(b, e1, mod - 1);
ll ans = BinExp(a, e2, mod);

// Permutations and Combinations
vector<ll> fact, inv, ifact;
void CombinatoricsPrecalculate() {
  fact.assign(N + 1, 1), inv.assign(N + 1, 1), ifact.assign(N + 1, 1);
  inv[0] = 0;
  for (int i = 2; i < N; i++) fact[i] = (fact[i - 1] * i) % mod;
  for (int i = 2; i < N; i++) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
  for (int i = 2; i < N; i++) ifact[i] = (ifact[i - 1] * inv[i]) % mod;
}
int nPr(int n, int r) { // Permutations
  if (n < r) return 0;
  return (fact[n] * ifact[n - r]) % mod;
}
int nCr(int n, int r) { // Combinations
  return (nPr(n, r) * ifact[r]) % mod;
}
int nCr_rep(int n, int r) { // Combinations with repetition
  return nCr(n + r - 1, r);
}
// Number of ways to distribute n identical items into k bins (bins can be empty)
ll stars_and_bars(int n, int k) {
  return nCr(n + k - 1, k - 1);
}
// Number of ways to distribute n identical items into k bins (each bin >= 1)
ll stars_and_bars_positive(int n, int k) {
  if (n < k) return 0;
  return nCr(n - 1, k - 1);
}
/*
- Balanced parentheses: number of valid expressions with n pairs, e.g., n=3 → 5 ways
- Binary trees: number of distinct binary trees with n nodes
- Dyck paths: paths from (0,0) to (n,n) never crossing above diagonal
- Polygon triangulations: number of ways to split a convex polygon with n+2 sides into triangles
- Stack-sorting / pattern avoiding permutations: number of permutations avoiding certain patterns
*/
int catalan(int n) {
  if (n < 0) return 0;
  return nCr(2 * n, n) * inv[n + 1] % mod;
}
ll perm_with_restrictions(int n, int r, int fixed) {
  // Example: nPr with some positions fixed
  if (r < fixed) return 0;
  return nPr(n - fixed, r - fixed);
}
// multinomial(v) = number of ways to arrange sum(v) items into groups of sizes v[0], v[1], ..., v[k-1]
ll multinomial(const vector<int>& v) {
  int sum = 0;
  for (int x : v) sum += x;
  ll res = fact[sum];
  for (int x : v) res = res * ifact[x] % mod;
  return res;
}
vector<int> groups = {2,2,1}; // AABBC
cout << multinomial(groups) << "\n"; // Output: 30
// der[i] = number of permutations of i elements with no element in its original position
ll der[N];
void precomputeDerangements() {
  der[0] = 1, der[1] = 0;
  for(int i = 2; i < N; i++)
    der[i] = ((i - 1) * (der[i - 1] + der[i - 2]) % mod) % mod;
}
// Returns nCr % p for large n, r and small p (p <= 10^5)
ll lucas(ll n, ll r, int p) {
  if (r == 0) return 1;
  return (lucas(n / p, r / p, p) * nCr(n % p, r % p)) % p; // Note: nCr here must use p as MOD
}
// Stirling numbers of the second kind: S(n,k) = number of ways to partition n elements into k non-empty subsets
ll stirling2(int n, int k) { // O(klogn)
  ll ans = 0;
  for(int i = 0; i <= k; i++) {
    ll term = (ll)nCr(k, i) * BinExp(k - i, n, mod) % mod;
    if(i % 2) term = mod - term;
    ans = (ans + term) % mod;
  }
  ans = ans * ifact[k] % mod;
  return ans;
}
// Burnside's lemma for necklace counting: number of distinct necklaces with n beads and k colors
ll burnside_necklace(ll n, ll k) {
  ll sum = 0;
  for (ll r = 0; r < n; r++) {
    sum += BinExp(k, __gcd(n, r), mod);
    sum %= mod;
  }
  // divide by n (modular inverse)
  return sum * BinExp(n, mod - 2, mod) % mod;
}
// Pascal's Triangle -> 0 based
// 0)	           1	   
// 1)	         1   1	   
// 2)	       1   2   1	   
// 3)	     1   3   3   1	   
// 4)	   1   4   6   4   1	  
// 5)  1   5   10  10  5   1  
int PascalsTriangle(int r, int c) {
  return nCr(r, c);
}
// 0)	           1	   
// 1)	         1   1	   
// 2)	       1   2   [1]	   
// 3)	     1   3   [3]   1	   
// 4)	   1   4   [6]   4   1	  
// 5)  1   5   10  (10)  5   1  
// sum of (0Cr, 1Cr, 2Cr, 3Cr, 4Cr) -> 5C(r + 1)
int HockeyStickIdentity(int n, int r) {
  return nCr(n + 1, r + 1);
}
// Vandermonde's identity: sum_{i=0}^{r} C(m, i) * C(n, r-i) = C(m+n, r)
// Counts ways to pick r items from two sets by summing over all splits.
int vandermondeIdentity(int n, int k) {
  return nCr(n + k, k);
}