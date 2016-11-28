import model.*;

public class HumanController extends Controller {
	public HumanController(Player p) {
		super(p);
	}

	@Override
	public Move nextMove(State s) {
		Move m = readMove();
		while (m == null) {
			m = readMove();
		}
		return m;
	}

	public Move readMove() {
		return null;
	}
}
