all_ns = []
all_ints = []
while True:
    usr = input()
    if not len(usr.strip()):
        break
    [ n, *ints ] = usr.split(' ')
    all_ns.append(int(n))
    all_ints.append([ int(i) for i in ints ])

for i in range(len(all_ns)):
    n = all_ns[i]
    ints = all_ints[i]

    diffs = set([ abs(ints[i] - ints[i + 1]) for i in range(n - 1)])

    if len(diffs) == n - 1 and max(diffs) == n - 1:
        print('Jolly')
    else:
        print('Not jolly')
