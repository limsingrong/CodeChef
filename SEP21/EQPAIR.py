for _ in range(int(input())):
  n = int(input())
  a = list(map(int, input().split()))
  d = dict()
  for x in a:
    if x not in d:
      d[x] = 1
    else:
      d[x] += 1
  ans = 0
  for x in d.values():
    ans += x*(x-1)//2
  print(ans)
