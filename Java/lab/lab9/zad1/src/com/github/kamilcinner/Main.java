package com.github.kamilcinner;

import javax.swing.*;
import java.awt.*;

public class Main extends JFrame {

    Main() {
        this.setSize(300, 300);

        SpringLayout springLayout = new SpringLayout();
        this.setLayout(springLayout);

        // Add Forename Panel.
        Panel forenamePanel = new Panel();
        BoxLayout forenameBoxLayout = new BoxLayout(forenamePanel, BoxLayout.X_AXIS);
        JLabel forenameLabel = new JLabel("Forename:");
        JTextField forenameTextField = new JTextField(10);
        forenamePanel.add(forenameLabel, BorderLayout.EAST);
        forenamePanel.add(forenameTextField, BorderLayout.WEST);
        this.add(forenamePanel);

        // Add Surname Panel.
        Panel surnamePanel = new Panel();
        BoxLayout surnameBoxLayout = new BoxLayout(surnamePanel, BoxLayout.X_AXIS);
        JLabel surnameLabel = new JLabel("Surname:");
        JTextField surnameTextField = new JTextField(10);
        surnamePanel.add(surnameLabel, BorderLayout.EAST);
        surnamePanel.add(surnameTextField, BorderLayout.WEST);
        this.add(surnamePanel);
        springLayout.putConstraint(SpringLayout.NORTH, surnamePanel, 0, SpringLayout.SOUTH, forenamePanel);


    }

    public static void main(String[] args) {
        Main window = new Main();
        window.setVisible(true);
    }
}
