package com.github.kamilcinner;

import javax.swing.*;
import javax.swing.border.Border;
import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;

public class Main extends JFrame {

    Main() {
        // Set main window layout.
        SpringLayout springLayout = new SpringLayout();
        this.getContentPane().setLayout(springLayout);
        this.setSize(300, 300);

        // Add editor pane.
        JEditorPane editorPane = new JEditorPane();
        editorPane.setPreferredSize(new Dimension(300, 100));
        this.add(editorPane);
        springLayout.putConstraint(SpringLayout.NORTH, editorPane, 0, SpringLayout.NORTH, this);

        // Add text area.
        JTextArea textArea = new JTextArea();
        textArea.setPreferredSize(new Dimension(300, 50));
        this.add(textArea);
        springLayout.putConstraint(SpringLayout.NORTH, textArea, 10, SpringLayout.SOUTH, editorPane);

        // Add bottom panel.
        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout());
        panel.setPreferredSize(new Dimension(300, 25));

        JTextField textField = new JTextField();
        panel.add(textField, BorderLayout.WEST);
        textField.setPreferredSize(new Dimension(150, 25));

        JButton btn = new JButton("Send");
        panel.add(btn, BorderLayout.EAST);

        this.add(panel);
        springLayout.putConstraint(SpringLayout.NORTH, panel, 10, SpringLayout.SOUTH, textArea);

        // Add btn listener.
        btn.addActionListener(event -> {
            try {
                URL url = new URL(textField.getText());

                editorPane.setPage(url);

                BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(url.openStream()));
                String line;
                while ((line = bufferedReader.readLine()) != null) {
                    textArea.append(line);
                }
                bufferedReader.close();

            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }

    public static void main(String[] args) {
        Main window = new Main();
        window.setVisible(true);
    }
}
