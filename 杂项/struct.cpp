#include <set>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
	int l, r, mid;
	node *lef, *rig;
	node (int l, int r) {
		this->l = l;
		this->r = r;
		mid = (l + r) >> 1;
		
		if (l == r)
			return;
		lef = new node(l, mid);
		rig = new node(mid + 1, r);
	}
};
struct node2 {
	int l, r, mid;
	node2 *lef, *rig;
	void build(int l, int r) {
		this->l = l;
		this->r = r;
		mid = (l + r) >> 1;
		
		if (l == r)
			return;
		(lef = new node2)->build(l, mid);
		(rig = new node2)->build(mid + 1, r);
	}
	int query(int x) {
		if (l == r)
			return l;
		if (x <= mid)
			return lef->query(x);
		else
			return rig->query(x);
	}
};
struct matrix {
	int v[4][4];
	int *operator [] (int x) { return v[x]; }
};
matrix operator * (matrix &a, matrix &b) {
	matrix ret;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				ret[i][j] += a[i][k] * b[k][j];
	return ret;
}
struct element {
	int x, y;
};
struct bignum {
	int n, a[10];
	void operator += (bignum &t) {
		n = max(n, t.n);
		for (int i = 1; i <= n; ++i) {
			a[i] += t.a[i];
			if (a[i] >= 1000) {
				a[i] -= 1000;
				a[i + 1] ++;
			}
		}
		if (a[n + 1] > 0)
			++n;
	}
};

bool cmp_element(const element &a, const element &b) {
	return a.x < b.x  ||  (a.x == b.x  &&  a.y < b.y);
}

struct cmp {
	bool operator () (element *a, element *b) {
		if (a->x != b->x)
			return a->x < b->x;
		if (a->y != b->y)
			return a->y < b->y;
		return a < b;
	}
};

set <element*, cmp> heap;

int main() {
	node *root = new node(1, 100);
	
	node2 *root2 = new node2;
	root2->build(1, 100);
	
	cout << root2->query(5) << endl;
	
	matrix a, b, c;
	a = b * c;
	
	element s[100];
	sort(s + 1, s + 100, cmp_element);
	
	bignum x, y;
	x += y;
}