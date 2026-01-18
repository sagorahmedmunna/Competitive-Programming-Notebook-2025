freopen("input.in", "r", stdin);
freopen("output.out", "w", stdout);
ios_base::sync_with_stdio(0), cin.tie(0);
// pragma
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")// use avx for older judges
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("-ffloat-store")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,abm,mmx")
// random number generator
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int num = rng() % limit;
int64_t rnd(int64_t l, int64_t r) { // can handle negative range also
  if (l > r) swap(l, r);
  return l + (rng() % (r - l + 1));
}
// ignore white space
cin.ignore(); or cin >> ws;
// STL merge function: merge two vectors or sets
vector<int> a = {1, 2, 7}, b = {4, 2, 3};
sort(a.begin(), a.end());
sort(b.begin(), b.end());
vector<int> c(a.size() + b.size());
merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());

set<int> a = {3, 2, 1}, b = {4, 5, 1};
set<int> c;
merge(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin()));
// tuple
tuple<int, int, int> tup = {1, 2, 3};
int first = get<0>(tup);
// custom compare function
struct item {
	int a, b;
};
bool cmp(item& a, item& b) {
	if(a.a != b.a) return a.a < b.a;
	return a.b > b.b;
}
bool custom(pair<int, int>& a, pair<int, int>& b) {
	if(a.first != b.first) return a.first > b.first;
	return a.second < b.second;
}
// custom compare in set
struct cmp{
	bool operator() (const pair<int, int>& a, const pair<int, int>& b) const {
		if (a.first != b.first) return a.first > b.first;
		return a.second < b.second;
	}
};
set<pair<int, int>, cmp> a;
// greater functions
priority_queue<int, vector<int>, greater<int>>
set<int, greater<int>>
map<int, int, greater<int>>
// fill with elements
fill(v.begin(), v.end(), -1);
// fill for array
fill(&dp[0][0][0], &dp[0][0][0] + N * M * N, INF);
// string to number
stoi(num);
// number to string
to_string(num);
// Binary to decimal
int n = stoi(binary, 0, 2);
// decimal to binary
string binary = bitset<64>(n).to_string();
binary.erase(0, binary.find_first_not_of('0'));
// count digit
int d = log10(num) + 1;
// set ith bit
n | (1 << i)
// unset ith bit
n & ~(1 << i)
// toggle or inverse ith bit
n ^ (1 << i)
__builtin_popcountll(x)
__builtin_clzll(x)
__builtin_ctzll(x)