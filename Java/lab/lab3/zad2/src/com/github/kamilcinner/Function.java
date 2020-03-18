package com.github.kamilcinner;

abstract class Function {

    double a, b;

    Function(double a, double b) {
        this.a = a;
        this.b = b;
    }

    public abstract double computeY(Point p);
}
