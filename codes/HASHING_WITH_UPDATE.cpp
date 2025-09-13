const int MAX = int(1e6) + 9;
vector<long long> MOD = {1909999999, 1999990999};
vector<array<long long, 2>> pw(MAX), ipw(MAX);
array<long long, 2> bs = {137, 277};
int BinExp(long long a, long long b, int mod) {
  a %= mod;
  int res = 1;
  while (b) {
    if (b & 1) res = (res * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return res;
}
void Preprocess() {
  pw[0][0] = pw[0][1] = 1;
  for (int i = 1; i < MAX; i++) {
    pw[i][0] = (pw[i - 1][0] * bs[0]) % MOD[0];
    pw[i][1] = (pw[i - 1][1] * bs[1]) % MOD[1];
  }
  ipw[0][0] = ipw[0][1] = 1;
  long long ip1 = BinExp(bs[0], MOD[0] - 2, MOD[0]);
  long long ip2 = BinExp(bs[1], MOD[1] - 2, MOD[1]);
  for (int i = 1; i < MAX; i++) {
    ipw[i][0] = (ipw[i - 1][0] * ip1) % MOD[0];
    ipw[i][1] = (ipw[i - 1][1] * ip2) % MOD[1];
  }
}
struct Hashing {
  int n;
  vector<array<long long, 2>> hs;
  Hashing(string& s) {
    if (pw[2][0] == 0) Preprocess();
    n = s.size();
    hs.resize(n + 1);
    for (int i = 0; i < n; i++) {
      hs[i + 1][0] = (hs[i][0] + (pw[i][0] * s[i]) % MOD[0]) % MOD[0];
      hs[i + 1][1] = (hs[i][1] + (pw[i][1] * s[i]) % MOD[1]) % MOD[1];
    }
  }
  array<long long, 2> get_hash(int l, int r) { // 0 based query
    l++, r++; // 1 based hashing
    long long res1 = ((hs[r][0] - hs[l - 1][0]) + MOD[0]) % MOD[0];
    long long res2 = ((hs[r][1] - hs[l - 1][1]) + MOD[1]) % MOD[1];
    res1 = (res1 * ipw[l - 1][0]) % MOD[0];
    res2 = (res2 * ipw[l - 1][1]) % MOD[1];
    //return res1 << 31 | res2;
    return {res1, res2};
  }
};
auto Hash_Merge(array<long long, 2> left, array<long long, 2> right, int left_sz) {
  for (int i = 0; i < 2; i++) {
    (right[i] *= pw[left_sz][i]) %= MOD[i];
    (left[i] += right[i]) %= MOD[i];
  }
  return left;
};
// # with update, find palindrome O(nlogn)
const int N = 1e6 + 9;
int power(long long n, long long k, const int mod) {
  int ans = 1 % mod;
  n %= mod;
  if (n < 0) n += mod;
  while (k) {
    if (k & 1) ans = (long long) ans * n % mod;
    n = (long long) n * n % mod;
    k >>= 1;
  }
  return ans;
}
using T = array<int, 2>;
const T MOD = {127657753, 987654319};
const T p = {137, 277};
T operator + (T a, int x) {return {(a[0] + x) % MOD[0], (a[1] + x) % MOD[1]};}
T operator - (T a, int x) {return {(a[0] - x + MOD[0]) % MOD[0], (a[1] - x + MOD[1]) % MOD[1]};}
T operator * (T a, int x) {return {(int)((long long) a[0] * x % MOD[0]), (int)((long long) a[1] * x % MOD[1])};}
T operator + (T a, T x) {return {(a[0] + x[0]) % MOD[0], (a[1] + x[1]) % MOD[1]};}
T operator - (T a, T x) {return {(a[0] - x[0] + MOD[0]) % MOD[0], (a[1] - x[1] + MOD[1]) % MOD[1]};}
T operator * (T a, T x) {return {(int)((long long) a[0] * x[0] % MOD[0]), (int)((long long) a[1] * x[1] % MOD[1])};}
ostream& operator << (ostream& os, T hash) {return os << "(" << hash[0] << ", " << hash[1] << ")";}
T pw[N], ipw[N];
void prec() {
  pw[0] =  {1, 1};
  for (int i = 1; i < N; i++) {
    pw[i] = pw[i - 1] * p;
  }
  ipw[0] =  {1, 1};
  T ip = {power(p[0], MOD[0] - 2, MOD[0]), power(p[1], MOD[1] - 2, MOD[1])};
  for (int i = 1; i < N; i++) {
    ipw[i] = ipw[i - 1] * ip;
  }
}
struct Hashing {
  int n;
  string s; // 1 - indexed
  vector<array<T, 2>> t; // (normal, rev) hash
  array<T, 2> merge(array<T, 2> l, array<T, 2> r) {
    l[0] = l[0] + r[0];
    l[1] = l[1] + r[1];
    return l;
  }
  void build(int node, int b, int e) {
    if (b == e) {
      t[node][0] = pw[b] * s[b];
      t[node][1] = pw[n - b + 1] * s[b];
      return;
    }
    int mid = (b + e) >> 1, l = node << 1, r = l | 1;
    build(l, b, mid);
    build(r, mid + 1, e);
    t[node] = merge(t[l], t[r]);
  }
  void upd(int node, int b, int e, int i, char x) {
    if (b > i || e < i) return;
    if (b == e && b == i) {
      t[node][0] = pw[b] * x;
      t[node][1] = pw[n - b + 1] * x;
      return;
    }
    int mid = (b + e) >> 1, l = node << 1, r = l | 1;
    upd(l, b, mid, i, x);
    upd(r, mid + 1, e, i, x);
    t[node] = merge(t[l], t[r]);
  }
  array<T, 2> query(int node, int b, int e, int i, int j) {
    if (b > j || e < i) return {T({0, 0}), T({0, 0})};
    if (b >= i && e <= j) return t[node];
    int mid = (b + e) >> 1, l = node << 1, r = l | 1;
    return merge(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
  }
  Hashing() {}
  Hashing(string _s) {
    n = _s.size();
    s = "." + _s;
    t.resize(4 * n + 1);
    build(1, 1, n);
  }
  void upd(int i, char c) {
    upd(1, 1, n, i, c);
    s[i] = c;
  }
  T get_hash(int l, int r) { // 1 - indexed
    return query(1, 1, n, l, r)[0] * ipw[l - 1];
  }
  T rev_hash(int l, int r) { // 1 - indexed
    return query(1, 1, n, l, r)[1] * ipw[n - r];
  }
  T get_hash() return get_hash(1, n);
  bool is_palindrome(int l, int r) return get_hash(l, r) == rev_hash(l, r);
}; 