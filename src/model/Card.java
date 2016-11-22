package model;

public class Card {
	private Suit suit;
	private Rank rank;

	public Card(Rank r, Suit s) {
		suit = s;
		rank = r;
	}

	@Override
	public String toString() {
		return rank + " of " + suit + "s";
	}

	public Rank getRank() {
		return rank;
	}

	public Suit getSuit() {
		return suit;
	}

	public enum Suit {
		SPADE,
		HEART,
		DIAMOND,
		CLUB;

		@Override
		public String toString() {
			switch(this) {
			case SPADE:
				return "Spade";
			case HEART:
				return "Heart";
			case DIAMOND:
				return "Diamond";
			case CLUB:
				return "Club";
			default:
				throw new RuntimeException("impossible situation");
			}
		}
	}

	public enum Rank implements Comparable<Rank> {
		TWO(2),
		THREE(3),
		FOUR(4),
		FIVE(5),
		SIX(6),
		SEVEN(7),
		EIGHT(8),
		NINE(9),
		TEN(10),
		JACK(11),
		QUEEN(12),
		KING(13),
		ACE(14);

		private Rank(int n) {
			number = n;
		}

		int number;

		@Override
		public String toString() {
			switch (this) {
			case ACE:
				return "Ace";
			case TWO:
			case THREE:
			case FOUR:
			case FIVE:
			case SIX:
			case SEVEN:
			case EIGHT:
			case NINE:
			case TEN:
				return Integer.toString(number);
			case JACK:
				return "Jack";
			case QUEEN:
				return "Queen";
			case KING:
				return "King";
			default:
				throw new RuntimeException("impossible case");
			}
		}
	}
}
