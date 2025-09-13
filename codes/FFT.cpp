struct cplx {
  long double a, b;
  cplx(long double a = 0, long double b = 0) : a(a), b(b) {}
  const cplx operator + (const cplx &c) const { return cplx(a + c.a, b + c.b); }
  const cplx operator - (const cplx &c) const { return cplx(a - c.a, b - c.b); }
  const cplx operator * (const cplx &c) const { return cplx(a * c.a - b * c.b, a * c.b + b * c.a); }
  const cplx operator / (const long double &d) const { return cplx(a / d, b / d); }
};
const long double PI = acos(-1);
vector<int> rev;
void Preprocess(int sz) {
  if ((int)rev.size() == sz) return;
  rev.resize(sz);
  rev[0] = 0;
  int lg_n = __builtin_ctz(sz);
  for (int i = 1; i < sz; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg_n - 1));
  }
}
void fft(vector<cplx> &a, bool inv = 0) {
  int n = a.size();
  for (int i = 1; i < n - 1; ++i) {
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    long double t = 2 * PI / len * (inv ? -1 : 1);
    cplx wlen = {cosl(t), sinl(t)};
    for (int st = 0; st < n; st += len) {
      cplx w(1);
      for (int i = 0; i < len / 2; ++i) {
        cplx ev = a[st + i], od = a[st + i + len / 2] * w;
        a[st + i] = ev + od;
        a[st + i + len / 2] = ev - od;
        w = w * wlen;
      }
    }
  }
  if (inv) {
    for (cplx& z : a) z = z / n;
  }
}
vector<long long> multiply(vector<int> &a, vector<int> &b) {
  int n = a.size(), m = b.size(), sz = 1;
  while(sz < n + m - 1) sz <<= 1;
  vector<cplx> x(sz), y(sz), z(sz);
  for(int i = 0 ; i < sz; i++) {
    x[i] = i < n ? cplx(a[i], 0) : cplx(0, 0);
    y[i] = i < m ? cplx(b[i], 0) : cplx(0, 0);
  }
  Preprocess(sz);
  fft(x), fft(y);
  for(int i = 0; i < sz; i++) z[i] = x[i] * y[i];
  fft(z, 1);
  vector<long long> c(n + m - 1);
  for(int i = 0; i < n + m - 1; i++) c[i] = round(z[i].a);
  return c;
}
auto c = mutiply(a, b);