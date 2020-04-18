import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.Timer;
import javax.swing.*;
public class TetrisPanel extends JFrame{

	protected GameArea game;
	protected ControlArea control;
	protected Timer downMoveTimer;
	private RankingList rank;
	private int delay;
	private boolean isPaused;
	private String username;

	TetrisPanel(String name) {
		super();
		this.username=name;
		delay=1000;

		game=new GameArea();
		game.setBorder(BorderFactory.createEtchedBorder(javax.swing.border.EtchedBorder.RAISED));

		control =new ControlArea();
		rank=new RankingList();
		isPaused=false;
		this.setSize(700, 875);
		Container container = getContentPane();
        container.add(control, BorderLayout.EAST);
        container.add(game, BorderLayout.CENTER);

        downMoveTimer= new Timer(delay, new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ae) {
				if(!game.moveSquare(3))
					try {
						updateData();
					} catch (IOException e) {
						e.printStackTrace();
					}
			}
        		
        });
        addListener(); 
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
	}

	protected void resetGame() throws IOException {
		isPaused = false;
		game.resetGame();
		control.resetData();
		updateData();
	}
	

	protected int updateData() throws IOException {
		int rr = game.cleanRow();
		control.updateData(rr, game.creatNextSquare());
		delay = (int) (1000*Math.pow(0.8, control.getLevel()-1));
		if(game.getNextSquare())
			downMoveTimer.setDelay(delay);
		else stopGame();

		return rr;
	}

	private void addListener() {
		control.addStartListener(
		new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent me) {
				try {
					restartGame();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}

		}, 
		new KeyListener() {
			@Override
			public void keyPressed(KeyEvent ke) {
				if(ke.getKeyCode()==KeyEvent.VK_UP)
					game.moveSquare(0);
				else if(ke.getKeyCode()==KeyEvent.VK_DOWN)
					game.moveSquare(3);
				else if(ke.getKeyCode()==KeyEvent.VK_LEFT)
					game.moveSquare(1);
				else if(ke.getKeyCode()==KeyEvent.VK_RIGHT)
					game.moveSquare(2);
			}

			public void keyReleased(KeyEvent arg0) {}
			public void keyTyped(KeyEvent arg0) {}
		});
		control.addPauseListener(
		new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent me) {
				pauseGame();
			}
		});
		
		control.addRankListener(
		new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent me) {
				try {
					rank.load();
					pauseGame();
				} catch (IOException e) {
					e.printStackTrace();
				}
				rank.setVisible(true);
			}
		});
	}
	
	protected void pauseGame() {
		isPaused = true;
		downMoveTimer.stop();		
	}

	protected void restartGame() throws IOException {
		if(!isPaused)
			resetGame();
		else
			isPaused = false;
		downMoveTimer.start();
	}

	protected void stopGame() throws IOException {
		rank.save(username,control.score);
		JOptionPane.showMessageDialog(null,"Level: "+control.level+"   "+"Score: "+control.score,"Tetris",JOptionPane.PLAIN_MESSAGE);
	}
}