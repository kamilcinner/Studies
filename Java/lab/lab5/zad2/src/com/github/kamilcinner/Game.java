package com.github.kamilcinner;

import java.util.ArrayList;
import java.util.Scanner;

public class Game {
    private Gamer gamerO;
    private Gamer gamerX;
    private ArrayList<Move> moves = new ArrayList<>();
    private Board board = new Board();
    private Commentator commentator = new Commentator();

    // Static method for easier printing.
    private static <T> void print(T arg) {
        Helpers.print(arg);
    }

    // Check if the given coordinates are not already taken in the board.
    private boolean isBoardFieldAvailable(int x, int y) {
        for (Move move : moves) {
            if (move.getX() == x && move.getY() == y) {
                return false;
            }
        }
        return true;
    }

    // Get coordinates from console input and validate them.
    private int[] getCoordinates() {
        // Create new scanner to get input form console.
        Scanner scanner = new Scanner(System.in);

        // Initialize coordinates with defaults for stability.
        int x = 0;
        int y = 0;

        boolean correctValue;
        do {
            // Assume that user will give correct values and if no repeat loop.
            correctValue = true;

            // Validate x value.
            print("Enter x:");
            x = scanner.nextInt();
            if (x < 0 || x > 2) {
                correctValue = false;
                print("Given x must me in [0, 2]!");
                continue;
            }

            // Validate y value;
            print("Enter y:");
            y = scanner.nextInt();
            if (y < 0 || y > 2) {
                correctValue = false;
                print("Given y must me in [0, 2]!");
                continue;
            }

            // Check if given coordinates are available.
            if (!isBoardFieldAvailable(x, y)) {
                correctValue = false;
                print("Given coordinates are already taken!");
            }
        } while (!correctValue);

        return new int[]{x, y};
    }

    // Check if the current board state describes a winner.
    boolean checkWinner() {
        char[][] boardFields = new char[3][3];
        // Initialize winner as 'space'.
        // Space means that there is no winner.
        char winner = ' ';

        // Initialize boardFields with spaces.
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                boardFields[i][j] = ' ';
            }
        }

        // Add players moves to the boardFields.
        for (Move move : moves) {
            boardFields[move.getX()][move.getY()] = move.getGamer().getSign();
        }

        // Check horizontally.
        for (int i = 0; i < 3; i++) {
            winner = boardFields[i][0];
            for (int j = 1; j < 3; j++) {
                if (winner != boardFields[i][j]) {
                    winner = ' ';
                    break;
                }
            }
            if (winner != ' ') break;
        }

        // Check vertically.
        if (winner == ' ') {
            for (int i = 0; i < 3; i++) {
                winner = boardFields[0][i];
                for (int j = 1; j < 3; j++) {
                    if (winner != boardFields[j][i]) {
                        winner = ' ';
                        break;
                    }
                }
                if (winner != ' ') break;
            }
        }

        // Check left bottom - right top.
        if (winner == ' ') {
            winner = boardFields[0][2];
            if (winner != boardFields[1][1] || winner != boardFields[2][0]) {
                winner = ' ';
            }
        }

        // Check left top - right bottom.
        if (winner == ' ') {
            winner = boardFields[0][0];
            if (winner != boardFields[1][1] || winner != boardFields[2][2]) {
                winner = ' ';
            }
        }

        // Check if there is a winner and print proper output to console.
        if (winner == 'O') {
            print(gamerO.getName() + " wins!");
            return true;
        } else if (winner == 'X') {
            print(gamerX.getName() + " wins!");
            return true;
        }

        // Return false if there is no winner yet.
        return false;
    }

    public static void main(String[] args) {
        // Create a game.
        Game game = new Game();
        // Assign run boolean true to start a game.
        boolean run = true;

        // Create scanner to get input form console.
        Scanner scanner = new Scanner(System.in);

        // Get Players names from console.
        print("Give 'O' Player name:");
        game.gamerO = new Gamer(scanner.next(), 'O');

        print("Give 'X' Player name:");
        game.gamerX = new Gamer(scanner.next(), 'X');

        // Define which Player has the move (O or X).
        boolean moveO = true;

        // Define max number of moves in the board.
        // Because our board is 3x3 there is max 9 moves.
        int movesCount = 0;

        // Define Player given coords to put a sign O or X.
        int[] coords;

        // Main Game loop.
        while (run) {
            // Increase count of moves as game flows.
            movesCount++;

            // Get coordinates for next move form Player.
            coords = game.getCoordinates();

            // Add new move assigned to proper Player.
            if (moveO) {
                game.moves.add(new Move(game.gamerO, coords[0], coords[1]));
            } else {
                game.moves.add(new Move(game.gamerX, coords[0], coords[1]));
            }

            // Print commentator formula.
            game.commentator.print(game.moves);

            // Print board.
            game.board.print(game.moves);

            // Change next move to opposite Player.
            moveO = !moveO;

            // Check if there is a winner already and if so stop the Game.
            if (game.checkWinner()) {
                run = false;
            }

            // If there is no winner and the Game reached max number of moves stop the Game
            // and print proper message.
            if (run && movesCount == 9) {
                run = false;
                print("Tie!");
            }
        }
    }
}
