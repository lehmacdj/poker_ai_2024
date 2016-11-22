package model;

import java.util.LinkedList;
import java.util.List;

public class Hand {
	public List<Card> hand;
	public Hand(Deck d) {
		for (int i = 0; i < 5; i++) {
			hand.add(d.deal());
		}
	}

	/** Construct a hand with [cards] */
	private Hand(List<Card> cards) {
		hand = cards;
	}

	public void replace(Deck d, List<Integer> indexes) {
		for (int i : indexes) {
			hand.remove(i);
			hand.add(d.deal());
		}
	}

	public Hand copy() {
		List<Card> copy = new LinkedList<>(hand);
		return new Hand(copy);
	}
}
