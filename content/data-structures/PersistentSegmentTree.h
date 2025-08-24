/**
 * Author: David Fu
 * Date: 9-12-2024
 * License: CC0
 * Source: N/A
 * Description:
 * Time:
 */
struct PersistentSegTree {
    int build(int l, int r) {
        int rt = ++ts; 
        if (l == r) return rt;
        int mid = l + r >> 1;
        tree[rt].ls = build(l, mid), tree[rt].rs = build(mid + 1, r);
        return rt;
    }
    int update(int pos, int cl, int cr, int idx) {
        int rt = ++ts;
        tree[rt].ls = tree[idx].ls, tree[rt].rs = tree[idx].rs, tree[rt].sum = tree[idx].sum + 1;
        if (cl == cr) return rt;
        int mid = cl + cr >> 1;
        if (pos <= mid) tree[rt].ls = update(pos, cl, mid, tree[idx].ls);
        else tree[rt].rs = update(pos, mid + 1, cr, tree[idx].rs);
        return rt; 
    }
    int query(int l, int r, int cl, int cr, int pos) {
        int mid = cl + cr >> 1, sum = tree[tree[r].ls].sum - tree[tree[l].ls].sum;
        if (cl == cr) return cl;
        if (pos <= sum) return query(tree[l].ls, tree[r].ls, cl, mid, pos);
        else return query(tree[l].rs, tree[r].rs, mid + 1, cr, pos - sum);
    }
}