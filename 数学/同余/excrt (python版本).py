x = []
y = []
x.append(1)
y.append(1)
ai = []
bi = []
n = 100
m = 100


def exgcd(a, b, x, y):
    if b == 0:
        x[0] = 1
        y[0] = 0
        return a
    gcd = exgcd(b, a % b, x, y);
    tp = x[0]
    x[0] = y[0]
    y[0] = tp - a // b * y[0]
    return gcd


def excrt():
    M = bi[1]
    Ans = ai[1]
    for i in range(2, n + 1):
        a = M
        b = bi[i]
        c = (ai[i] - Ans % b + b) % b
        gcd = exgcd(a, b, x, y)
        bg = b // gcd
        if c % gcd != 0:
            return -1

        x[0] = (x[0] * (c // gcd)) % bg

        Ans = Ans + x[0] * M

        M = M * bg
        Ans = (Ans % M + M) % M

    return (Ans % M + M) % M


n, m = map(int, input().split())

ai.append(-1)
bi.append(-1)

for i in range(1, n + 1):
    l,r = map(int, input().split())
    bi.append(l)
    ai.append(r)

Ans = excrt()

if Ans == -1:
    print("he was definitely lying");
elif Ans >= m:
    print("he was probably lying")
else:
    print(Ans)
