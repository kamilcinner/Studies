import math


class SquareFunction:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

    def solve(self):
        if self.a == 0 and self.b == 0:
            if self.c == 0:
                return float("inf"), float("inf")
            else:
                return float("nan"), float("nan")
        if self.a == 0:
            return - self.c / self.b, - self.c / self.b
        delta = self.b * self.b - 4 * self.a * self.c
        if delta < 0:
            return float("nan"), float("nan")
        return (- self.b - math.sqrt(delta)) / (2 * self.a), (- self.b + math.sqrt(delta)) / (2 * self.a)


def main():
    print(SquareFunction(3, 4, 5).solve())
    print(SquareFunction(4, 0, 0).solve())
    print(SquareFunction(1, 5, 7).solve())
    print(SquareFunction(-4, 22, 13).solve())
    print(SquareFunction(0, 0, 0).solve())


if __name__ == "__main__":
    main()