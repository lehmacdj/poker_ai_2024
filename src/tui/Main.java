package tui;

import model.*;
import controller.*;

public class Main {
	public static void main(String[] args) {
		Game g = new Game();
		GamePrinter p = new GamePrinter();
		Controller human = new HumanController(Player.SECOND);
		Controller ai = new PokerAI(Player.FIRST);
		g.addListener(p);
		g.addListener(human);
		g.addListener(ai);
		g.start();
	}
}
