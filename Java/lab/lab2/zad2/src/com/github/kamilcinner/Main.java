package com.github.kamilcinner;

public class Main {
    private static int argsCount = 0;

    private static void print(String s) {
        System.out.println(s);
    }

    private Main(String[] args) {
        argsCount = args.length;
    }

    private static void printString(String s) {
        System.out.println(s);
    }

    private static void printArguments(String[] args) {
        for (String s : args) {
            printString(s);
        }
    }

    private static double computeAverage(double[] args) {
        double average = 0;
        for (double a : args) {
            average += a;
        }
        return average /= args.length;
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
        new Main(args); // TODO: This looks kinda weird
        print("Show start args:");
        printArguments(args);

        print("Show average from start args:");
        double[]  numbers = new double[argsCount];
        for (int i = 0;i < argsCount;i++) {
            numbers[i] = Double.parseDouble(args[i]);
        }
        double average = computeAverage(numbers);
        print(String.valueOf(average));
        print("Show average in words:");
        String markAsWord = markInWords(average);
        print(markAsWord);
        print("Show average in short word:");
        print(markInShortWord(markAsWord));
    }
}
