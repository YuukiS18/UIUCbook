/**
 * Author: ACL
 * Source: ACL
 * Description: Finds $\sum_{i=0}^{n-1}\left\lfloor \frac{a\cdot i + b}{m}\right\rfloor$ mod $2^{64}$.
 * Status: tested on atcoder
 * Time: O(\log n)
 */
#pragma once

typedef unsigned long long ull;

ull floor_sum_unsigned(ull n, ull m, ull a, ull b) {/// start-hash
    ull ans = 0;
    while (true) {
        if (a >= m) {
            ans += n * (n - 1) / 2 * (a / m);
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }
        ull y_max = a * n + b;
        if (y_max < m) break;
        n = (ull)(y_max / m);
        b = (ull)(y_max % m);
        std::swap(m, a);
    }
    return ans;
}/// end-hash

ll floor_sum(ll n, ll m, ll a, ll b) {
    ull ans = 0;
    if (a < 0) {
        ll a2 = a % m; if(a2 < 0) a2 += m;
        ans -= 1ULL * n * (n - 1) / 2 * (((ull)a2 - a) / m);
        a = a2;
    }
    if (b < 0) {
        ll b2 = b % m; if(b2 < 0) b2 += m;
        ans -= 1ULL * n * (((ull)b2 - b) / m);
        b = b2;
    }
    return ans + floor_sum_unsigned(n, m, a, b);
}