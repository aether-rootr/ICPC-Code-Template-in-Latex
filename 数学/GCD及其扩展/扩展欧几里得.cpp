//已知a, b求解一组x，y，使它们满足贝祖等式： ax+by = gcd(a, b) =d
int ExtendGCD(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1; *y = 0; // b=0
        return a;
    }

    int r = ExtendGCD(b, a%b, x, y);
    int t = *y; // temp
    *y = *x - (a / b)*(*y); // y1 = x2 - k*y2
    *x = t; // x1 = y2
    return r;
}