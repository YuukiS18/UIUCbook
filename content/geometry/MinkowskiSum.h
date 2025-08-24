/**
 * Author: David Fu
 * Date: 9-12-2024
 * License: CC0
 * Source: N/A
 * Description:
 * Time: O(n + m)
 */
void Minkowski() {
    // Suppose ca, cb are convex hulls
    vector<point> v1, v2;
    for (int i = 0; i < ca.size(); i++) v1.pb(ca[(i + 1) % ca.size()] - ca[i]);
    for (int i = 0; i < cb.size(); i++) v2.pb(cb[(i + 1) % cb.size()] - cb[i]);
    c[cnt++] = ca[0] + cb[0];
    int i = 0, j = 0;
    while (i < v1.size() || j < v2.size()) {
        if (j >= v2.size() || (i < v1.size() && cross(v1[i], v2[j]) >= 0))
            c[cnt] = c[cnt - 1] + v1[i], cnt++, i++;
        else c[cnt] = c[cnt - 1] + v2[j], cnt++, j++;
    }
    // Do convex hull on c again
}