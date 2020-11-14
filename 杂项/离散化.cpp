#include <bits/stdc++.h>

using namespace std;

#define PII pair <int, int>
#define fr first
#define sc second
#define mp make_pair
#define N 100050

// Input
int val[N], n;

// Output
int Cnt, sg[N];
PII li[N];

void Solve() {
	for (int i=1;i<=n;i++)
		li[i]=mp(val[i],i);
	sort(li+1,li+n+1);

	li[0].fr=-1;
	for (int i=1;i<=n;i++)
		sg[Cnt+=li[i].fr!=li[i-1].fr]=li[i].fr,
		val[li[i].sc]=Cnt;
	return;
}