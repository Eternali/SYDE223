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

    def __add__(self, other):
        if len(self.data) >= len(other.data):
            l = self.data
            s = other.data
        else:
            l = other.data
            s = self.data
        
        added = [ c + s[i] if i < len(s) else c for (i, c) in enumerate(l) ]
        return Polynomial(A=added, size=len(added))
    
    def __sub__(self, other):
        if len(self.data) >= len(other.data):
            l = self.data
            s = other.data
        else:
            l = other.data
            s = self.data

        left = self.data
        right = other.data

        subtracted = [ c - right[i] if i < len(right) else c for (i, c) in enumerate(left) ]
        if len(right) > len(left):
            subtracted += [ -1 * c for c in right[len(left):] ]
        return Polynomial(A=subtracted, size=len(subtracted))

    def __mul__(self, other):
        return Polynomial()

    def to_string(self):
        if len(self.data) == 0:
            return '0'
        prefix = lambda c, i: '' if i == len(self.data) - 1 else ' + ' if c > 0 else ' - '
        to_str = lambda c, i: f'{prefix(c, i)}{abs(c)}' + (f'x^{i}' if i != 0 else '') if c != 0 else ''
        return ''.join([ to_str(c, i) for (i, c) in reversed(list(enumerate(self.data))) ])

    def print(self):
        print(self.to_string())

    def derivative(self):
        return Polynomial()
