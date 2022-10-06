mod = int(10**9 + 7)

def solve(p, a, k):
  # compute p^a + p^{a+1} + ... + p^{2^k a}
  first = pow(p, a, mod)
  ratio = p
  terms = (pow(2, k, mod-1)*a - a + 1)%(mod - 1)
  res = (first * (pow(ratio, terms, mod) - 1)) % mod
  res *= pow(ratio - 1, mod-2, mod)
  return res%mod

for _ in range(int(input())):
  ans = 1
  n, k = map(int, input().split())
  for i in range(2, n+1):
    if i*i > n:
      break
    if n%i != 0:
      continue
    ct = 0
    while n%i == 0:
      n //= i
      ct += 1
    ans *= solve(i, ct, k)
    ans %= mod
  if n > 1:
    ans *= solve(n, 1, k)
    ans %= mod
  print(ans)
