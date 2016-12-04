package model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.Stream;

import model.Move.Type;

public class State {
	// the player that is currently the dealer
	private Player dealer;

	// the next player
	private Player next;

	// the deck
	private Deck deck;

	// the board (only contains the revealed cards)
	private List<Card> board;

	// player hands
	private List<Card> player1Hand;
	private List<Card> player2Hand;

	// money that players have and the pot
	private double player1Stack;
	private double player2Stack;
	private double pot;

	// the game status
	public enum Status { PREFLOP, FLOP, TURN, RIVER, ROUND_OVER, HAS_WINNER }
	private Status status;
	private Player winner;

	// bidding state
	private double minimumRaise;
	private double amountToCall;

	/** Create a new State */
	/*package*/ State() {
		// setup permanent board state
		player1Stack = INITIAL_STACK;
		player2Stack = INITIAL_STACK;
		pot = 0;
		winner = null;
		dealer = Player.FIRST;

		setupRound();
	}

	/** Sets up a round with [dealer] */
	private void setupRound() {
		deck = new Deck();
		dealHands();
		board = new ArrayList<>();
		status = Status.PREFLOP;
		next = dealer;
		minimumRaise = INITIAL_MIN_RAISE;
		amountToCall = 5;
		commitBidFor(dealer, SMALL_BLIND);
		commitBidFor(dealer.opponent(), BIG_BLIND);
	}

	/** Creates a hand using cards from [deck] */
	private void dealHands() {
		List<Card> dealerHand = new ArrayList<>();
		List<Card> otherHand = new ArrayList<>();
		for (int i = 0; i < 2; i++) {
			dealerHand.add(deck.deal());
			otherHand.add(deck.deal());
		}
		if (dealer.equals(Player.FIRST)) {
			player1Hand = dealerHand;
			player2Hand = otherHand;
		} else {
			player1Hand = otherHand;
			player2Hand = dealerHand;
		}
	}

	/** Reveals a card on the board */
	private void reveal() {
		board.add(deck.deal());
	}

	/** Update the cards in the state with a move */
	/* package */ void update(Move m) {
		double stack = getStack(next);
		if (m.TYPE.equals(Type.BID)) {
			double amount = Math.min(stack, m.AMOUNT);

			// TODO: handle the case where player calling is ALL IN
			if (amount == amountToCall) { // call
				commitBidFor(next, amount);
				if (currentPlayerActsLast()) {// round end
					advanceStateAfterCall();
					updatePotForWinner(playerWithWinningHand());
				}
			} else if (amount - amountToCall >= minimumRaise &&
					amountToCall + amount <= getStack(next.opponent())) { // raise
				minimumRaise = amount - amountToCall;
				commitBidFor(next, amount);
			} else {
				throw new RuntimeException("Invalid bid (" + amount + ") " +
						"(either didn't raise enough, " +
						"didn't put in enough money to call, " +
						"or bid more money than the opponent could add)");
			}

		} else if (m.TYPE.equals(Type.FOLD)) {
			// give money to person who didn't fold
			status = Status.ROUND_OVER;
			updatePotForWinner(next.opponent());
		}

		next = next.opponent();

		if (status.equals(Status.ROUND_OVER)) {
			handleRoundEnd();
		}
	}

	public void commitBidFor(Player p, double amount) {
		pot += amount;
		// remove gold from current players stack
		if (p.equals(Player.FIRST)) {
			player1Stack -= amount;
		} else {
			player2Stack -= amount;
		}
	}

	/** Handle the end of a round */
	public void handleRoundEnd() {
		// check winner
		if (player1Stack < 5.) {
			status = Status.HAS_WINNER;
			winner = Player.SECOND;
		} else if (player2Stack < 5.) {
			status = Status.HAS_WINNER;
			winner = Player.FIRST;
		} else {
			setupRound();
		}
	}

	/** Update the state after a player calls */
	public void advanceStateAfterCall() {
		switch (status) {
			case PREFLOP:
				status = Status.FLOP;
				for (int i = 0; i < 3; i++) { reveal(); }
				return;
			case FLOP:
				status = Status.TURN;
				reveal();
				return;
			case TURN:
				status = Status.RIVER;
				reveal();
				return;
			case RIVER:
				status = Status.ROUND_OVER;
				return;
			case ROUND_OVER:
			case HAS_WINNER:
				throw new RuntimeException("Invalid state while advancing state after draw");
		}
	}

	/** Update the pot and players stacks for winning player p. p is nonnull */
	private void updatePotForWinner(Player p) {
		if (p.equals(Player.FIRST)) {// player 1 wins the pot
			player1Stack += pot;
		} else if (p.equals(Player.SECOND)) {// player 2 wins the pot
			player2Stack += pot;
		} else {// split the pot
			player1Stack += pot / 2.;
			player2Stack += pot / 2.;
		}
		pot = 0;
	}

	private boolean currentPlayerActsLast() {
		switch (status) {
			case PREFLOP:
				if (next.equals(dealer)) {
					return true;
				}
				break;
			case FLOP:
			case TURN:
			case RIVER:
				if (! next.equals(dealer)) {
					return true;
				}
				break;
			case ROUND_OVER:
			case HAS_WINNER:
				throw new RuntimeException("Invalid state for call to currentPlayerActsLast");
		}
		return false;
	}

	/** Return the person winning the board */
	// private native Player playerWithWinningHand();
	private Player playerWithWinningHand() {
		int winner = winningHand(
			getNativeHand(dealer),
			getNativeHand(dealer.opponent()),
			getNativeBoard()
		);
		if (winner == 0) {
			return Player.NONE;
		} else if (winner == 1) {
			return dealer;
		} else {
			return dealer.opponent();
		}
	}

	private static native int winningHand(
		long[] hand1,
		long[] hand2,
		long[] board
	);

	static {
		System.loadLibrary("Poker");
	}

	/** returns a Hand for [p] that is not backed by the state */
	public List<Card> getHand(Player p) {
		List<Card> hand = p == Player.FIRST ? player1Hand : player2Hand;
		return Collections.unmodifiableList(hand);
	}

	/** return the bid for [p] */
	public double getPot() {
		return pot;
	}

	public double getMinimumRaise() {
		return minimumRaise;
	}

	public double getAmountToCall() {
		return amountToCall;
	}

	/** Get the stack size for [p] */
	public double getStack(Player p) {
		return p == Player.FIRST ? player1Stack : player2Stack;
	}

	/** Get the status */
	public Status getStatus() {
		return status;
	}

	public Player getDealer() {
		return dealer;
	}

	public List<Card> getBoard() {
		return Collections.unmodifiableList(board);
	}

	/** Returns the winner, or null if there is none */
	public Player getWinner() {
		return winner;
	}

	/*package*/ Player nextPlayer() {
		return next;
	}

	public long[] getNativeHand(Player p) {
		List<Card> hand = getHand(p);
		return new long[]{hand.get(0).toLong(), hand.get(1).toLong()};
	}

	public long[] getNativeBoard() {
		return Stream.concat(
			board.stream()
				.map(e -> e.toLong()),
			Stream.generate(() -> 0L))
			.mapToLong(e -> e)
			.limit(5)
			.toArray();
	}

	// static

	// the amount of money that players start with
	final static double INITIAL_STACK = 1000.;
	final static double SMALL_BLIND = 5.;
	final static double BIG_BLIND = 10.;
	final static double INITIAL_MIN_RAISE = BIG_BLIND;
}
