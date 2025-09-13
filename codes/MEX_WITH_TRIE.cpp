const int N = 2e5 * 22 + 9;
int nxt[N][2], cnt[N], intCnt[N], node = 2;
void insert(int x) {
  int u = 1;
  for(int i = 20; i >= 0; i--) {
    int bit = (x >> i) & 1;
    if(!nxt[u][bit]) nxt[u][bit] = node++;
    u = nxt[u][bit];
    cnt[u]++;
  }
  intCnt[u]++;
}
int find(int x) {
  int u = 1;
  for (int i = 20; i >= 0; i--) {
    int bit = (x >> i) & 1;
    if (!nxt[u][bit]) return 0;
    u = nxt[u][bit];
  }
  return intCnt[u];
}
void erase(int x) {
  if (find(x) == 0) return;
  int u = 1;
  for (int i = 20; i >= 0; i--) {
    int bit = (x >> i) & 1;
    int v = nxt[u][bit];
    cnt[v]--;
    u = v;
  }
  intCnt[u]--;
}
int mex() {
  int u = 1, ret = 0;
  for(int i = 20; i >= 0; i--) {
    if(u == 0 || !nxt[u][0]) return ret;
    if(cnt[nxt[u][0]] >= (1 << i)) {
      u = nxt[u][1];
      ret |= (1 << i);
    } else {
      u = nxt[u][0];
    }
  }
  return ret;
}
