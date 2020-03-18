package com.github.kamilcinner;

class SquareFunction extends Function {

    double c;

    SquareFunction(double a, double b, double c) {
        super(a, b);
        this.c = c;
    }

    public double computeY(Point p) {
        return a*Math.pow(p.args[0], 2) + b*p.args[0] + c;
    }

    double[] solve() {
        if (a == 0 && b == 0) {
            if (c == 0) {
                return new double[]{Double.POSITIVE_INFINITY, Double.POSITIVE_INFINITY};
            } else {
                return new double[]{Double.NaN, Double.NaN};
            }
        }
        if (a == 0) {
            return new double[]{-c/b, -c/b};
        }
        double delta = b*b - 4*a*c;
        if (delta < 0) {
            return new double[]{Double.NaN, Double.NaN};
        }
        return new double[]{(-b-Math.sqrt(delta)) / (2*a), (-b+Math.sqrt(delta)) / (2*a)};
    }
}