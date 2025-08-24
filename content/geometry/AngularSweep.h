/**
 * Author: David Fu
 * Date: 9-12-2024
 * License: CC0
 * Source: N/A
 * Description:
 * Time: 
 */
inline bool cmp(point p1, point p2) {
    return angle(p1) < angle(p2) || (angle(p1) == angle(p2) && dist(p1, p) < dist(p2, p));
}
int solve(int r) {
    int maxi = 0;
    vector<pdi> v;
    for (int i = 0; i < n; i++) {
        if (dist(a[i], p) > 2 * r) continue;
        double a1 = angle(a[i] - p), a2 = acos(dist(a[i], p) / (2 * r));
        v.pb({a1 + a2, -1}); v.pb({a1 - a2, 1}); v.pb({a1 + a2 + 2 * PI, -1}); v.pb({a1 - a2 + 2 * PI, 1});
    }
    sort(v.begin(), v.end(), [&](pdi p1, pdi p2) { return p1.first < p2.first || (p1.first == p2.first && p1.second > p2.second);});
    for (int i = 0, sum = 0; i < v.size(); i++) 
        sum += v[i].second, maxi = max(maxi, sum);
    return maxi;
}