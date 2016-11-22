package model;

import java.util.LinkedList;
import java.util.Collections;

public class Deck {
	private LinkedList<Card> deck;

	public Deck() {
		for (Card.Rank r : Card.Rank.values()) {
			for (Card.Suit s : Card.Suit.values()) {
				deck.add(new Card(r, s));
			}
		}
		Collections.shuffle(deck);
	}

	public Card deal() {
		return deck.poll();
	}
}
