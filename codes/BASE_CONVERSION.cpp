// 2 <= b <= 62
const string D = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
string decimalToBase(int64_t n, int b) {
  if (n == 0) return "0";
  string result;
  bool neg = n < 0;
  if (neg) n = -n;
  while (n > 0) {
    result.push_back(D[n % b]);
    n /= b;
  }
  if (neg) result.push_back('-');
  reverse(result.begin(), result.end());
  return result;
}
int64_t baseToDecimal(const string &s, int b) {
  int64_t result = 0;
  int start = 0, neg = 0;
  if (s[0] == '-') neg = start = 1;
  for (int i = start; i < (int)s.size(); i++) {
    char c = s[i];
    int val;
    if ('0' <= c && c <= '9') val = c - '0';
    else if ('A' <= c && c <= 'Z') val = c - 'A' + 10;
    else if ('a' <= c && c <= 'z') val = c - 'a' + 36;
    result = result * b + val;
  }
  return neg ? -result : result;
}