const double PI = acos((double)-1.0);
using ld = long double;
using ll = long long;
struct point { ld x, y; };
void manhattanToChebychev(int& x, int& y) {
  int X = x + y, Y = x - y;
  x = X, y = Y;
}
void chebyshevToManhattan(int& x, int& y) {
  int X = (x + y) / 2, Y = (x - y) / 2;
  x = X, y = Y;
}
ll manhattanDistance(point& p1, point& p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
/*
  Calculates the minimum time to move between two points
  when diagonal movement is allowed.
  This uses Chebyshev distance.
*/
ll chebyshevDistance(point& p1, point& p2) {
  return max(abs(p1.x - p2.x), abs(p1.y - p2.y));
}
// determines the relative position (cross product) of a point (p3) 
// with respect to the line passing through (p1) and (p2)
// if (d > 0): point (p3) is to the left of the line
// if (d < 0): point (p3) is to the right of the line
// if (d == 0): point (p3) lies exactly on the line.
ll determinant(point p1, point p2, point p3) {
  ll d = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
  return d;
}
bool arePointsOnSameSide(point p1, point p2, point p3, point p4) {
  ll d1 = determinant(p1, p2, p3);
  ll d2 = determinant(p1, p2, p4);
  return (d1 * d2) > 0;
}
bool doLinesIntersect(point p1, point p2, point p3, point p4) {
  ll d1 = determinant(p3, p4, p1);
  ll d2 = determinant(p3, p4, p2);
  ll d3 = determinant(p1, p2, p3);
  ll d4 = determinant(p1, p2, p4);
  return (d1 * d2 < 0) && (d3 * d4 < 0);
}
// distance of two points
ld distance(point& p1, point& p2) {
  return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
// a point inside cricle
// x1, y1 = point of circle, r = radius of circle
// x2, y2 = target point
bool isInside(int x1, int y1, int x2, int y2, int r) {
  return ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)) <= r * r;
}
ld toDegrees(ld radians) {
  return radians * (180.0 / PI);
}
// circle with radius r
struct Circle {
  ld r;
  Circle(ld _r) { r = _r; }
  ld Diameter() { return 2 * r; }
  ld Circumference() { return 2 * PI * r; }
  ld Area() { return PI * r * r; }
  // if theta in radians, make it to degrees
  // all the calculations are in degree
  ld Sector_Area(ld theta) { return (theta / 360.0) * Area(); }
  ld Arc_Length(ld theta) { return (theta / 360.0) * Circumference(); }
  ld Chord_Length(ld theta) { return 2 * r * sin((theta * PI) / 360.0); }
  ld Segment_Area(ld theta) { return Sector_Area(theta) - (0.5 * r * r * sin((theta * PI) / 180.0)); }
  ld Circumscribed_Square_Area() { return 4 * r * r; }
  ld Inscribed_Square_Area() { return 2 * r * r; }
  ld Sphere_Surface_Area() { return 4 * PI * r * r; }
  ld Sphere_Volume() { return (4.0 / 3.0) * PI * r * r * r; }
  ld Cylinder_Surface_Area(ld h) { return 2 * PI * r * (r + h); }
  ld Cylinder_Volume(ld h) { return PI * r * r * h; }
  ld Cone_Surface_Area(ld l) { return PI * r * (r + l); }
  ld Cone_Volume(ld h) { return (1.0 / 3.0) * PI * r * r * h; }
  ld Annulus_Area(ld R) { return PI * (r * r - R * R); }
};
// triangle with three sides: a, b, c
struct Triangle {
  ld a, b, c, s;
  Triangle(point x, point y, point z) {
    a = distance(x, y);
    b = distance(y, z);
    c = distance(z, x);
    s = (a + b + c) / 2;
  }
  Triangle(ld _a, ld _b, ld _c) {
    a = _a, b = _b, c = _c;
    s = (a + b + c) / 2;
  }
  ld Area() { return sqrt(s * (s - a) * (s - b) * (s - c)); }
  ld Perimeter() { return a + b + c; }
  ld Angle_A_Radians() { return acos((b * b + c * c - a * a) / (2 * b * c)); }
  ld Angle_B_Radians() { return acos((a * a + c * c - b * b) / (2 * a * c)); }
  ld Angle_C_Radians() { return acos((a * a + b * b - c * c) / (2 * a * b)); }
  ld Angle_A_Degrees() { return toDegrees(Angle_A_Radians()); }
  ld Angle_B_Degrees() { return toDegrees(Angle_B_Radians()); }
  ld Angle_C_Degrees() { return toDegrees(Angle_C_Radians()); }
  ld Inradius() { return sqrt((s - a) * (s - b) * (s - c) / s); }
  ld Circumradius() { return (a * b * c) / (4 * Area()); }
  ld Exradius_A() { return sqrt((s - a) * (s - b) * (s - c) / (s - a)); }
  ld Exradius_B() { return sqrt((s - a) * (s - b) * (s - c) / (s - b)); }
  ld Exradius_C() { return sqrt((s - a) * (s - b) * (s - c) / (s - c)); }
  ld Altitude_A() { return 2 * Area() / a; }
  ld Altitude_B() { return 2 * Area() / b; }
  ld Altitude_C() { return 2 * Area() / c; }
  ld Median_A() { return sqrt((2 * b * b + 2 * c * c - a * a) / 4); }
  ld Median_B() { return sqrt((2 * a * a + 2 * c * c - b * b) / 4); }
  ld Median_C() { return sqrt((2 * a * a + 2 * b * b - c * c) / 4); }
};
// n sided polygon (n-gon) with side length a
struct Polygon {
  int n;
  ld a;
  Polygon(int _n, ld _a) { n = _n, a = _a; }
  ld Perimeter() { return n * a; }
  ld Exterior_Angle_Degrees() { return 360.0 / n; }
  ld Exterior_Angle_Radians() { return (2 * PI) / n; }
  ld Interior_Angle_Degrees() { return (n - 2) * 180.0 / n; }
  ld Interior_Angle_Radians() { return PI - (2 * PI / n); }
  ld Circumradius() { return a / (2 * sin(PI / n)); }
  ld Inradius() { return a / (2 * tan(PI / n)); }
  ld Area() { return (n * a * a) / (4 * tan(PI / n)); }
  ld Central_Angle_Degrees() { return 360.0 / n; }
  ld Central_Angle_Radians() { return (2 * PI) / n; }
  ll Diagonals_count() { return n * (n - 3) / 2; }
  ld Diagonal_length() { return a / sin(PI / n); }
  ld Height() {
    if (n & 1) return 2 * Inradius();
    else return Inradius() + Circumradius();
  }
  ld Width() {
    if (n & 1) {
      return 2 * Circumradius() * sin((n - 1) * PI / (2 * n));
    } else {
      if ((n / 2) & 1) return 2 * Circumradius();
      else return 2 * Inradius();
    }
  }
};