package controller;

import java.util.Scanner;

import model.Move;
import model.Player;
import model.State;

public class HumanController extends Controller {
	public HumanController(Player p) {
		super(p);
	}

	@Override
	public Move nextMove(State s) {
		Move m = readMove();
		while (m == null) {
			System.out.println("Invalid move please try again");
			m = readMove();
		}
		return m;
	}

	/**
	 * Returns the move that the user input. If the move was invalid returns
	 * null instead.
	 */
	public Move readMove() {
		System.out.println("Please enter one of the following commands:");
		System.out.println(" bid <amount>");
		System.out.println(" fold");
		Scanner reader = new Scanner(System.in);
		String command = reader.next();
		Move move = null;
		if (command.equals("bid")) {
			int amount = reader.nextInt();
			move = Move.makeBid(amount);
		} else if (command.equals("fold")) {
			move = Move.makeFold();
		}
		reader.close();
		return move;
	}

}
