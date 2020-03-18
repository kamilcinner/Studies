package com.github.kamilcinner;

import java.util.Scanner;

public class Main {
    private static void print(String s) {
        System.out.println(s);
    }

    private static void printNumbers(double[] numbers) {
        for (double n : numbers) {
            print(Double.toString(n));
        }
    }

    private static double computeAverage(double[] args) {
        double average = 0;
        for (double a : args) {
            average += a;
        }
        average /= args.length;
        return average;
    }

    private static String markInWords(double mark) {
        if (mark <= 5.0 && mark > 4.5) return "bardzo dobra";
        else if (mark <= 4.5 && mark > 3.5) return "dobra";
        else if (mark <= 3.5 && mark > 2.5) return "dostateczna";
        else return "niedostateczna";
    }

    private static String markInShortWord(String mark) {
        switch (mark) {
            case "bardzo dobra": return "bdb";
            case "dobra": return "db";
            case "dostateczna": return "dst";
            default: return "ndst";
        }
    }

    public static void main(String[] args) {
//        print("Enter number of args:");
//        Scanner scanner = new Scanner(System.in);
//        int argsCount = scanner.nextInt();
//
//        double[] numbers = new double[argsCount];
//        for (int i = 0;i < argsCount;i++) {
//            print("Enter args["+i+"]: ");
//            numbers[i] = scanner.nextDouble();
//        }
        // ad.2 what the author had on mind?
        double[] numbers = new double[5];
        for (int i = 0;i < 5;i++) {
            numbers[i] = Double.parseDouble(args[i]);
        }
        print("Show args count:");
        print(Integer.toString(args.length));

        print("Show given numbers:");
        printNumbers(numbers);
        print("Show average from start args:");
        double average = computeAverage(numbers);
        print(String.valueOf(average));
        print("Show average in words:");
        String markAsWord = markInWords(average);
        print(markAsWord);
        print("Show average in short word:");
        print(markInShortWord(markAsWord));
    }
}
