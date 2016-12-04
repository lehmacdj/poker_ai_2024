package tui;

import model.Move;
import model.Player;
import model.State;

public class PokerAI extends Controller {
	public PokerAI(Player p) {
		super(p);
	}

	public Move nextMove(State s) {
		Player dealer = s.getDealer();
		boolean isDealer = player.equals(dealer);
		long[] nativeHand = s.getNativeHand(player);
		long[] nativeBoard = s.getNativeBoard();
		System.out.printf("%b, %.1f, [%.1f, %.1f], %.1f, [%x, %x], [%x, %x, %x, %x, %x]\n",
			isDealer,
			s.getPot(),
			s.getStack(dealer),
			s.getStack(dealer.opponent()),
			s.getAmountToCall(),
			nativeHand[0], nativeHand[1],
			nativeBoard[0], nativeBoard[1], nativeBoard[2], nativeBoard[3], nativeBoard[4]);
		double nextMove = nativeNextMove(
			isDealer,
			s.getPot(),
			new double[]{s.getStack(dealer), s.getStack(dealer.opponent())},
			s.getAmountToCall(),
			nativeHand,
			nativeBoard
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
		System.loadLibrary("Poker");
	}
}
