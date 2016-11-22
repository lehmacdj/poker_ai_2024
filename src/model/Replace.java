package model;

import java.util.List;

public class Replace extends Move {
	List<Integer> indexes;

	public Replace(List<Integer> indexes) {
		this.indexes = indexes;
	}

	public List<Integer> getIndexes() {
		return indexes;
	}
}
