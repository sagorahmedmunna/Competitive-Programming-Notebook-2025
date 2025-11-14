const double PI = acos((double)-1.0);
using ll = long long;
struct PT {
  ll x, y;
  bool operator < (const PT &p) const {
    return x == p.x ? y < p.y : x < p.x;
  }
};
ll area(PT a, PT b, PT c) { // twice of area
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
ll convexHullArea() {
  int n = hull.size();
  ll totalArea = 0;
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    totalArea += hull[i].x * hull[j].y - hull[j].x * hull[i].y;
  }
  return llabs(totalArea); // twice of area
  return llabs(totalArea) / 2.0;
}
ll f(int i, PT P, int n) {
  return area(hull[i], hull[(i + 1) % n], P);
}
ld minTriangleArea(PT P) {
  int n = hull.size(), l = 0, r = n - 1;
  while (r - l > 5) {
    int m1 = l + (r - l) / 3;
    int m2 = r - (r - l) / 3;
    if (f(m1, P, n) < f(m2, P, n)) r = m2 - 1;
    else l = m1 + 1;
  }
  ll ans = 1.1e17;
  for (int i = l; i <= r; i++)
    ans = min(ans, f(i, P, n));
  return ans; // twice of area
  return (ld)ans / 2.0;
}