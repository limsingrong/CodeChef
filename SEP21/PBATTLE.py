for _ in range(int(input())):
  n = int(input())
  a = list(map(int, input().split()))
  b = list(map(int, input().split()))
  c = [(a[i], b[i]) for i in range(n)]
  c.sort()
  ans, mx = 0, 0
  for i in reversed(range(n)):
    if c[i][1] > mx:
      ans += 1
    mx = max(mx, c[i][1])
  print(ans)
