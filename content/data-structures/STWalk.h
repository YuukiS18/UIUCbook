/**
 * Author: Dilhan Salgado
 * Date: 2025
 * Source: folklore
 * Description: Assumes p(unit) = True.
 * If p is monotone returns the max r such that p(f(s[l], s[l + 1], ..., s[r - 1])) = True 
 **/

 template <class F>
 int search(int node, F& p, T pref) {
   if (node >= n) return node - n;
   T nex = f(pref, s[2 * node]);
   if (p(nex)) return search(2 * node + 1, p, nex);
   return search(2 * node, p, pref);
 }
 template <class F>
 int walk(int b, int e, F& p) {
   int ee = e;
   vector<int> l, r;
       for (b += n, e += n; b < e; b /= 2, e /= 2) {
           if (b % 2) l.pb(b++);
           if (e % 2) r.pb(--e);
       }
   reverse(all(r));
   l.insert(l.end(), all(r));
   T curr = unit;
   for (auto i : l) {
     T nex = f(curr, s[i]);
     if (!p(nex)) return search(i, p, curr);
   }
   return ee;
 }