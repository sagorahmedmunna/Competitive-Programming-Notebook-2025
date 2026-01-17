char find_digit(int64_t k) {
  int64_t len = 1, count = 9, start = 1;
  while (k > len * count) {
    k -= len * count;
    len++, count *= 10, start *= 10;
  }
  int64_t num = start + (k - 1) / len;
  string s = to_string(num);
  return s[(k - 1) % len];
}
int main() {
  int q; cin >> q;
  while (q--) {
    int64_t k;
    cin >> k;
    cout << find_digit(k) << '\n';
  }
}
