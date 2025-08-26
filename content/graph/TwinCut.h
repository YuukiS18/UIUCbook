/**
 * Author: Dilhan Salgado (based on description by defnotmee)
 * Date: 2025
 * Source: typing
 * Description: Twin-Cut Tree.
 * Be careful with the root.
 */

 using vvi = vector<vi>;
 struct TwinCut { /// start-hash
   vvi _adj;
   int n;
   vvi adj;
   vi par, art, ord, pari, topo, lo;
   int dfs(vvi &adj, int u) {
     lo[u] = ord[u] = sz(topo);
     topo.push_back(u);
     for (auto v : adj[u]) {
       if (ord[v] == -1) {
         pari[v] = u;
         lo[u] = min(lo[u], dfs(adj, v));
       } else if (v != pari[u]) {
         lo[u] = min(lo[u], ord[v]);
       }
     }
     return lo[u];
   }
   TwinCut(vvi adj_o) : _adj(adj_o), n(sz(_adj)), adj(2 * n), par(2 * n), art(n), ord(n, -1), pari(n), lo(n) {
     dfs(adj_o, 0);
     rep(i, 0, n) {
       int u = topo[i];
       par[2 * u + 1] = 2 * u;
       if (i) {
         int p = pari[u];
         if (lo[u] >= ord[p]) {
           par[2 * u] = 2 * p + 1;
           art[p] = 1;
         } else {
           par[2 * u] = 2 * p;
         }
       }
     }
     art[0] = count(all(pari), 0) > 2;
     rep(i, 1, 2 * n) {
       adj[par[i]].push_back(i);
       adj[i].push_back(par[i]);
     }
   }
 }; /// end-hash
 
 void trav(vvi adj) { /// start-hash
   TwinCut tree(adj);
   vi vis(2 * sz(adj));
   rep(i, 1, sz(adj)) {
     if (vis[2 * i] == 0) continue;
     if (sz(adj[i]) == 1) continue;
     vi st = {2 * i};
     vis[2 * i] = i;
     while (!st.empty()) {
       int u = st.back(); st.pop_back();
       if (u & 1) continue;
       for (auto v : tree.adj[u]) {
         if (vis[v] == i) continue;
         if (tree.ord[v / 2] < tree.lo[u / 2]) continue;
         vis[v] = i;
         st.push_back(v);
       }
     }
   }
 } /// end-hash