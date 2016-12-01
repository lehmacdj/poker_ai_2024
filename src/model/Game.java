package model;

import java.util.ArrayList;

public class Game {
	private State state;
	private ArrayList<GameListener> gameListeners;

	public Game() {
		gameListeners = new ArrayList<>();
	}

	public Player nextPlayer() {
		return state.nextPlayer();
	}

	public State getState() {
		return state;
	}

	public void makeMove(Move m) {
		state.update(m);

		for (GameListener gl : gameListeners) {
			gl.gameChanged(this);
		}
	}

	public void addListener(GameListener gl) {
		gameListeners.add(gl);
	}

	public void start() {
		for (GameListener gl : gameListeners) {
			gl.gameChanged(this);
		}
	}
}
