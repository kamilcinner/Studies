package com.github.kamilcinner;

import javax.swing.*;
import java.awt.*;

public class Main extends JFrame {

    Main(String title) {
        super(title);

        // Panel p1.
        JPanel p1 = new JPanel();
        p1.setLayout(new BoxLayout(p1, BoxLayout.PAGE_AXIS));
        JButton[] buttons = new JButton[5];
        for (JButton btn : buttons) {
            btn = new JButton("Text");
            p1.add(btn);
        }
        p1.setBackground(Color.LIGHT_GRAY);
        p1.setBorder(javax.swing.BorderFactory.createTitledBorder("Options"));
        this.add(p1, BorderLayout.WEST);

        // Panel p2. (Form)
//        JPanel p2 = new JPanel();
//        p2.setLayout(new GridLayout(5,2));
//        for (int i = 0; i < 10; i++) {
//            if (i % 2 == 0) {
//                p2.add(new JLabel("Position " + i + ": ", JLabel.RIGHT));
//            } else {
//                p2.add(new JTextField(20));
//            }
//        }
//        p2.setBackground(Color.CYAN);
//        p2.setBorder(javax.swing.BorderFactory.createTitledBorder("Form"));
//        this.add(p2, BorderLayout.EAST);

        // Panel p3.
        JPanel p3 =  new JPanel(new FlowLayout(FlowLayout.RIGHT));
        p3.add(new JButton("Ok"));
        p3.setBackground(Color.GREEN);
        this.add(p3, BorderLayout.SOUTH);

        // Panel p4.
        String[] tableHeaders = { "Sing.", "Forename", "Surname" };
        String[][] names = {
                { "Kornelia", "Authguard" },
                { "Magda", "Braweheart" },
                { "Gosia", "Miseryiort" },
                { "Kamil", "Cinner" },
                { "Ubuntu", "Kernel" }
        };
        Object[][] tableModel = new Object[5][3];
        for (int i = 0; i < 5; i++) {
            tableModel[i][0] = i + 1;
            tableModel[i][1] = names[i][0];
            tableModel[i][2] = names[i][1];
        }
        JTable table = new JTable(tableModel, tableHeaders);
        JScrollPane p4 = new JScrollPane(table);
        this.add(p4, BorderLayout.CENTER);

        // Menu.
        JMenuBar menuBar = new JMenuBar();
        JMenu fileMenu = new JMenu("File");
        fileMenu.add(new JMenuItem("Action 1"));
        fileMenu.add(new JMenuItem("Action 2"));
        fileMenu.add(new JMenuItem("Action 3"));
        menuBar.add(fileMenu);
        JMenu editMenu = new JMenu("Edit");
        editMenu.add(new JMenuItem("Action 1"));
        editMenu.add(new JMenuItem("Action 2"));
        editMenu.add(new JMenuItem("Action 3"));
        menuBar.add(editMenu);
        this.setJMenuBar(menuBar);

        // Form formatter.
        int numPairs = 10;
        String[] labels = new String[numPairs];
        for (int i = 0; i < numPairs; i++) {
            labels[i] = "Position " + i + ":";
        }
        JPanel form = new JPanel(new SpringLayout());
        for (int i = 0; i < numPairs; i++) {
            JLabel l = new JLabel(labels[i], JLabel.TRAILING);
            form.add(l);
            JTextField textField = new JTextField(10);
            l.setLabelFor(textField);
            form.add(textField);
        }
        this.add(form, BorderLayout.EAST);

        //Lay out the panel.
        SpringUtilities.makeCompactGrid(form,
                numPairs, 2, //rows, cols
                6, 6, //initX, initY
                6, 6); //xPad, yPad

        this.pack();
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            Main window = new Main(args[0]);
        }
    }
}
