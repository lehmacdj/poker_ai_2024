/**
 * The c++ jni interface for the AI.
 */

import model.*;

public class PokerAI {
	public native Move nextMove(State s);
}
