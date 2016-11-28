package model;

public class State {
	private Hand first;
	private Hand second;
	private Deck deck;
	private int firstBid;
	private int secondBid;
	private int firstChips;
	private int secondChips;

	/* package */ State() {
		Deck d = new Deck();
		first = new Hand(d);
		second = new Hand(d);
	}

	/** Update the cards in the state with a move */
	/* package */ void update(Player p, Move m) {
		Hand current = getPlayer(p);
		if (m instanceof Replace) {
			current.replace(deck, ((Replace)m).getIndexes());
		} else {
			throw new RuntimeException("Invalid move type: " + m.getClass().toString());
		}
	}

	/** returns a Hand for [p] that is not backed by the state */
	public Hand getPlayer(Player p) {
		return p == Player.FIRST ? first.copy() : second.copy();
	}

	/** return the bid for [p] */
	public int getBid(Player p) {
		return p == Player.FIRST ? firstBid : secondBid;
	}

	public int getChips(Player p) {
		return p == Player.FIRST ? firstChips : secondChips;
	}
}
