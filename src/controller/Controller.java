package controller;

import model.*;

public abstract class Controller implements GameListener {
	private final Player player;

	protected Controller(Player p) {
		player = p;
	}

	public abstract Move nextMove(State s);

	public void gameChanged(Game g) {
		if (g.nextPlayer() == this.player) {
			g.makeMove(nextMove(g.getState()));
		}
	}
}
