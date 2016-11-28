import model.*;

public class BoardPrinter implements GameListener {
	public void printStack(Player p, State s) {
	}

	public void printBid(Player p, State s) {
	}

	public void printDeck(Player p, State s) {
	}

	public void printHand(Player p, State s) {
	}

	@Override
	public void gameChanged(Game g) {
		System.out.println("To play: " + g.nextPlayer());
	}
}
