import java.io.IOException;

import javax.swing.JOptionPane;

public class Main {

	private static void game() {

				String name = (String) JOptionPane.showInputDialog(null, "Name");
				TetrisPanel player = new TetrisPanel(name);
				player.setVisible(true);
	}

	private static void twoPlayerGame() throws IOException {
				String opponent = (String) JOptionPane.showInputDialog(null, "IP(default:localhost)");
				TwoPlayerTetrisPanel player2;

				String name1 = "player1";
				String name2 = "player2";
				if (opponent.length() > 0)
					player2 = new TwoPlayerTetrisPanel(name2, opponent, 4000, 5000);
				else
					player2 = new TwoPlayerTetrisPanel(name2,"localhost", 4000, 5000);

				TwoPlayerTetrisPanel player1 = new TwoPlayerTetrisPanel(name1,"localhost", 5000, 4000);

				player1.setVisible(true);
				player2.setVisible(true);
	}	
	
	public static void main(String[] args) throws IOException {
				Object[] options = { "1 Player", "2 Players" };
				int op = JOptionPane.showOptionDialog(null, "Please select mode: ", "Tetris", JOptionPane.YES_NO_OPTION,
						JOptionPane.QUESTION_MESSAGE, null, options, options[0]);
				if (op == JOptionPane.YES_OPTION)
					game();
				else if (op == JOptionPane.NO_OPTION)
					twoPlayerGame();
	}
}
