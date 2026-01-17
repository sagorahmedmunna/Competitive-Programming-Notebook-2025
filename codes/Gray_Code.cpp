// Generate all 2^n n-bit strings so consecutive ones differ in exactly one bit.
int main() {
  int n; cin >> n;
  for (int i = 0; i < (1 << n); i++) {
    bitset<16> b(i ^ (i >> 1));
    for (int j = n - 1; j >= 0; j--) cout << b[j];
    cout << '\n';
  }
}