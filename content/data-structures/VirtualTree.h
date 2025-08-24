/**
 * Author: David Fu
 * Date: 9-12-2024
 * License: CC0
 * Source: N/A
 * Description: 
 * Time: 
 */
struct VirtualTree {
    // dfs1 calculates DFS order as id & binary lifting for lca
    void build() {
        dfs1(1, 0);
        ts = top = 0, head[s[++top] = 1] = 0;
        sort(h, h + k, [&](int a, int b) { return id[a] < id[b]; });
        for (int i = 0; i < k; i++) {
            if (h[i] == 1) continue;
            int l = lca(h[i], s[top]);
            if (l != s[top]) {
                while (id[l] < id[s[top - 1]])
                    edge[++ts] = {s[top - 1], s[top], head[s[top - 1]]}, head[s[top - 1]] = ts, top--;
                if (l != s[top - 1])
                    head[l] = 0, edge[++ts] = {l, s[top], head[l]}, head[l] = ts, s[top] = l;
                else edge[++ts] = {l, s[top--], head[l]}, head[l] = ts;
            }
            head[h[i]] = 0, s[++top] = h[i];
        }
        for (int i = 1; i < top; i++)
            edge[++ts] = {s[i], s[i + 1], head[s[i]]}, head[s[i]] = ts;
    }
}