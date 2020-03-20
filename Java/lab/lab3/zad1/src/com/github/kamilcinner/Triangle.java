package com.github.kamilcinner;

import java.util.Arrays;

class InvalidTriangle extends Exception {
}

class Triangle {
    
    private double a, b, c;
    
    Triangle(double a, double b, double c) throws InvalidTriangle {
        double[] sides = new double[3];
        sides[0] = a;
        sides[1] = b;
        sides[2] = c;
        Arrays.sort(sides);

        if (sides[0] + sides[1] < sides[2]) {
            throw new InvalidTriangle();
        } else {
            this.a = sides[0];
            this.b = sides[1];
            this.c = sides[2];
        }
    }
    
    double getCircumference() {
        return a + b + c;
    }

    double getField() {
        double p = (a + b + c) / 2.0;
        return Math.sqrt(p*(p-a)*(p-b)*(p-c));
    }

    double getA() {
        return a;
    }

    double getB() {
        return b;
    }

    double getC() {
        return c;
    }

    static String getType(double a, double b, double c) {
        double[] sides = new double[3];
        sides[0] = a;
        sides[1] = b;
        sides[2] = c;
        Arrays.sort(sides);
        if (Math.pow(sides[0], 2) + Math.pow(sides[1], 2) == Math.pow(sides[2], 2)) return "rectangular";
        else if (Math.pow(sides[0], 2) + Math.pow(sides[1], 2) < Math.pow(sides[2], 2)) return "obtuse";
        else return "acute";
    }
}
