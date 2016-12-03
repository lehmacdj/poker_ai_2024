package model;

public enum Player {
	FIRST,
	SECOND,
	NONE;

	public Player opponent() {
		return this == FIRST ? SECOND : FIRST;
	}
}
