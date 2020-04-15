package com.github.kamilcinner;

import java.util.ArrayList;

public class Commentator implements Printable {

    @Override
    public void print(ArrayList<Move> moves) {
        Move lastMove = moves.get(moves.size()-1);
        Gamer gamer = lastMove.getGamer();

        String name = gamer.getName();
        char sign = gamer.getSign();
        int x = lastMove.getX();
        int y = lastMove.getY();

        Helpers.print("Player "+name+" put sign '"+sign+"' on field ("+x+", "+y+").");
    }
}
