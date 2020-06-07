package com.github.kamilcinner;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.*;

public class Main extends JFrame implements ActionListener, ItemListener, ChangeListener {

    public class MyMouseAdapter extends MouseAdapter {

        @Override
        public void mouseEntered(MouseEvent e) {
            Object btn = e.getSource();
            if (btn.toString().contains("Accept")) {
                acceptBtn.setBackground(Color.RED);
            }
            else {
                cancelBtn.setBackground(Color.RED);
                System.out.println("in red cancel");
            }
            System.out.println("In btn");
        }

        @Override
        public void mouseExited(MouseEvent e) {
            Object btn = e.getSource();
            JButton btnObj;
            if (btn == acceptBtn) {
                btnObj = acceptBtn;
            }
            else {
                btnObj = cancelBtn;
            }
            System.out.println("Out btn");
            btnObj.setBackground(Color.WHITE);
        }
    }

    JTextField forenameTextField;
    JTextField surnameTextField;

    JRadioButton maleRadioBtn;
    JRadioButton femaleRadioBtn;

    JSpinner ageSpinner;

    JList<String> animalList;

    JButton acceptBtn;
    JButton cancelBtn;

    Main() {
        this.setSize(300, 300);

        SpringLayout springLayout = new SpringLayout();
        this.setLayout(springLayout);

        // Add Forename Panel.
        Panel forenamePanel = new Panel();
        forenamePanel.setLayout(new BoxLayout(forenamePanel, BoxLayout.X_AXIS));
        JLabel forenameLabel = new JLabel("Forename:");
        forenameTextField = new JTextField(10);
        forenamePanel.add(forenameLabel, BorderLayout.EAST);
        forenamePanel.add(forenameTextField, BorderLayout.WEST);
        this.add(forenamePanel);

        // Add Surname Panel.
        Panel surnamePanel = new Panel();
        surnamePanel.setLayout(new BoxLayout(surnamePanel, BoxLayout.X_AXIS));
        JLabel surnameLabel = new JLabel("Surname:");
        surnameTextField = new JTextField(10);
        surnamePanel.add(surnameLabel, BorderLayout.EAST);
        surnamePanel.add(surnameTextField, BorderLayout.WEST);
        this.add(surnamePanel);
        springLayout.putConstraint(SpringLayout.NORTH, surnamePanel, 0, SpringLayout.SOUTH, forenamePanel);

        // Add radio buttons.
        Panel genderPanel = new Panel();
        genderPanel.setLayout(new BoxLayout(genderPanel, BoxLayout.X_AXIS));
        JLabel genderLabel = new JLabel("Gender:");
        genderPanel.add(genderLabel);
        maleRadioBtn = new JRadioButton("Male");
        genderPanel.add(maleRadioBtn);
        femaleRadioBtn = new JRadioButton("Female");
        genderPanel.add(femaleRadioBtn);
        ButtonGroup genderBtnGroup = new ButtonGroup();
        genderBtnGroup.add(maleRadioBtn);
        genderBtnGroup.add(femaleRadioBtn);
        this.add(genderPanel);
        springLayout.putConstraint(SpringLayout.NORTH, genderPanel, 0, SpringLayout.SOUTH, surnamePanel);

        // Add age chooser.
        Panel agePanel = new Panel();
        agePanel.setLayout(new BoxLayout(agePanel, BoxLayout.X_AXIS));
        JLabel ageLabel = new JLabel("Age:");
        agePanel.add(ageLabel);
        ageSpinner = new JSpinner();
        agePanel.add(ageSpinner);
        this.add(agePanel);
        springLayout.putConstraint(SpringLayout.NORTH, agePanel, 0, SpringLayout.SOUTH, genderPanel);

        // Add animal chooser.
        Panel animalPanel = new Panel();
        BoxLayout animalBoxLayout = new BoxLayout(animalPanel, BoxLayout.Y_AXIS);
        animalPanel.setLayout(animalBoxLayout);
        JLabel animalLabel = new JLabel("Choose animals you carry at home:");
        animalPanel.add(animalLabel);
        String[] animalData = { "Dog", "Cat", "Hamster", "Rabbit", "Spider", "Fish", "Insect", "Boar" };
        animalList = new JList<>(animalData);
        animalList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
        animalList.setLayoutOrientation(JList.VERTICAL_WRAP);
        animalList.setVisibleRowCount(5);
        JScrollPane animalListScroller = new JScrollPane(animalList);
        animalListScroller.setPreferredSize(new Dimension(120, 80));
        animalPanel.add(animalListScroller);
        this.add(animalPanel);
        springLayout.putConstraint(SpringLayout.NORTH, animalPanel, 0, SpringLayout.SOUTH, agePanel);

        // Add submit buttons.
        Panel submitPanel = new Panel();
        submitPanel.setLayout(new BoxLayout(submitPanel, BoxLayout.X_AXIS));
        acceptBtn = new JButton("Accept");
        submitPanel.add(acceptBtn);
        cancelBtn = new JButton("Cancel");
        submitPanel.add(cancelBtn);
        this.add(submitPanel);
        springLayout.putConstraint(SpringLayout.NORTH, submitPanel, 10, SpringLayout.SOUTH, animalPanel);

        // Set not editable.
        maleRadioBtn.setEnabled(false);
        femaleRadioBtn.setEnabled(false);
        ageSpinner.setEnabled(false);
        animalList.setEnabled(false);

        // Add action listener.
        surnameTextField.addActionListener(this);

        // Add item listener.
        maleRadioBtn.addItemListener(this);
        femaleRadioBtn.addItemListener(this);

        // Add change listener.
        ageSpinner.addChangeListener(this);

        // Add accept button listener.
        acceptBtn.addActionListener(e -> {
            StringBuilder messageBuilder = new StringBuilder();

            // Add chosen gender.
            messageBuilder.append("Gender: ");
            if (maleRadioBtn.isSelected()) {
                messageBuilder.append(maleRadioBtn.getText());
            } else if (femaleRadioBtn.isSelected()) {
                messageBuilder.append(femaleRadioBtn.getText());
            }
            messageBuilder.append("\n");

            // Add chosen age.
            messageBuilder.append("Age: ");
            messageBuilder.append(ageSpinner.getValue());
            messageBuilder.append("\n");

            // Add chosen animals.
            messageBuilder.append("Animals :\n");

            for (String animal : animalList.getSelectedValuesList()) {
                messageBuilder.append("- ");
                messageBuilder.append(animal);
                messageBuilder.append("\n");
            }

            JOptionPane.showMessageDialog(this, messageBuilder.toString());
        });

        // Add cancel button listener.
        cancelBtn.addActionListener(e -> {
            JOptionPane.showMessageDialog(this, "Window will be closed.");
            System.exit(0);
        });

        // Add mouse listeners.
        MyMouseAdapter adapter = new MyMouseAdapter();
        acceptBtn.addMouseListener(adapter);
        cancelBtn.addMouseListener(adapter);
    }

    public static void main(String[] args) {
        Main window = new Main();

        int option = JOptionPane.showConfirmDialog(window, "Do you want tak a part in the query?", "Welcome", JOptionPane.OK_CANCEL_OPTION);
        if (option == 0) {
            window.setVisible(true);
        } else {
            System.exit(0);
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (forenameTextField.getText().equals("") || surnameTextField.getText().equals("")) {
            JOptionPane.showMessageDialog(this, "Forename and Surname cannot be blank!");
        } else {
            maleRadioBtn.setEnabled(true);
            femaleRadioBtn.setEnabled(true);
        }
    }

    @Override
    public void itemStateChanged(ItemEvent e) {
        ageSpinner.setEnabled(true);
    }

    @Override
    public void stateChanged(ChangeEvent e) {
        animalList.setEnabled(true);
    }
}
