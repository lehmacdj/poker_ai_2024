package tui;

import model.Game;
import model.GameListener;
import model.Move;
import model.Player;
import model.State;
import model.State.Status;

public abstract class Controller implements GameListener {
	protected final Player player;

	protected Controller(Player p) {
		player = p;
	}

	public abstract Move nextMove(State s);

	public void gameChanged(Game g) {
		if (! g.getState().getStatus().equals(Status.HAS_WINNER) &&
			! g.getState().getStatus().equals(Status.ROUND_OVER)) {
			if (g.nextPlayer() == this.player) {
				g.makeMove(nextMove(g.getState()));
			}
		}
	}
}
