package controller;

import java.util.Scanner;

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
			}
			move = Move.makeBid(amount + s.getAmountToCall());
		} else if (command.equals("fold")) {
			move = Move.makeFold();
		} else if (command.equals("all-in")) {
			move = Move.makeBid(s.getStack(player));
		} else if (command.equals("quit") || command.equals(":q")) {
			System.out.println("Ending game...");
			System.exit(1);
		}
		return move;
	}

	@Override
	public void finalize() {
		in.close();
	}
}
