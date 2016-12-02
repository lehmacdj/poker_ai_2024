package tui;

import model.*;
import controller.*;

public class Main {
	public static void main(String[] args) {
		Game g = new Game();
		GamePrinter p = new GamePrinter();
		Controller human = new HumanController(Player.FIRST);
		Controller human2 = new HumanController(Player.SECOND);
		g.addListener(p);
		g.addListener(human2);
		g.addListener(human);
		g.start();
	}
}
