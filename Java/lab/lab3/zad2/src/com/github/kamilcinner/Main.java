package com.github.kamilcinner;

public class Main {

    private static <T> void print(T arg) {
        System.out.println(arg);
    }

    private static void printSquareFunction(SquareFunction sq, String sqName, Point p1, Point p2) {
        print("Square Function "+sqName+":");
        print("y = ("+ sq.a +"x^2) + ("+ sq.b +"x) + ("+ sq.c +")");
        print("Compute y for x="+p1.args[0]+":");
        print(sq.computeY(p1));
        print("Compute y for x="+p2.args[0]+":");
        print(sq.computeY(p2));
        print("Solve function:");
        double[] results = sq.solve();
        print(results[0] +", "+ results[1]);
        print("");
    }

    public static void main(String[] args) {
        SquareFunction sq1 = new SquareFunction(3, 4, 5);
        SquareFunction sq2 = new SquareFunction(4, 0, 0);
        SquareFunction sq3 = new SquareFunction(1, 5, 7);
        SquareFunction sq4 = new SquareFunction(-4, 22, 13);
        SquareFunction sq5 = new SquareFunction(0, 0, 0);

        Point p1 = new Point(5,6);
        Point p2 = new Point(-4,8);

        printSquareFunction(sq1, "sq1", p1, p2);
        printSquareFunction(sq2, "sq2", p1, p2);
        printSquareFunction(sq3, "sq3", p1, p2);
        printSquareFunction(sq4, "sq4", p1, p2);
        printSquareFunction(sq5, "sq5", p1, p2);
    }
}
