
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.KeyListener;
import java.awt.event.MouseListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class ControlArea extends JPanel{

	private JButton start, pause, rank;
	private JLabel[][] nextSquare;
	private JPanel nextSquarePanel;
	private JLabel s, l;
	
	public int level,score;
	
	ControlArea(){

		score=0;
		level=1;
		start = new JButton("Start");
		pause = new JButton("Pause");
		rank = new JButton("RankingList");
		s = new JLabel("Score: ",JLabel.CENTER);
		l = new JLabel("Level: ",JLabel.CENTER);
		s.setPreferredSize(new Dimension(100,50));
		l.setPreferredSize(new Dimension(100,50));
		nextSquarePanel = new JPanel(new GridLayout(4,4));
		nextSquare = new JLabel[4][4];
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
			{
				nextSquare[i][j] = new JLabel();
				nextSquare[i][j].setPreferredSize(new Dimension(20,20));
				nextSquare[i][j].setBackground(Color.YELLOW);
				nextSquarePanel.add(nextSquare[i][j]);
			}
		
		FlowLayout layout = new FlowLayout();
		layout.setVgap(50);
		this.setLayout(layout);
		
		this.setPreferredSize(new Dimension(100,500));
		this.add(nextSquarePanel);
		this.add(l);
		this.add(s);
		this.add(start);
		this.add(pause);
		this.add(rank);
	}

	public void resetData() {
		score = 0;
		s.setText("Score: "+score);
		level = 1;
		l.setText("Level: "+level);
	}
	

	public void addStartListener(MouseListener m,KeyListener k) {
		start.addMouseListener(m);
		start.addKeyListener(k);
	}
	public void addPauseListener(MouseListener l)
	{
		pause.addMouseListener(l);
	}
	
	public void addRankListener(MouseListener l) {
		rank.addMouseListener(l);
	}
	

	public void updateData(int c,Square p) {
		score += c*100;
		level = score/1000 + 1;
		s.setText("Score: "+score);
		l.setText("Level: "+level);
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++) {
				nextSquare[i][j].setOpaque(false);
				nextSquare[i][j].setBorder(BorderFactory.createEmptyBorder());
			}

		for(int i=0;i<p.getShape().length;i++){
			nextSquare[p.getShape()[i].x][p.getShape()[i].y].setOpaque(true);
			nextSquare[p.getShape()[i].x][p.getShape()[i].y].setBackground(p.color);
			nextSquare[p.getShape()[i].x][p.getShape()[i].y].setBorder(BorderFactory.createTitledBorder(""));
		}

		nextSquarePanel.updateUI();
	}
	
	public int getLevel()
	{
		return level;
	}
	
	public int getScore() { return score; }
}
