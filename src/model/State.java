package model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

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
	private int player1Stack;
	private int player2Stack;
	private int pot;

	// the game status
	public enum Status { PREFLOP, FLOP, TURN, RIVER, ROUND_OVER, HAS_WINNER }
	private Status status;
	private Player winner;

	/** Create a new State */
	/*package*/ State() {
		// setup permanent board state
		player1Stack = INITIAL_STACK;
		player2Stack = INITIAL_STACK;
		pot = 0;
		winner = null;

		setupRound(Player.FIRST);
	}

	/** Sets up a round with [dealer] */
	private void setupRound(Player dealer) {
		deck = new Deck();
		this.dealer = dealer;
		dealHands();
		board = new ArrayList<>();
		status = Status.PREFLOP;
		next = dealer.opponent();
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
		int stack = getStack(next);
		if (m.TYPE.equals(Type.BID)) {
			int amount = Math.min(stack, m.AMOUNT);

			pot += amount;
			// remove gold from current players stack
			if (next.equals(Player.FIRST)) {
				player1Stack -= amount;
			} else {
				player2Stack -= amount;
			}

		} else if (m.TYPE.equals(Type.FOLD)) {
			// give money to person who didn't fold
			if (next.opponent().equals(Player.FIRST)) {
				player1Stack += pot;
			} else {
				player2Stack += pot;
			}
			pot = 0;

			status = Status.ROUND_OVER;
		}

		if (status.equals(Status.ROUND_OVER)) {
			// check winner
			if (player1Stack == 0) {
				status = Status.HAS_WINNER;
				winner = Player.SECOND;
			} else if (player2Stack == 0) {
				status = Status.HAS_WINNER;
				winner = Player.FIRST;
			} else {
				setupRound(dealer.opponent());
			}
		}
	}

	/** returns a Hand for [p] that is not backed by the state */
	public List<Card> getHand(Player p) {
		List<Card> hand = p == Player.FIRST ? player1Hand : player2Hand;
		return Collections.unmodifiableList(hand);
	}

	/** return the bid for [p] */
	public int getPot() {
		return pot;
	}

	/** Get the stack size for [p] */
	public int getStack(Player p) {
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

	// static

	// the amount of money that players start with
	final static int INITIAL_STACK = 1000;
}
