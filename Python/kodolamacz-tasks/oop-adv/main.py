from abc import ABC, abstractmethod
import math


class Node(ABC):
    @abstractmethod
    def name(self):
        pass

    def printNode(self):
        print(f"Computing {self.name}.", end=' ')

    @abstractmethod
    def value(self):
        pass


class Number(Node):
    def __init__(self, number):
        self.number = number

    def name(self):
        return "number"

    def printNode(self):
        print(f"I am a number {self.number}")

    def value(self):
        return self.number


class Addition(Node):
    def __init__(self, comp1, comp2):
        self.comp1 = comp1
        self.comp2 = comp2

    def name(self):
        return "addition"

    def printNode(self):
        self.comp1.printNode()
        self.comp2.printNode()
        super().printNode()
        print(f"{self.comp1.value()} + {self.comp2.value()} = {self.value()}")

    def value(self):
        return self.comp1.value() + self.comp2.value()


class Subtraction(Node):
    def __init__(self, minuend, subtrahend):
        self.minuend = minuend
        self.subtrahend = subtrahend

    def name(self):
        return "subtraction"

    def printNode(self):
        self.minuend.printNode()
        self.subtrahend.printNode()
        super().printNode()
        print(f"{self.minuend.value()} - {self.subtrahend.value()} = {self.value()}")

    def value(self):
        return self.minuend.value() - self.subtrahend.value()


class Multiply(Node):
    def __init__(self, factor1, factor2):
        self.factor1 = factor1
        self.factor2 = factor2

    def name(self):
        return "multiply"

    def printNode(self):
        self.factor1.printNode()
        self.factor2.printNode()
        super().printNode()
        print(f"{self.factor1.value()} * {self.factor2.value()} = {self.value()}")

    def value(self):
        return self.factor1.value() * self.factor2.value()


class Division(Node):
    def __init__(self, dividend, divider):
        self.dividend = dividend
        self.divider = divider

    def name(self):
        return "division"

    def printNode(self):
        self.dividend.printNode()
        self.divider.printNode()
        super().printNode()
        print(f"{self.dividend.value()} / {self.divider.value()} = {self.value()}")

    def value(self):
        return self.dividend.value() / self.divider.value()


class Factorial(Node):
    def __init__(self, number):
        self.number = number

    def name(self):
        return "factorial"

    def printNode(self):
        self.number.printNode()
        super().printNode()
        print(f"{self.number.value()}! = {self.value()}")

    def value(self):
        return math.factorial(self.number.value())


def main():
    fakeMinusOne = Number(1)
    four = Number(4)
    five = Number(5)
    seven = Number(7)
    eight = Number(8)

    addition = Addition(five, seven)
    subtraction = Subtraction(eight, four)
    multiply = Multiply(addition, subtraction)
    division = Division(multiply, fakeMinusOne)
    factorial = Factorial(division)

    factorial.printNode()


if __name__ == "__main__":
    main()