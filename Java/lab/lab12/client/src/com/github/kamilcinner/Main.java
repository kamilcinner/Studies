package com.github.kamilcinner;

import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.net.*;

public class Main extends JFrame {

    Socket socket;
    JTextArea textArea;
    JEditorPane editorPane;

    Main() throws IOException {
        // Set main window layout.
        SpringLayout springLayout = new SpringLayout();
        this.getContentPane().setLayout(springLayout);
        this.setSize(300, 300);

        // Add editor pane.
        editorPane = new JEditorPane();
        editorPane.setPreferredSize(new Dimension(300, 100));
        this.add(editorPane);
        springLayout.putConstraint(SpringLayout.NORTH, editorPane, 0, SpringLayout.NORTH, this);

        // Add text area.
        textArea = new JTextArea();
        textArea.setPreferredSize(new Dimension(300, 50));
        this.add(textArea);
        springLayout.putConstraint(SpringLayout.NORTH, textArea, 10, SpringLayout.SOUTH, editorPane);

        // Add bottom panel.
        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout());
        panel.setPreferredSize(new Dimension(300, 25));

        JTextField textField = new JTextField();
        panel.add(textField, BorderLayout.WEST);
        textField.setEnabled(false);
        textField.setPreferredSize(new Dimension(150, 25));

        JButton btn = new JButton("Send");
        panel.add(btn, BorderLayout.EAST);

        this.add(panel);
        springLayout.putConstraint(SpringLayout.NORTH, panel, 10, SpringLayout.SOUTH, textArea);

        // Add btn listener.
        btn.addActionListener(event -> {
            try {
                sendDataToServer();
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        InetAddress inetAddress = InetAddress.getByName("localhost");
        socket = new Socket(inetAddress, 8080);
        textArea.setText("Connected to the server!");
    }

    void sendDataToServer() throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        bufferedWriter.write(editorPane.getText() + "\n");
        bufferedWriter.close();
    }

    public static void main(String[] args) throws IOException {
        Main window = new Main();
        window.setVisible(true);
    }
}
