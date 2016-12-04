package tui;

import java.util.Optional;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import model.Move;
import model.Player;
import model.State;

public class HumanController extends Controller {
	Scanner in;

	public HumanController(Player p) {
		super(p);
		in = new  Scanner(System.in);
	}

	@Override
	public Move nextMove(State s) {
		// privacy during dual human games
		System.out.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		System.out.println("Press enter to continue");
		in.nextLine();
		printBoard(s);
		printSelf(s);
		printOpponent(s);
		Move m = readMove(s);
		while (m == null) {
			System.out.println("Invalid move please try again");
			m = readMove(s);
		}
		return m;
	}

	/**
	 * Returns the move that the user input. If the move was invalid returns
	 * null instead.
	 */
	public Move readMove(State s) {
		System.out.println("Please enter one of the following commands:");
		System.out.println(" call");
		System.out.println(" raise <amount>");
		System.out.println(" fold");
		System.out.println(" all-in");
		String command = in.next();
		Move move = null;
		if (command.equals("call")) {
			move = Move.makeBid(s.getAmountToCall());
		} else if (command.equals("raise")) {
			double amount = in.nextDouble();
			if (amount < s.getMinimumRaise()) {
				System.out.println("Error: the minimum raise is " + s.getMinimumRaise());
				return null;
			} else if (amount > s.getStack(player.opponent())) {
				System.out.println("Error: can't raise more than you opponent has money");
				return null;
			}
			move = Move.makeBid(amount + s.getAmountToCall());
		} else if (command.equals("fold")) {
			move = Move.makeFold();
		} else if (command.equals("all-in")) {
			if (s.getStack(player) - s.getAmountToCall() > s.getStack(player.opponent())) {
				System.out.println("Error: can't raise more money than your opponent has");
				return null;
			}
			move = Move.makeBid(s.getStack(player));
		} else if (command.equals("quit") || command.equals(":q")) {
			System.out.println("Ending game...");
			System.exit(1);
		}
		return move;
	}

	public void printBoard(State s) {
		System.out.printf("(%.1f): %s\n",
			s.getPot(),
			Stream.concat(
				s.getBoard().stream()
					.map(e -> Optional.of(e)),
				Stream.generate(() -> Optional.empty()))
				.limit(5)
				.map(e -> e
					.map(v -> v.toString())
					.orElse("-"))
				.collect(Collectors.joining(", "))
		);
	}

	public void printSelf(State s) {
		System.out.printf("You (%.1f): %s\n",
			s.getStack(player),
			s.getHand(player).stream()
				.map(o -> o.toString())
				.collect(Collectors.joining(", "))
		);
	}

	public void printOpponent(State s) {
		System.out.printf("Opponent (%.1f)\n", s.getStack(player.opponent()));
	}

	@Override
	public void finalize() {
		in.close();
	}
}
