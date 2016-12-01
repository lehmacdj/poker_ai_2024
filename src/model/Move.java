package model;

public class Move {
	public final Type TYPE;
	public final int AMOUNT;

	public enum Type {
		BID,
		FOLD;
	}

	private Move() {
		TYPE = Type.FOLD;
		AMOUNT = -1;
	}

	private Move(int amount) {
		TYPE = Type.BID;
		AMOUNT = amount;
	}

	public static Move makeBid(int amount) {
		return new Move(amount);
	}

	public static Move makeFold() {
		return new Move();
	}
}
