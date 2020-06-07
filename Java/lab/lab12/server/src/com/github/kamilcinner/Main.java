package com.github.kamilcinner;

import javax.swing.*;
import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.URL;

public class Main extends JFrame {

    ServerSocket serverSocket;
    JTextArea textArea;

    Main() throws IOException {
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
                getDataFromClient();
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        serverSocket = new ServerSocket(8080);
        textArea.setText("Server started!");
    }

    void getDataFromClient() throws IOException {
        Socket socket = serverSocket.accept();
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        String line;
        textArea.setText("");
        while ((line = bufferedReader.readLine()) != null) {
            textArea.append(line);
        }
    }

    public static void main(String[] args) throws IOException {
        Main window = new Main();
        window.setVisible(true);

        window.getDataFromClient();
    }
}
