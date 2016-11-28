import model.*;

public class TUI {
	public static void main(String[] args) {
		Game g = new Game();
		BoardPrinter p = new BoardPrinter();
		Controller human = new HumanController(Player.FIRST);
		Controller ai = new PokerAI(Player.SECOND);
		g.addListener(p);
		g.addListener(ai);
		g.addListener(human);
		g.start();
	}
}
