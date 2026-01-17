// Remove (1,2) or (2,1) coins from the two piles per move.
int main() {
  int t;
  cin >> t;
  while (t--) {
    long long a, b;
    cin >> a >> b;
    if ((a + b) % 3 == 0 && min(a, b) * 2 >= max(a, b))
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}