/**
 * Author: David Fu
 * Date: 9-12-2024
 * License: CC0
 * Source: N/A
 * Description:
 * Time:
 */
struct KDTree {
	const double alpha = .75;
	struct point { int a[dim];};
	struct node { 
		point p; int mini[dim], maxi[dim], size, ls, rs;
	} tree[1111111];
	stack<int> ind; int ans;
	inline void pushup(int idx) {/// start-hash
		for (int i = 0; i < dim; i++) {
			tree[idx].maxi[i] = tree[idx].mini[i] = tree[idx].p.a[i];
			if (tree[idx].ls) {
				tree[idx].maxi[i] = max(tree[idx].maxi[i], tree[tree[idx].ls].maxi[i]);
				tree[idx].mini[i] = min(tree[idx].mini[i], tree[tree[idx].ls].mini[i]);
			}
			if (tree[idx].rs) {
				tree[idx].maxi[i] = max(tree[idx].maxi[i], tree[tree[idx].rs].maxi[i]);
				tree[idx].mini[i] = min(tree[idx].mini[i], tree[tree[idx].rs].mini[i]);
			}
		}
		tree[idx].size = tree[tree[idx].ls].size + tree[tree[idx].rs].size + 1;
	}/// end-hash
	int build(int l, int r, int axis) {/// start-hash
		if (l > r) return 0;
		int mid = l + r >> 1, idx;
		nth_element(p + l, p + mid, p + r + 1, [&](point p1, point p2) {
			return p1.a[axis] < p2.a[axis];
		});
		if (ind.empty()) idx = ++ts;
		else {idx = ind.top(); ind.pop();}
		tree[idx].p = p[mid];
		tree[idx].ls = build(l, mid - 1, (axis + 1) % dim);
		tree[idx].rs = build(mid + 1, r, (axis + 1) % dim);
		pushup(idx);
		return idx;
	}/// end-hash
	void flatten(int idx, int cnt) {/// start-hash
		if (tree[idx].ls) flatten(tree[idx].ls, cnt);
		p[cnt + tree[tree[idx].ls].size] = tree[idx].p;
		ind.push(idx);
		if (tree[idx].rs) flatten(tree[idx].rs, cnt + tree[tree[idx].ls].size + 1);
	}/// end-hash
	void insert(const point& p, int& idx, int axis) {/// start-hash
		if (! idx) {
			idx = ++ts, tree[idx].p = p, pushup(idx);
			return;
		}
		if (p.a[axis] < tree[idx].p.a[axis]) insert(p, tree[idx].ls, (axis + 1) % dim);
		else insert(p, tree[idx].rs, (axis + 1) % dim);
		pushup(idx);
		if (tree[tree[idx].ls].size > tree[idx].size * alpha || tree[tree[idx].rs].size > tree[idx].size * alpha) {
			flatten(idx, 0);
			idx = build(0, tree[idx].size - 1, axis);
		}
	}/// end-hash
	inline int tree_dist(const point& p, int idx) {/// start-hash
		int ans = 0;
		for (int i = 0; i < dim; i++) 
			ans += max(0, p.a[i] - tree[idx].maxi[i]) + max(0, tree[idx].mini[i] - p.a[i]);
		return ans;
	}/// end-hash
	void query(const point& p, int idx) {/// start-hash
		ans = min(ans, dist(p, tree[idx].p));
		int lans = tree[idx].ls? tree_dist(p, tree[idx].ls): INT_MAX;
		int rans = tree[idx].rs? tree_dist(p, tree[idx].rs): INT_MAX;
		if (lans < rans) {
			if (lans < ans) query(p, tree[idx].ls);
			if (rans < ans) query(p, tree[idx].rs);
		} else {
			if (rans < ans) query(p, tree[idx].rs);
			if (lans < ans) query(p, tree[idx].ls);
		}
	}/// end-hash
	ll query(const point& p1, const point& p2, int idx) {/// start-hash
		if (p1.a[0] <= tree[idx].mini[0] && p1.a[1] <= tree[idx].mini[1] && p2.a[0] >= tree[idx].maxi[0] && p2.a[1] >= tree[idx].maxi[1])
			return tree[idx].sum;
		else if (p1.a[0] > tree[idx].maxi[0] || p1.a[1] > tree[idx].maxi[1] || p2.a[0] < tree[idx].mini[0] || p2.a[1] < tree[idx].mini[1])
			return 0;

		ll ans = (tree[idx].p.a[0] >= p1.a[0] && tree[idx].p.a[1] >= p1.a[1] && tree[idx].p.a[0] <= p2.a[0] && tree[idx].p.a[1] <= p2.a[1]) * tree[idx].p.a[2];
		if (tree[idx].ls) ans += query(p1, p2, tree[idx].ls);
		if (tree[idx].rs) ans += query(p1, p2, tree[idx].rs);

		return ans;
	}/// end-hash
}