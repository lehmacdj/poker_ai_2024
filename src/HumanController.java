import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

import model.Move;
import model.Player;
import model.Replace;
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
		System.out.println(" 1) replace <card-id-list>");
		System.out.println(" 2) bid <amount>");
		Scanner reader = new Scanner(System.in);
		String command = reader.next();
		Move move = null;
		if (command.equals("replace")) {
			move = new Replace(Arrays.asList(new int[]{0, 1}));
		} else if (command.equals("bid")) {
		}
		reader.close();
		return move;
	}
}
