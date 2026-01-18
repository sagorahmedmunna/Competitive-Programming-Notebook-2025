char find_digit(ll k) {
  ll len = 1, count = 9, start = 1;
  while (k > len * count) {
    k -= len * count;
    len++, count *= 10, start *= 10;
  }
  ll num = start + (k - 1) / len;
  string s = to_string(num);
  return s[(k - 1) % len];
}
int main() {
  int q; cin >> q;
  while (q--) {
    ll k;
    cin >> k;
    cout << find_digit(k) << '\n';
  }
}
