const int mod = 1e9 + 7;
int distinctSubseq(string &a) {
  vector<int> last(26); // for array, use map
  int res = 1;
  for(auto& ai : a) {
    int curr = (2LL * res - last[ai - 'a']) % mod;
    if (curr < 0) curr += mod;
    last[ai - 'a'] = res;
    res = curr;
  }
  return (res - 1 + mod) % mod; // without empty set
}