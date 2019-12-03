import math


class Complex:
    def __init__(self, re, im):
        self.re = re
        self.im = im
    def abs(self):
        return math.sqrt(pow(self.re, 2) + pow(self.im, 2))
    def printComplex(self):
        print(str(self.re) + " + " + str(self.im) + "i")
    @staticmethod
    def add(c1, c2):
        return Complex(c1.re + c2.re, c1.im + c2.im)
    @staticmethod
    def mul(c1, c2):
        return Complex(c1.re * c2.re - c1.im * c2.im, c1.re * c2.im + c2.re * c1.im)

def main():
    # print(str(pow(2, 3)))
    c1 = Complex(12, 3)
    c2 = Complex(1, 2)

    c1.printComplex()
    print(str(c1.abs()))
    c2.printComplex()
    print(str(c2.abs()))

    c3 = Complex.add(c1, c2)
    c3.printComplex()

    c4 = Complex.mul(c1, c3)
    c4.printComplex()


if __name__ == "__main__":
    main()