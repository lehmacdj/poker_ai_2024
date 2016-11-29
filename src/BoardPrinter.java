import model.*;

/**
 * Prints a board with the following configuration.
 * To play: PLAYER
 * Cards Left: DECK_SIZE
 *
 * Player 1 (BID)
 * Chips: CHIPS
 * Hand:
 * HAND_CARDS
 *
 * Player 2 (BID)
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
		System.out.println("To play: " + g.nextPlayer());
	}
}
