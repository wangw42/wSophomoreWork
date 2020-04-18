import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class GameArea extends JPanel {

	private JLabel[][] grid;
	private int row;
	private int col;
	private Square movingSquare;
	private LinkedList<Square> nextSquare;

	GameArea() {
		super();
		setLayout(new GridLayout(15, 10));
		row=15;
		col=10;
		grid = new JLabel[row][col];

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				grid[i][j] = new JLabel();
				grid[i][j].setPreferredSize(new Dimension(40, 40));
				grid[i][j].setBackground(Color.gray);
				add(grid[i][j]);
			}

			nextSquare = new LinkedList<Square>();
		}
	}

	public int cleanRow() {

		movingSquare = null;
		int count = 0;
		for (int i = grid.length - 1; i >= 0; i--) {
			int j;
			for (j = 0; j < grid[0].length; j++)
				if (!grid[i][j].isOpaque())
					break;

			if (j == grid[0].length) {
				count++;
				for (int k = i; k > 0; k--)
					for (int l = 0; l < grid[0].length; l++) {
						grid[k][l].setOpaque(grid[k - 1][l].isOpaque());
						grid[k - 1][l].setBorder(BorderFactory.createEmptyBorder());
						if (!grid[k][l].isOpaque())
							grid[k][l].setBorder(BorderFactory.createEmptyBorder());
						else
							grid[k][l].setBorder(BorderFactory.createTitledBorder(""));

					}

				i++;
			}
		}
		return count;
	}

	public void increaseRow(int n) {
		Random r = new Random();
		for (int i = 0; i < grid.length - n; i++)
			for (int j = 0; j < grid[0].length; j++) {
				grid[i][j].setOpaque(grid[i + n][j].isOpaque());
				if (grid[i][j].isOpaque()) {
					grid[i][j].setBorder(BorderFactory.createTitledBorder(""));
				} else
					grid[i][j].setBorder(BorderFactory.createEmptyBorder());

			}

		for (int i = grid.length - n; i < grid.length; i++)
			for (int j = 0; j < grid[0].length; j++) {
				grid[i][j].setOpaque(r.nextBoolean());
				if (grid[i][j].isOpaque()) {
					grid[i][j].setBorder(BorderFactory.createTitledBorder(""));
				} else
					grid[i][j].setBorder(BorderFactory.createEmptyBorder());

			}
	}

	public Square creatNextSquare() {

		if (nextSquare.isEmpty())
			nextSquare.add(new Square(new Point(0, grid[0].length / 2 - 1)));

		nextSquare.add(new Square(new Point(0, grid[0].length / 2 - 1)));

		return nextSquare.getLast();
	}

	public boolean getNextSquare() {
		return drawSquare(nextSquare.poll());
	}

	synchronized boolean moveSquare(int k) {
		if (movingSquare == null)
			return true;
		switch (k) {
		case 0:
			if (!drawSquare(movingSquare.getChangedSuqare(true, 0, 0)))
				if (!drawSquare(movingSquare.getChangedSuqare(true, 0, -1)))
					if (!drawSquare(movingSquare.getChangedSuqare(true, 0, -2)))
						if (!drawSquare(movingSquare.getChangedSuqare(true, 0, -3)))
							break;
		case 1:
			drawSquare(movingSquare.getChangedSuqare(false, 0, -1));
			break;
		case 2:
			drawSquare(movingSquare.getChangedSuqare(false, 0, 1));
			break;
		case 3:
			return drawSquare(movingSquare.getChangedSuqare(false, 1, 0));
		}
		return true;
	}

	synchronized boolean drawSquare(Square unit) {
		List<Point> topaint = new ArrayList<Point>();

		for (Point n : unit.getPaintLocation())
			topaint.add(n);

		if (movingSquare != null)
			for (Point b : movingSquare.getPaintLocation())
				topaint.remove(b);

		for (Point s : topaint)
			if (s.x < 0 || s.x >= grid.length || s.y < 0 || s.y >= grid[0].length || grid[s.x][s.y].isOpaque())
				return false;

		if (movingSquare != null)
			for (Point s : movingSquare.getPaintLocation()) {
				grid[s.x][s.y].setOpaque(false);
				grid[s.x][s.y].setBorder(BorderFactory.createEmptyBorder());
			}
		movingSquare = unit;

		for (Point s : movingSquare.getPaintLocation()) {
			grid[s.x][s.y].setOpaque(true);
			grid[s.x][s.y].setBackground(unit.color);
			grid[s.x][s.y].setBorder(BorderFactory.createTitledBorder(""));

		}

		this.updateUI();
		return true;
	}

	public void resetGame() {

		for (int i = 0; i < grid.length; i++)
			for (int j = 0; j < grid[0].length; j++) {
				grid[i][j].setOpaque(false);
				grid[i][j].setBorder(BorderFactory.createEmptyBorder());
			}

		movingSquare = null;
		nextSquare.clear();
	}

	public void endGame() {
		movingSquare = null;
	}

}