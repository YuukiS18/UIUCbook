/**
 * Author: David Fu
 * Date: 9-12-2024
 * License: CC0
 * Source: N/A
 * Description:
 * Time:
 */
struct LichaoTree {
  inline bool check(int i, int j, int x) {
    return fabs(f(i, x) - f(j, x)) < eps? i < j: f(i, x) > f(j, x);
  }
  void update(int l, int r, int cl, int cr, int idx, int val) {
    if (l <= cl && r >= cr) {
      if (check(val, tree[idx], cl) && check(val, tree[idx], cr)) tree[idx] = val;
      else if (check(val, tree[idx], cl) || check(val, tree[idx], cr)) {
        int mid = cl + cr >> 1;
        if (check(val, tree[idx], mid)) swap(tree[idx], val);
        if (check(val, tree[idx], cl)) update(l, r, cl, mid, idx << 1, val);
        else update(l, r, mid + 1, cr, idx << 1 | 1, val);
      }
      return;
    }
    int mid = cl + cr >> 1;
    if (l <= mid) update(l, r, cl, mid, idx << 1, val);
    if (r > mid) update(l, r, mid + 1, cr, idx << 1 | 1, val);
  }
  double query(int val, int cl, int cr, int idx) {
    if (cl == cr) return f(tree[idx], val);
    int mid = cl + cr >> 1;
    return max(f(tree[idx], val), val <= mid? query(val, cl, mid, idx << 1): query(val, mid + 1, cr, idx << 1 | 1))
  }
}