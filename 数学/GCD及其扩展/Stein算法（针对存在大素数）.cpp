int SteinGCD(int a, int b) {
    if (a < b) { int t = a; a = b; b = t; }
    if (b == 0) return a;
    if ((a & 1) == 0 && (b & 1) == 0)
        return SteinGCD(a >> 1, b >> 1) << 1;
    else if ((a & 1) == 0 && (b & 1) != 0)
        return SteinGCD(a >> 1, b);
    else if ((a & 1) != 0 && (b & 1) == 0)
        return SteinGCD(a, b >> 1);
    else
        return SteinGCD(a - b, b);
}