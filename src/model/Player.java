package model;

public enum Player {
	AI,
	HUMAN;

	public Player opponent() {
		return this == AI ? HUMAN : AI;
	}
}
