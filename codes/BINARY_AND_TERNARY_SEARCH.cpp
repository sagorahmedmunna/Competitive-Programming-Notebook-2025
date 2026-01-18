//Binary Search (integer)
int lo = 0, hi = n - 1;
while (lo <= hi) {
  int mid = (lo + hi) / 2;
  if (f(mid)) hi = mid - 1;
  else lo = mid + 1;
}
// -> another version
while (lo < hi) {
  int mid = (lo + hi) / 2;
  if (f(mid)) hi = mid;
  else lo = mid + 1;
}
//Binary Search (double)
double lo = 0, hi = inf;
int itr = 50;
while (itr--) {
  double mid = (lo + hi) / 2;
  if (f(mid)) hi = mid;
  else lo = mid;
}
//Ternary Search (integer, max)
int lo = 0, hi = n - 1;
while (lo < hi) {
  // int mid1 = lo + (hi - lo) / 3;
  // int mid2 = hi - (hi - lo) / 3;
  int mid = (lo + hi) / 2;
  if (f(mid) < f(mid + 1)) lo = mid + 1;
  else  hi = mid;
}
//Ternary Search (double, max)
double lo = 0, hi = inf;
int itr = 50;
while (itr--) {
  double mid1 = lo + (hi - lo) / 3;
  double mid2 = hi - (hi - lo) / 3;
  if (f(mid1) < f(mid2)) lo = mid1;
  else  hi = mid2;
}