const double PI = acos((double)-1.0);
using ll = long long;
struct PT {
  ll x, y;
  bool operator < (const PT &p) const {
    return x == p.x ? y < p.y : x < p.x;
  }
};
ll area(PT a, PT b, PT c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
vector<PT> ConvexHull(vector<PT> p) {
  int n = p.size(), m = 0;
  if (n < 3) return p;
  vector<PT> hull(n + n);
  sort(p.begin(), p.end());
  for (int i = 0; i < n; ++i) {
    while (m > 1 and area(hull[m - 2], hull[m - 1], p[i]) <= 0) --m;
    hull[m++] = p[i];
  }
  for (int i = n - 2, j = m + 1; i >= 0; --i) {
    while (m >= j and area(hull[m - 2], hull[m - 1], p[i]) <= 0) --m;
    hull[m++] = p[i];
  }
  hull.resize(m - 1);
  return hull;
}