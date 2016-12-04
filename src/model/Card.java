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
		return "" + rank + suit;
	}

	public Rank getRank() {
		return rank;
	}

	public Suit getSuit() {
		return suit;
	}

	public enum Suit {
		SPADE(3),
		HEART(2),
		DIAMOND(1),
		CLUB(0);

		int num;

		private Suit(int i) {
			num = i;
		}

		public int toInt() {
			return num;
		}

		@Override
		public String toString() {
			switch(this) {
			case SPADE:
				return "\u2660";
			case HEART:
				return "\u2665";
			case DIAMOND:
				return "\u2666";
			case CLUB:
				return "\u2663";
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
				return "A";
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
				return "J";
			case QUEEN:
				return "Q";
			case KING:
				return "K";
			default:
				throw new RuntimeException("impossible case");
			}
		}

		int toInt() {
			return number;
		}
	}

	public long toLong() {
		return ((long)rank.toInt() << 32) | (long)suit.toInt();
	}
}
