package controller;

/**
 * The c++ jni interface for the AI.
 */

import model.*;

public class PokerAI extends Controller {
	public PokerAI(Player p) {
		super(p);
	}

	public Move nextMove(State s) {
		Player dealer = s.getDealer();
		boolean isDealer = player.equals(dealer);
		double nextMove = nativeNextMove(
			isDealer,
			s.getPot(),
			new double[]{s.getStack(dealer), s.getStack(dealer.opponent())},
			s.getAmountToCall(),
			s.getNativeHand(player),
			s.getNativeBoard()
		);
		if (nextMove < 0) {
			return Move.makeFold();
		} else {
			return Move.makeBid(nextMove);
		}
	}

	public static native int nativeNextMove(
		boolean isDealer,
		double pot,
		double[] stacks,
		double minimumBidToCall,
		long[] hand,
		long[] board
	);

	static {
		System.loadLibrary("PokerLib");
	}
}
