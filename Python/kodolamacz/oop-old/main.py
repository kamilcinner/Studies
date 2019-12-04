import math


class SquareFunction:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

    def solve(self):
        if self.a == 0:
            if self.b == 0 and self.c == 0:
                return -1, 0
            return 1, - self.c / self.b
        else:
            delta = self.b * self.b - 4 * self.a * self.c
            if delta < 0:
                return 0, 0
            elif delta == 0:
                return 1, - self.b / (2 * self.a)
            else:
                return 2, (- self.b - math.sqrt(delta)) / (2 * self.a), (- self.b + math.sqrt(delta)) / (2 * self.a)


def printResult(result):
    if result[0] == -1:
        print("The given function has infinite number of zeros")
    elif result[0] == 0:
        print("The given function has no zeros")
    elif result[0] == 1:
        print("The given function has one zero: " + str(result[1]))
    elif result[0] == 2:
        print("The given function has two zeros: " + str(result[1]) + " and " + result[2])
    else:
        print("Something went wrong!!!")


def main():
    f1 = SquareFunction(4, 0, 0)
    printResult(f1.solve())


if __name__ == "__main__":
    main()