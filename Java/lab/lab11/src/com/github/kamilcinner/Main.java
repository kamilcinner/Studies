package com.github.kamilcinner;

import javax.swing.*;
import java.awt.*;
import java.io.*;

public class Main extends JFrame {

    Main() {
        // Set main window layout.
//        this.getContentPane().setLayout(new BoxLayout(this.getContentPane(), BoxLayout.Y_AXIS));
        SpringLayout springLayout = new SpringLayout();
        this.getContentPane().setLayout(springLayout);
        this.setSize(300, 300);

        // Add editor pane.
        JEditorPane editorPane = new JEditorPane();
        editorPane.setPreferredSize(new Dimension(300, 220));
        this.add(editorPane);
        springLayout.putConstraint(SpringLayout.NORTH, editorPane, 0, SpringLayout.NORTH, this);

        // Add buttons.
        JPanel panel = new JPanel();
        panel.setPreferredSize(new Dimension(300, 25));
        panel.setLayout(new BorderLayout());
        JButton openBtn = new JButton("Open");
        panel.add(openBtn, BorderLayout.WEST);
        JButton saveBtn = new JButton("Save");
        panel.add(saveBtn, BorderLayout.EAST);
        this.add(panel);
        springLayout.putConstraint(SpringLayout.NORTH, panel, 20, SpringLayout.SOUTH, editorPane);

        // Add button listeners.
        openBtn.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser();
            if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
                File file = fileChooser.getSelectedFile();
                String path = file.getAbsolutePath();
                String line;
                StringBuilder textBuilder = new StringBuilder();
                BufferedReader bufferedReader;
                try {
                    bufferedReader = new BufferedReader(new FileReader(path));

                    while ((line = bufferedReader.readLine()) != null) {
                        textBuilder.append(line);
                        textBuilder.append("\n");
                    }

                    // Add loaded text to editor.
                    editorPane.setText(textBuilder.toString());

                } catch (IOException fileNotFoundException) {
                    fileNotFoundException.printStackTrace();
                }
            }
        });

        saveBtn.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser();
            if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
                File file = fileChooser.getSelectedFile();
                String path = file.getAbsolutePath();

                try {
                    BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(path));
                    bufferedWriter.write(editorPane.getText());
                    bufferedWriter.close();

                } catch (IOException ioException) {
                    ioException.printStackTrace();
                }
            }
        });
    }

    public static void main(String[] args) {
	    Main window = new Main();
	    window.setVisible(true);
    }
}
