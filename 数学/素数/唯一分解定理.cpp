const int M = 1000000;
bool isprime[M+5];
int prime[M+5], cnt;

void solve() {
	for(int i = 1;i <= M; i++) isprime[i] = 1;
	for(int i = 3;i <= M; i++) if(!(i%2)) isprime[i] = 0;
	for(int i = 2;i <= M; i++) {
		if(isprime[i]) {
			for(int j = i*2; j<= M; j += i)
				isprime[j] = 0;
		}
	}
	isprime[1] = 0;
	for(int i = 2;i <= M; i++) {
		if(isprime[i]) prime[++cnt] = i;
	}
}

long long getfac(long long x) {
	long long ans=1;
	for(int i = 1;i <= cnt && prime[i] <= x; i++) {
		long long sum = 0;//当前质因数的幂指数
		while(x%prime[i] == 0) { //当是这个数的因子时
			sum++;
			x /= prime[i];
		}
		ans *= (sum+1);//应用定理的结论
	}
	if(x>1) ans *= 2;//当搜索不到的时候，如果这个数最后大于一，那么这个最后结果肯定是素数，并且指数是1
	return ans;
}