// iterative
const int N = 1e6 + 9, A = 26;
int nxt[N][A], pref_cnt[N], word_cnt[N], node = 2;
void insert(string& s, int u = 1) {
  for (auto& c : s) {
    int idx = c - 'a';
    if (!nxt[u][idx]) nxt[u][idx] = node++;
    u = nxt[u][idx];
    pref_cnt[u]++;
  } word_cnt[u]++;
}
int countPref(string& s, int u = 1) {
  for (auto& c : s) {
    int idx = c - 'a';
    if (!nxt[u][idx]) return 0;
    u = nxt[u][idx];
  } return pref_cnt[u];
}
int find(string& s, int u = 1) {
  for (auto& c : s) {
    int idx = c - 'a';
    if (!nxt[u][idx]) return 0;
    u = nxt[u][idx];
  } return word_cnt[u];
}
void erase(string& s, int u = 1) {
  if (find(s) == 0) return;
  for (auto& c : s) {
    int idx = c - 'a';
    int v = nxt[u][idx];
    pref_cnt[v][idx]--;
    u = v;
  } word_cnt[u]--;
}

// trie integer iterative (max xor, min xor)
const int N = 2e5 * 31 + 9, A = 2;
int nxt[N][A], pref_cnt[N], int_cnt[N], node = 2;
void insert(int num, int u = 1) {
  for (int bit = 30; bit >= 0; bit--) {
    int idx = (num >> bit) & 1;
    if (!nxt[u][idx]) nxt[u][idx] = node++;
    u = nxt[u][idx];
    pref_cnt[u]++;
  } int_cnt[u]++;
}
int find(int num, int u = 1) {
  for (int bit = 30; bit >= 0; bit--) {
    int idx = (num >> bit) & 1;
    if (!nxt[u][idx]) return 0;
    u = nxt[u][idx];
  } return int_cnt[u];
}
void erase(int num, int u = 1) {
  if (find(num) == 0) return;
  for(int bit = 30; bit >= 0; bit--) {
    int idx = (num >> bit) & 1;
    int v = nxt[u][idx];
    pref_cnt[v]--;
    u = v;
  } int_cnt[u]--;
}
int maxXor(int num) {
  int res = 0, u = 1;
  for (int bit = 30; bit >= 0; bit--) {
    int idx = (num >> bit) & 1;
    int flip = idx ^ 1;
    if (nxt[u][flip] && pref_cnt[nxt[u][flip]]) {
      res += (1 << bit);
      u = nxt[u][flip];
    } else {
      u = nxt[u][idx];
    }
  } return res;
}
int minXor(int num) {
  int res = 0, u = 1;
  for (int bit = 30; bit >= 0; bit--) {
    int idx = (num >> bit) & 1;
    if (nxt[u][idx] && pref_cnt[nxt[u][idx]]) {
      u = nxt[u][idx];
    } else {
      res += (1 << bit);
      u = nxt[u][idx ^ 1];
    }
  } return res;
}