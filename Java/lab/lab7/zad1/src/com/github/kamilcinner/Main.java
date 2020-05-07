package com.github.kamilcinner;

import javax.swing.*;
import java.awt.*;

public class Main {

    public static void main(String[] args) {
	    JFrame window = new JFrame("zad1");
        Container container = window.getContentPane();

        // Add buttons to the window.
        final int BUTTON_COUNT = 9;
        JButton[] buttons = new JButton[BUTTON_COUNT];
        final String[] LOCATIONS = { BorderLayout.CENTER, BorderLayout.NORTH, BorderLayout.WEST, BorderLayout.EAST,
                BorderLayout.SOUTH };
        for (int i = 0; i < BUTTON_COUNT; i++) {
            buttons[i] = new JButton("OK "+ i);
            container.add(buttons[i], LOCATIONS[i % 5]);
        }

        // Add window close on exit.
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Set window size and location.
        window.setSize(300, 300);
        window.setLocation(100, 100);

        // Change Layout Manager.
        container.setLayout(new FlowLayout());
//        container.setLayout(new GridLayout(2, 4));
//        container.setLayout(new BoxLayout(container, BoxLayout.PAGE_AXIS));
//        container.setLayout(new SpringLayout());

        window.setVisible(true);
    }
}
