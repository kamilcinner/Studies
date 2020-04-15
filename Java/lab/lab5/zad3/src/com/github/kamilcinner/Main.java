package com.github.kamilcinner;

public class Main {

    public static void main(String[] args) {
        Thread thread = new Thread(new RunnableImpl());
        thread.start();

        Thread thread2 = new Thread(()->{
            for (int i = 0; i < 10; i++) {
                System.out.println("Thread 2: " + i * 10);
            }
        });
        thread2.start();
    }
}
