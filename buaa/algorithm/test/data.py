from random import randint

# max = 10
# fout = open('input.txt', "w")

# n = random.randint(1, max)
# m = random.randint(1, max)
# fout.write("{0} {1}\n".format(n, m))

# for _ in range(m):
#     lo = random.randint(1, n)
#     hi = random.randint(lo, n)
#     fout.write("{0} {1}\n".format(lo, hi))

fout = open('input.txt', 'w')

    
t = 50
fout.write("{0}\n".format(t))
for _ in range(t):
    n = randint(2, 50)
    k = randint(0, 10)
    fout.write("{0} {1}\n".format(n, k))
    for _ in range(k):
        a = randint(1, n - 1)
        b = randint(a + 1, n)
        fout.write("{0} {1}\n".format(a, b))
