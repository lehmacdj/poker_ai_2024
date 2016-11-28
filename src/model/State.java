package model;

public class State {
	private Hand ai;
	private Hand human;
	private Deck deck;
	private int aiBid;
	private int humanBid;
	private int aiChips;
	private int humanChips;

	/* package */ State() {
		Deck d = new Deck();
		human = new Hand(d);
		ai = new Hand(d);
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
		return p == Player.AI ? ai.copy() : human.copy();
	}

	/** return the bid for [p] */
	public int getBid(Player p) {
		return p == Player.AI ? aiBid : humanBid;
	}

	public int getChips(Player p) {
		return p == Player.AI ? aiChips : humanChips;
	}
}
