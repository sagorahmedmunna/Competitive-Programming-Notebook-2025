using ll = long long;
const int D = 60;
struct XorBasis {
  // number of subsequences of xor-sum X, for ith prefix -> 2 ^ (i - sz);
  ll basis[D] = {};
  int sz = 0, n = 0;
  void insert(ll x) {
    for (int i = D - 1; i >= 0; i--) {
      if (!((x >> i) & 1)) continue;
      if (!basis[i]) {
        basis[i] = x;
        sz++;
        break;
      }
      x ^= basis[i];
    } n++;
  }
  bool canRepresent(ll x) {
    for (int i = D - 1; i >= 0; i--) {
      if ((x >> i) & 1) x ^= basis[i];
    }
    return x == 0;
  }
  ll maxXor(ll x = 0) {
    for (int i = D - 1; i >= 0; i--) {
      if ((x ^ basis[i]) > x) x ^= basis[i];
    }
    return x;
  }
  ll minXor() { // except xor 0
    for (int i = 0; i < D; i++) {
      if (basis[i]) return basis[i];
    }
    return 0;
  }
  ll maxXorWith(ll x) {
    return maxXor(x);
  }
  ll minXorWith(ll x) {
    for (int i = D - 1; i >= 0; i--) {
      if ((x ^ basis[i]) < x) x ^= basis[i];
    }
    return x;
  }
  ll countDistinctXors() {
    return 1LL << sz;
  }
  ll kthXor(ll k) { // returns k + 1 th xor, 1st zor is 0
    ll res = 0;
    ll tot = countDistinctXors();
    if (tot < k) return -1;
    for (int i = D - 1; i >= 0; i--) {
      if (basis[i]) {
        ll low = tot / 2;
        if ((low < k && (res & 1 << i) == 0) ||
          (low >= k && (res & 1 << i) > 0)) res ^= basis[i];
        if (low < k) k -= low;
        tot /= 2;
      }
    }
    return res;
  }
  ll kthLargestXor(ll k) {
    return kthXor(countDistinctXors() - 1 - k);
  }
  ll kthXorAllCombinations(ll k) {
    if (n - sz > 60) return kthXor(1);
    ll totComb = 1LL << n;
    ll disComb = countDistinctXors();
    ll dupPerDis = totComb / disComb;    
    ll disIdx = (k - 1) / dupPerDis + 1;
    return kthXor(disIdx);
  }
  ll kthLargestXorAllCombinations(ll k) {
    if (n - sz > 60) return kthXor(countDistinctXors());
    ll totComb = 1LL << n;
    ll disComb = countDistinctXors();
    ll dupPerDis = totComb / disComb;    
    ll disIdx = (k - 1) / dupPerDis + 1;
    ll desIdx = disComb - disIdx + 1;
    return kthXor(desIdx);
  }
  ll countSubsetsLessThan(ll x) {
    ll lo = 0, hi = countDistinctXors();
    while (lo <= hi) {
      ll mid = (lo + hi) / 2;
      if (kthXor(mid) < x) lo = mid + 1;
      else hi = mid - 1;
    }
    return hi;
  }
  ll countSubsetsWithXor(ll x) {
    if (!canRepresent(x)) return 0;
    return 1LL << (n - sz); // if n > 60 use mod
  }
};