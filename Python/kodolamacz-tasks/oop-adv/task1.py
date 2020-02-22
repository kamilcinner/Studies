from abc import ABC, abstractmethod
import math

class Figure(ABC):
    def __init__(self, name):
        self.name = name

    @abstractmethod
    def computeCircumference(self):
        pass

    @abstractmethod
    def computeField(self):
        pass

    @abstractmethod
    def getFigureType(self):
        pass

    def printFigure(self):
        print("I am " + self.getFigureType() + ". My circumference = " + str(self.computeCircumference()) + ". My field = " + str(self.computeField()))


class Circle(Figure):
    def __init__(self, r):
        super().__init__(self.getFigureType())
        self.r = r

    def computeCircumference(self):
        return 2 * math.pi * self.r

    def computeField(self):
        return math.pi * math.pow(self.r, 2)

    def getFigureType(self):
        return "Circle"


class Triangle(Figure):
    def __init__(self, a, b, c):
        super().__init__(self.getFigureType())
        self.a = a
        self.b = b
        self.c = c

    def computeCircumference(self):
        return self.a + self.b + self.c

    def computeField(self):
        p1 = self.a + self.b + self.c
        p2 = self.a + self.b - self.c
        p3 = self.a - self.b + self.c
        p4 = - self.a + self.b + self.c
        return math.sqrt(p1 * p2 * p3 * p4) / 4

    def getFigureType(self):
        return "Triangle"


class Square(Figure):
    def __init__(self, a):
        super().__init__(self.getFigureType())
        self.a = a

    def computeCircumference(self):
        return 4 * self.a

    def computeField(self):
        return self.a * self.a

    def getFigureType(self):
        return "Square"


class Rectangle(Square):
    def __init__(self, a, b):
        super().__init__(a)
        self.name = self.getFigureType()
        self.b = b

    def computeCircumference(self):
        return 2 * self.a + 2 * self.b

    def computeField(self):
        return self.a * self.b

    def getFigureType(self):
        return "Rectangle"


def main():
    square = Square(10)
    square.printFigure()

    rectangle = Rectangle(2, 6.5)
    rectangle.printFigure()

    triangle = Triangle(3,4,5)
    triangle.printFigure()

    circle = Circle(25)
    circle.printFigure()

    figureList = [square, rectangle, triangle, circle]
    fieldSum = 0
    circumferenceSum = 0

    for f in figureList:
        fieldSum += f.computeField()
        circumferenceSum += f.computeCircumference()

    print(fieldSum)
    print(circumferenceSum)


if __name__ == "__main__":
    main()
