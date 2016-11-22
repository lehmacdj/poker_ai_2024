package model;

public class Game {
	private Player next;
	private State state;

	public Game() {
		next = Player.HUMAN;
	}

	public Player nextPlayer() {
		return next;
	}

	public State getState() {
		return state;
	}

	public void makeMove(Move m) {
		state.update(next, m);
	}
}
