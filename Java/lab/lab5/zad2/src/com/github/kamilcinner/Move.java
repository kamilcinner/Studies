package com.github.kamilcinner;

public class Move {
    private Gamer gamer;
    private int x;
    private int y;

    public Move(Gamer gamer, int x, int y) {
        this.gamer = gamer;
        this.x = x;
        this.y = y;
    }

    public Gamer getGamer() {
        return gamer;
    }

    public void setGamer(Gamer gamer) {
        this.gamer = gamer;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }
}
