package tui;

import model.*;
import controller.*;

public class Main {
	public static void main(String[] args) {
		Game g = new Game();
		GamePrinter p = new GamePrinter();
		Controller human = new HumanController(Player.FIRST);
		Controller ai = new PokerAI(Player.SECOND);
		g.addListener(p);
		g.addListener(human);
		g.addListener(ai);
		g.start();
	}
}
