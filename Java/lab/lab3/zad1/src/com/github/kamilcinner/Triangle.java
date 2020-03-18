package com.github.kamilcinner;

class InvalidTriangle extends Exception {

}

class Triangle {
    
    private double a, b, c;
    
    Triangle(double a, double b, double c) throws InvalidTriangle {
        if (a+b<c || a+c<b || b+c<a) {
            throw new InvalidTriangle();
        } else {
            this.a = a;
            this.b = b;
            this.c = c;
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
        if ((a*a + b*b == c*c) || (a*a + c*c == b*b) || (b*b + c*c == a*a)) return "rectangular";
        else if ((a*a + b*b < c*c) || (a*a + c*c < b*b) || (b*b + c*c < a*a)) return "obtuse";
        else return "acute"; // if ((a*a + b*b < c*c) && (a*a + c*c < b*b) && (b*b + c*c < a*a))
    }
}
