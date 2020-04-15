package com.github.kamilcinner;

import java.util.ArrayList;

public class Board implements Printable {

    @Override
    public void print(ArrayList<Move> moves) {
        char[][] board = new char[3][3];
        // Initialize board with dots.
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '.';
            }
        }
        // Add players moves to the board.
        for (Move move : moves) {
            board[move.getX()][move.getY()] = move.getGamer().getSign();
        }
        // Print board to console.
        for (int i = 0; i < 3; i++) {
            Helpers.print(""+board[i][0] + board[i][1] + board[i][2]);
        }
    }
}
