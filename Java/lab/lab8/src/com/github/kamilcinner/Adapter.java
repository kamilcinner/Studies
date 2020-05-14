package com.github.kamilcinner;

import javax.swing.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Adapter extends WindowAdapter {
    @Override
    public void windowOpened(WindowEvent e) {
        JOptionPane.showMessageDialog(null, "Welcome!");
    }

    @Override
    public void windowClosed(WindowEvent e) {
        System.exit(0);
    }
}
