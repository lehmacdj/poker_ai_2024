import model.*;

public class TUI {
	public static void main(String[] args) {
		Game g = new Game();
		BoardPrinter p = new BoardPrinter();
		Controller ai = new PokerAI(Player.AI);
		Controller human = new HumanController(Player.HUMAN);
		g.addListener(p);
		g.addListener(ai);
		g.addListener(human);
		g.start();
	}
}
