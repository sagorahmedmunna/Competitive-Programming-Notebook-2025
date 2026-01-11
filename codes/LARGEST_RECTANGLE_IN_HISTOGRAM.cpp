int64_t largestRectangleInHistogram(vector<int>& a) {
  int64_t n = a.size(), mx = 0;
  stack<int> st;
  for (int i = 0; i <= n; i++) {
    int cur = (i == n ? 0 : a[i]);
    while (!st.empty() && a[st.top()] >= cur) {
      int64_t h = a[st.top()];
      st.pop();
      int left = st.empty() ? -1 : st.top();
      mx = max(mx, h * (i - left - 1));
    }
    st.push(i);
  } return mx;
}