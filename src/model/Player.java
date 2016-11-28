package model;

public enum Player {
	FIRST,
	SECOND;

	public Player opponent() {
		return this == FIRST ? SECOND : FIRST;
	}
}
