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