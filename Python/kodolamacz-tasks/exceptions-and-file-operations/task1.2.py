class Fraction:
    def __init__(self, numerator, denominator):
        if denominator == 0:
            raise ValueError("You cannot set 0 as denominator!")
        if not isinstance(numerator, int) or not isinstance(denominator, int):
            raise ValueError("You must provide integer numbers!")
        self.numerator = numerator
        self.denominator = denominator

    def shorten(self):
        divider = euclidean(self.numerator, self.denominator)
        if divider != 1:
            self.numerator //= divider
            self.denominator //= divider

    @staticmethod
    def add(f1, f2):
        f = Fraction(f1.numerator * f2.denominator + f2.numerator * f1.denominator, f1.denominator * f2.denominator)
        f.shorten()
        return f

    @staticmethod
    def subtract(f1, f2):
        f = Fraction(f1.numerator * f2.denominator - f2.numerator * f1.denominator, f1.denominator * f2.denominator)
        f.shorten()
        return f

    @staticmethod
    def multiply(f1, f2):
        f = Fraction(f1.numerator * f2.numerator, f1.denominator * f2.denominator)
        f.shorten()
        return f

    @staticmethod
    def divide(f1, f2):
        if f2.numerator == 0:
            raise ZeroDivisionError("You cannot divide by 0!")
        f = Fraction(f1.numerator * f2.denominator, f1.denominator * f2.numerator)
        f.shorten()
        return f


def euclidean(a, b): # we can use builtin gcd() function
    if b != 0:
        return euclidean(b, a % b)
    return a


def printFraction(f):
    print(str(f.numerator) + "/" + str(f.denominator))


def main():
    f1 = Fraction(3, 29)
    f2 = Fraction(0, 25)
    printFraction(f1)
    printFraction(f2)

    f2.shorten()
    printFraction(f2)

    f3 = Fraction.add(f1, f2)
    printFraction(f3)

    f4 = Fraction.subtract(f1, f2)
    printFraction(f4)

    f5 = Fraction.multiply(f1, f2)
    printFraction(f5)

    try:
        f6 = Fraction.divide(f1, f2)
        printFraction(f6)
    except ZeroDivisionError as e:
        print(e)


if __name__ == "__main__":
    main()