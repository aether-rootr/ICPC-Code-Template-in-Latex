1 → n
0 → ans
for i = 1 to k
    n * n[i] → n
for i = 1 to k
    n / n[i] → m
    inv(m, n[i]) → b               // b * m mod n[i] = 1
    (ans + m * b) mod n → ans
return ans