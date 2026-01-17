vector<int> lpf(N), phi(N), mu(N), primes;
void linear_sieve() {
  phi[1] = mu[1] = 1;
  for (int i = 2; i < N; i++) {
    if (lpf[i] == 0) {
      lpf[i] = i, phi[i] = i - 1, mu[i] = -1;
      primes.push_back(i);
    }
    for (int p : primes) {
      if (p > lpf[i] || i * p >= N) break;
      lpf[i * p] = p;
      if (i % p == 0) {
        phi[i * p] = phi[i] * p;
        mu[i * p] = 0;
        break;
      } else {
        phi[i * p] = phi[i] * (p - 1);
        mu[i * p] = -mu[i];
      }
    }
  }
}