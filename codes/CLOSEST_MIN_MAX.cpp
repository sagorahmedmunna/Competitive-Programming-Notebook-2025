// closest left, right index where current element is max or min
// closest max or min element from the current element
array<vector<int>, 2> closest_min_element(vector<int> &a) {
  int n = a.size();
  vector<int> l(n), r(n);
  stack<int> st;
  st.push(-1);
  for (int i = 0; i < n; i++) {
    while (st.top() != -1 && a[st.top()] > a[i]) st.pop();
    l[i] = st.top() + 1; // closest index where current element is min
    // l[i] = st.top(); // closest min element index
    st.push(i);
  }
  while (!st.empty()) st.pop();
  st.push(n);
  for (int i = n - 1; i >= 0; i--) {
    while (st.top() != n && a[st.top()] >= a[i]) st.pop();
    r[i] = st.top() - 1; // closest index where current element is min
    // r[i] = st.top(); // closest min element index
    st.push(i);
  }
  return {l, r};
}
array<vector<int>, 2> closest_max_element(vector<int> &a) {
  int n = a.size();
  vector<int> l(n), r(n);
  stack<int> st;
  st.push(-1);
  for (int i = 0; i < n; i++) {
    while (st.top() != -1 && a[st.top()] < a[i]) st.pop();
    l[i] = st.top() + 1;
    // l[i] = st.top(); // closest max element index
    st.push(i);
  }
  while (!st.empty()) st.pop();
  st.push(n);
  for (int i = n - 1; i >= 0; i--) {
    while (st.top() != n && a[st.top()] <= a[i]) st.pop();
    r[i] = st.top() - 1;
    // r[i] = st.top(); // closest max element index
    st.push(i);
  }
  return {l, r};
}