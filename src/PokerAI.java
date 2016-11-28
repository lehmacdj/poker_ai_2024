/**
 * The c++ jni interface for the AI.
 */

import model.*;

public class PokerAI extends Controller {
	public PokerAI(Player p) {
		super(p);
	}

	public native Move nextMove(State s);
}
