#!/usr/bin/python3

## Conrad Heidebrecht (20710386)
## Kyle Lane ()

from polynomial import Polynomial


def assert_that(boolean, msg=''):
    try:
        assert(boolean)
        print('Passed : ' + msg)
    except AssertionError:
        print('Failed : ' + msg)
    return boolean


class PolynomialTest:

    def __init__(self):
        self.a = None
        self.b = None

    def test_constructors(self):
        print('[**] Testing constructors:')
        self.a = Polynomial(A=[1,2,3,4,5], size=5)
        assert_that(self.a.data == [1,2,3,4,5], msg='Construct polynomial with array')
        self.a = Polynomial()
        assert_that(len(self.a.data) <= 1000 and all([ -1000 <= c <= 1000 for c in self.a.data ]), 'Generate random polynomial')
        self. a = Polynomial(fileName='data.txt')
        assert_that(self.a.data == [5,4,3,2,1], 'Load polynomial from file')

    def test_empty(self):
        print('[**] Testing empty polynomials')
        self.a = Polynomial(A=[], size=0)
        self.b = Polynomial(A=[], size=0)
        assert_that(self.a.to_string() == '0', 'Empty polynomial should print 0')
        assert_that(self.a.derivative().data == [], 'Empty polynomial should have a derivative of 0')
        assert_that((self.a + self.b).data == [], 'Adding empty polynomials should return nothing')
        assert_that((self.a - self.b).data == [], 'Subtracting empty polynomials should return nothing')
        assert_that((self.a * self.b).data == [], 'Multiplying empty polynomials should return nothing')

    def test_regular(self):
        print('[**] Testing regular polynomials')
        self.a = Polynomial(A=[1,2,3,4,5], size=5)
        self.b = Polynomial(A=[6,7,8,9,10], size=5)
        assert_that(self.a.to_string() == '5x^4 + 4x^3 + 3x^2 + 2x + 1', 'Polynomial should print properly')
        assert_that(self.a.derivative().data == [2,6,12,20], 'Derivative should calculate correctly.')
        assert_that((self.a + self.b).data == [7,9,11,13,15], 'Adding polynomials should calculate correctly')
        assert_that((self.a - self.b).data == [-5,-5,-5,-5,-5], 'Subtracting polynomials should calculate correctly')
        assert_that((self.a * self.b).data == [6,19,40,70,110,114,106,85,50], 'Multiplying polynomials should calculate correctly')
    
    def test_with_zeros(self):
        print('[**] Testing polynomials with some coefficients equal to 0')
        self.a = Polynomial(A=[0,2,7,0,5], size=5)
        self.b = Polynomial(A=[6,0,8,9,0], size=5)
        assert_that(self.a.to_string() == '5x^4 + 7x^2 + 2x', 'Polynomial should print properly')
        assert_that(self.a.derivative().data == [2,14,0,20], 'Derivative should calculate correctly.')
        assert_that((self.a + self.b).data == [6,2,15,9,5], 'Adding polynomials should calculate correctly')
        assert_that((self.a - self.b).data == [-6,2,-1,-9,5], 'Subtracting polynomials should calculate correctly')
        assert_that((self.a * self.b).data == [0,12,42,16,104,63,40,45], 'Multiplying polynomials should calculate correctly')
    
    def test_diff_lens(self):
        print('[**] Testing polynomials of different lengths')
        self.a = Polynomial(A=[1,8,4], size=3)
        self.b = Polynomial(A=[6,7,8,1,13], size=5)
        assert_that(self.a.to_string() == '4x^2 + 8x + 1', 'Polynomial should print properly')
        assert_that(self.a.derivative().data == [8,8], 'Derivative should calculate correctly.')
        assert_that((self.a + self.b).data == [7,15,12,1,13], 'Adding polynomials should calculate correctly')
        assert_that((self.a - self.b).data == [-5,1,-4,-1,-13], 'Subtracting polynomials should calculate correctly')
        assert_that((self.a * self.b).data == [6,55,88,93,53,108,52], 'Multiplying polynomials should calculate correctly')

    def run(self):
        self.test_constructors()
        print()
        self.test_empty()
        print()
        self.test_regular()
        print()
        self.test_with_zeros()
        print()
        self.test_diff_lens()


if __name__ == '__main__':
    PolynomialTest().run()
