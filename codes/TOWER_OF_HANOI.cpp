void hanoi(int n, int a, int b, int c) {
  if (n == 0) return;
  hanoi(n - 1, a, c, b);
  cout << a << " " << c << '\n';
  hanoi(n - 1, b, a, c);
}
int main() {
  int n; cin >> n;
  int k = (1LL << n) - 1;
  cout << k << '\n';
  hanoi(n, 1, 2, 3);
}
