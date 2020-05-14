package com.github.kamilcinner;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

public class Main extends JFrame implements ActionListener, ItemListener {
    JComboBox comboBox;
    JLabel comboBoxLabel;

    Main(String title) {
        super(title);
        this.setBackground(Color.BLUE);
        // Add window close on exit.
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Set window size and location.
        this.setSize(300, 300);
        this.setLocation(100, 100);

        // Add and set layout.
        SpringLayout springLayout = new SpringLayout();
        this.setLayout(springLayout);

        // Add text field.
        JTextField textField = new JTextField(20);
        this.add(textField);

        // Add spring layout constraints.
        springLayout.putConstraint(SpringLayout.WEST, textField, 40, SpringLayout.WEST, this);
        springLayout.putConstraint(SpringLayout.NORTH, textField, 10, SpringLayout.NORTH, this);

        // Create panel.
        JPanel panel = new JPanel();
        BoxLayout boxLayout = new BoxLayout(panel, BoxLayout.X_AXIS);
        Dimension preferredPanelDimension = new Dimension(280, 30);
        panel.setPreferredSize(preferredPanelDimension);

        // Add three buttons to the panel.
        JButton button1 = new JButton("1");
        JButton button2 = new JButton("2");
        JButton button3 = new JButton("3");

        panel.add(button1);
        panel.add(button2);
        panel.add(button3);

        // Add panel to the window.
        this.add(panel);
        springLayout.putConstraint(SpringLayout.WEST, panel, 10, SpringLayout.WEST, this);
        springLayout.putConstraint(SpringLayout.NORTH, panel, 40, SpringLayout.SOUTH, textField);

        // Add combo box.
        String[] numberStrings = { "One", "Two", "Three", "Four", "Five" };

        comboBox = new JComboBox(numberStrings);
        this.add(comboBox);
        springLayout.putConstraint(SpringLayout.NORTH, comboBox, 20, SpringLayout.SOUTH, panel);

        // Add label for combo box.
        comboBoxLabel = new JLabel(comboBox.getSelectedItem().toString(), JLabel.TRAILING);
        this.add(comboBoxLabel);
        comboBoxLabel.setLabelFor(comboBox);
        springLayout.putConstraint(SpringLayout.WEST, comboBoxLabel, 10, SpringLayout.EAST, comboBox);
        springLayout.putConstraint(SpringLayout.NORTH, comboBoxLabel, 25, SpringLayout.SOUTH, panel);

        // Add listeners to buttons.
        button1.addActionListener(this);
        button2.addActionListener(actionEvent -> System.out.println("Pressed " + getActionEventButtonText(actionEvent)));
        button3.addActionListener(actionEvent -> System.out.println("Pressed " + getActionEventButtonText(actionEvent)));

        // Add listener to window.
        addWindowListener(new Adapter());

        // Add listener to combo box.
        comboBox.addItemListener(this);

        // Show window.
        this.setVisible(true);
    }

    public static void main(String[] args) {
	    Main window = new Main("zad1");
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        System.out.println("Pressed " + getActionEventButtonText(actionEvent));
    }

    @Override
    public void itemStateChanged(ItemEvent itemEvent) {
        comboBoxLabel.setText(itemEvent.getItem().toString());
    }

    private String getActionEventButtonText(ActionEvent actionEvent) {
        String text = actionEvent.getSource().toString();
        int textPosition = text.lastIndexOf("text") + 5;
        return text.substring(textPosition, textPosition + 1);
    }
}
