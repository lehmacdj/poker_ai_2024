package tui;

import model.*;

/**
 * Prints a board with the following configuration.
 * To play: PLAYER
 * Board: BOARD
 * Pot: POT
 *
 * NEXT_PLAYER (BID)
 * Chips: CHIPS
 * Hand:
 * HAND_CARDS
 *
 * LAST_PLAYER (BID)
 * Chips: CHIPS
 * Hand:
 * HAND_CARDS
 */
public class BoardPrinter implements GameListener {
	public void printPlayer(Player p, State s) {
		System.out.println(p + " (" + s.getBid(p) + ")");
		System.out.println("Chips: " + s.getChips(p));
		System.out.println("Hand:");
		for (Card c : s.getHand(p).hand) {
			System.out.println("    " + c);
		}
	}

	@Override
	public void gameChanged(Game g) {
		State s = g.getState();
		Player next = g.nextPlayer();
		System.out.println("Board: " + s);
		System.out.println("Pot: " + s);
		System.out.println();
		printPlayer(next, s);
		System.out.println();
		printPlayer(next.opponent(), s);
	}
}
