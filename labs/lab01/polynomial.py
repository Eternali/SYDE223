#!/usr/bin/python3

## Conrad Heidebrecht (20710386)
## Kyle Lane ()

import random


class Polynomial:

    def __init__(self, A=None, size=None, fileName=''):
        if A == None and size == None and fileName == '':
            self.data = [ random.randint(-1000, 1000) for _ in range(random.randint(0, 1000)) ]
        elif fileName != '':
            with open(fileName, 'r') as f:
                size = f.readline()
                self.data = []
                for line in f.readlines():
                    self.data.append(int(line))
        elif size != None:
            self.data = [ A[i] for i in range(size) ]
        else:
            raise Exception()

    def __eq__(self, other):
        return self.data == other.data;

    def _order_arr(self, first, second):
        if len(first) >= len(second):
            return (first, second)
        return (second, first)

    def __add__(self, other):
        (l, s) = self._order_arr(self.data, other.data)
        added = [ c + s[i] if i < len(s) else c for (i, c) in enumerate(l) ]
        return Polynomial(A=added, size=len(added))
    
    def __sub__(self, other):
        left = self.data
        right = other.data
        subtracted = [ c - right[i] if i < len(right) else c for (i, c) in enumerate(left) ]
        if len(right) > len(left):
            subtracted += [ -1 * c for c in right[len(left):] ]
        return Polynomial(A=subtracted, size=len(subtracted))

    def __mul__(self, other):
        (l, s) = self._order_arr(self.data, other.data)
        if len(s) < 1:
            return Polynomial(A=[], size=0)
        s += [ 0 for _ in range(len(l) - len(s)) ]
        tmp = []
        for (i, c) in enumerate(l):
            tmp += [ (i + j, c * d) for (j, d) in enumerate(s) if c * d != 0 ]
        mult = [ 0 for _ in range(max(set([ t[0] for t in tmp ])) + 1) ]
        for (i, c) in enumerate(mult):
            mult[i] = sum([ d for (j, d) in tmp if j == i ])

        return Polynomial(A=mult, size=len(mult))

    def to_string(self):
        if len(self.data) == 0:
            return '0'
        # last = reversed(self.data).index(0)
        prefix = lambda c, i: '' if i == len(self.data) - 1 else ' + ' if c > 0 else ' - '
        to_str = lambda c, i: f'{prefix(c, i)}{abs(c)}' + (f'x^{i}' if i > 1 else 'x' if i != 0 else '') if c != 0 else ''
        return ''.join([ to_str(c, i) for (i, c) in reversed(list(enumerate(self.data))) ])

    def print(self):
        print(self.to_string())

    def derivative(self):
        return Polynomial(
            A=[ c * (i + 1) for (i, c) in enumerate(self.data[1:]) ],
            size=len(self.data) - 1
        )
