#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T, class R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Sorting Descending (or Equal)
template <class T> using ordered_set = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> using ordered_multiset = tree<T, null_type, greater_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T, class R> using ordered_map = tree<T, R, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Fucntions
st.order_of_key(k); // count of elements smaller than k. — O(log n)
st.find_by_order(k); // Returns the iterator for the kth element (0 based index). — O(log n)
st.size() - st.order_of_key(k + 1); // count of elements greater than k. - O(log n)
st.order_of_key(r + 1) - st.order_of_key(l); // count of elements between l to r
st.erase(st.find_by_order(st.order_of_key(k))); // erase in multiset