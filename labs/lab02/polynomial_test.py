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
        assert_that(self.a.to_string() == '5x^4 + 4x^3 + 3x^2 + 2x^1 + 1', 'Polynomial should print properly')
        assert_that(self.a.derivative().data == [], 'Derivative should calculate correctly.')
        assert_that((self.a + self.b).data == [7,9,11,13,15], 'Adding polynomials should calculate correctly')
        assert_that((self.a - self.b).data == [-5,-5,-5,-5,-5], 'Subtracting polynomials should calculate correctly')
        assert_that((self.a * self.b).data == [], 'Multiplying polynomials should calculate correctly')
    
    def test_with_zeros(self):
        print('[**] Testing polynomials with some coefficients equal to 0')
        self.a = Polynomial(A=[1,2,0,4,5], size=5)
        self.b = Polynomial(A=[6,7,8,9,0], size=5)
        assert_that(self.a.to_string() == '5x^4 + 4x^3 + 2x^1 + 1', 'Polynomial should print properly')
        assert_that(self.a.derivative().data == [], 'Derivative should calculate correctly.')
        assert_that((self.a + self.b).data == [7,9,8,13,5], 'Adding polynomials should calculate correctly')
        assert_that((self.a - self.b).data == [-5,-5,-8,-5,5], 'Subtracting polynomials should calculate correctly')
        assert_that((self.a * self.b).data == [], 'Multiplying polynomials should calculate correctly')
    
    def test_diff_lens(self):
        print('[**] Testing polynomials of different lengths')
        self.a = Polynomial(A=[1,2,3,4,5], size=5)
        self.b = Polynomial(A=[6,7,8,1,13,2,32], size=7)
        assert_that(self.a.to_string() == '5x^4 + 4x^3 + 3x^2 + 2x^1 + 1', 'Polynomial should print properly')
        assert_that(self.a.derivative().data == [], 'Derivative should calculate correctly.')
        assert_that((self.a + self.b).data == [7,9,11,5,18,2,32], 'Adding polynomials should calculate correctly')
        assert_that((self.a - self.b).data == [-5,-5,-5,3,-8,-2,-32], 'Subtracting polynomials should calculate correctly')
        assert_that((self.a * self.b).data == [], 'Multiplying polynomials should calculate correctly')

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
