import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.LinkedList;

import javax.swing.*;


public class TwoPlayerTetrisPanel extends TetrisPanel {

	private Thread sendThread,receiveThread,sendDataThread,receiveDataThread;
	private Timer receiveTimer,receiveDataTimer;
	private ServerSocket s,sd;
	private Socket send,receive,sendData,receiveData;
	private int sendPort,receivePort;
	private String sendIP;
	OutputStream out;
	private int othScore;
	private int loseCnt = 0;


	TwoPlayerTetrisPanel(String username, String ip, int sp, int rp) {
		super(username);
		sendIP = ip;
		sendPort = sp;
		receivePort = rp;
		final JLabel othScore = new JLabel("Opponent: 0", JLabel.CENTER);
		new LinkedList<Integer>();

		receiveThread = new Thread(){
			public void run() {
				try {
					s = new ServerSocket(receivePort);
					receive = s.accept();
					InputStream in = receive.getInputStream();
					DataInputStream is = new DataInputStream(in);

					receiveTimer = new Timer(0, new ActionListener(){
						@Override
						public void actionPerformed(ActionEvent e) {
							try {
								int score = is.readInt();
								TwoPlayerTetrisPanel.this.othScore = score;
								othScore.setText("Opponent: " + score);
								control.add(othScore);
							} catch (Exception e1) {
								receiveTimer.stop();

								if (TwoPlayerTetrisPanel.this.othScore > control.getScore()) {
									stopGame();
								} else {
									winGame();
								}

							}
						}
					});
					receiveTimer.start();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}

		};

		sendThread = new Thread(){
			public void run() {
				while(true){
					try {
						send = new Socket(sendIP,sendPort);

						OutputStream out = send.getOutputStream();
						DataOutputStream os = new DataOutputStream(out);
						while(true) {
							try {
								int score = control.getScore();
								os.writeInt(score);
								os.flush();
							} catch (Exception e) {
								//winGame();
								break;
							}
						}
						break;
					} catch (UnknownHostException e) {
						e.printStackTrace();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}

		};

		receiveDataThread = new Thread(){
			public void run() {
				try {
					sd = new ServerSocket(receivePort+1);
					receiveData = sd.accept();
					InputStream in = receiveData.getInputStream();
					receiveDataTimer = new Timer(10, new ActionListener(){
						@Override
						public void actionPerformed(ActionEvent e) {
							try {
								if(in.available()!=0)
									game.increaseRow(in.read());
							} catch (IOException e1) {
								receiveDataTimer.stop();
							}
						}
					});
					receiveDataTimer.start();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}

		};

		sendDataThread = new Thread(){
			public void run() {
				while(true)
				{
					try {
						sendData = new Socket(sendIP,sendPort+1);
						out = sendData.getOutputStream();
						break;
					} catch (UnknownHostException e) {
						e.printStackTrace();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}

		};

		resetGame();
	}

	@Override
	protected int updateData() {
		int ret=0;
		try {
			int i = super.updateData();
			if (i > 1)
				try {
					out.write(i - 1);
					out.flush();
				} catch (IOException e) {
					e.printStackTrace();
				}
			ret = i;
			return i;
		}catch (IOException e){
			e.printStackTrace();
		}

		return ret;
	}
	@Override
	protected void resetGame() {
		try {
			super.resetGame();
			this.sendThread.start();
			this.receiveThread.start();
			this.sendDataThread.start();
			this.receiveDataThread.start();
			downMoveTimer.start();
		}catch (IOException e){
			e.printStackTrace();
		}
	}
	@Override
	protected void restartGame() {}
	@Override
	protected void pauseGame() {}

	@Override
	protected void stopGame(){
		if(loseCnt==0 && othScore > control.getScore()) {
			JOptionPane.showMessageDialog(null, "You Lose", "Tetris", JOptionPane.ERROR_MESSAGE);
			loseCnt++;
		}
		receiveThread.interrupt();
		sendThread.interrupt();
		try {
			send.close();
			receive.close();
			s.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	protected void winGame() {
		JOptionPane.showMessageDialog(null, "You win, score:"+control.score, "Tetris", JOptionPane.INFORMATION_MESSAGE);
		game.endGame();
		sendThread.interrupt();
		receiveThread.interrupt();
		try {
			send.close();
			receive.close();
			s.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}