package tui;

import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import model.*;
import model.State.Status;

public class GamePrinter implements GameListener {
	public void printPlayer(Player p, State s) {
		System.out.printf("%s (%.1f): %s\n",
			p,
			s.getStack(p),
			s.getHand(p).stream()
				.map(o -> o.toString())
				.collect(Collectors.joining(", "))
		);
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

	@Override
	public void gameChanged(Game g) {
		State s = g.getState();
		System.out.println();
		if (s.getStatus().equals(Status.ROUND_OVER)) {
			printBoard(s);
			printPlayer(Player.FIRST, s);
			printPlayer(Player.SECOND, s);
			System.out.println(s.getWinner() + " wins the round.");
			g.startNextRound();
		} else if (s.getStatus().equals(Status.HAS_WINNER)) {
			printBoard(s);
			printPlayer(Player.FIRST, s);
			printPlayer(Player.SECOND, s);
			System.out.println("The winner is " + s.getWinner());
			System.exit(0);
		}
	}
}
