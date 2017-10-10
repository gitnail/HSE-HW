#include <bits/stdc++.h>

using namespace std;

const double pi = acos(-1);
const int N = 1 << 20;


int revv(int x, int bits) {
    int ret = 0;
    for (int i = 0; i < bits; ++i) {
        ret <<= 1;
        ret |= x & 1;
        x >>= 1;
    }
    return ret;
}

void fft(vector<double>& a, vector<double>& b, int n, bool rev) {
    int bits = 0;
    while (1 << bits < n) ++bits;
    for (int i = 0; i < n; i++) {
        int j = revv(i, bits);
        if (i < j) {
            swap(a[i], a[j]);
            swap(b[i], b[j]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        int half = len >> 1;
        double wmx = cos(2.0 * pi / len);
        double wmy = sin(2.0 * pi / len);
        if (rev)
            wmy = -wmy;
        for (int i = 0; i < n; i += len) {
            double wx = 1;
            double wy = 0;
            for (int j = 0; j < half; j++) {
                double cx = a[i + j];
                double cy = b[i + j];
                double dx = a[i + j + half];
                double dy = b[i + j + half];
                double ex = dx * wx - dy * wy;
                double ey = dx * wy + dy * wx;
                a[i + j] = cx + ex;
                b[i + j] = cy + ey;
                a[i + j + half] = cx - ex;
                b[i + j + half] = cy - ey;
                double wnx = wx * wmx - wy * wmy;
                double wny = wx * wmy + wy * wmx;
                wx = wnx;
                wy = wny;
            }
        }
    }
    if (rev) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
            b[i] /= n;
        }
    }
}





