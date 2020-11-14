long long ans = n * k;
for (long long l = 1, r; l <= n;
     l = r + 1) {  //此处l意同i,r意同j,下个计算区间的l应为上个区间的r+1
  if (k / l != 0)
    r = min(k / (k / l), n);
  else
    r = n;  // l大于k时
  ans -= (k / l) * (r - l + 1) * (l + r) /
         2;  //这个区间内k/i均相等,对i求和是等差数列求和
}