package com.github.kamilcinner;

public class Main {

    private static <T> void print(T arg) {
        System.out.println(arg);
    }

    private static void printTriangle(Triangle t, String triangleName) {
        print("Triangle "+triangleName+":");
        print(t.getA());
        print(t.getB());
        print(t.getC());
        print("Field:");
        print(t.getField());
        print("Circumference:");
        print(t.getCircumference());
        print("Type:");
        print(Triangle.getType(t.getA(), t.getB(), t.getC()));
    }

    public static void main(String[] args) {
        try {
            Triangle t1 = new Triangle(3, 4, 5);
            printTriangle(t1, "t1");

            Triangle t2 = new Triangle(4, 4, 4);
            printTriangle(t2, "t2");

//            Triangle t3 = new Triangle(1,1,10);
//            printTriangle(t3, "t3");
        } catch (InvalidTriangle e) {
            print("You can't create triangle from given side lengths!");
            e.printStackTrace();
        }

    }
}
