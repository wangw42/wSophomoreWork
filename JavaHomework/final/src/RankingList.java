import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JLabel;


public class RankingList extends JFrame{
	private JLabel[][] box;
	private int MAXSIZE = 20;
		
	RankingList(){
		super();
		setLayout(new GridLayout(MAXSIZE, 2));
		this.setSize(700, 875);
		this.setTitle("Ranking List");
		box = new JLabel[MAXSIZE][2];
		
		for(int i=0;i<MAXSIZE;i++) {
			for(int j=0;j<2;j++) {
				box[i][j] = new JLabel("",JLabel.CENTER);
				box[i][j].setBackground(Color.gray);
				box[i][j].setFont(new Font (Font.DIALOG, Font.PLAIN, 18));
				box[i][j].setBorder(BorderFactory.createLineBorder(Color.black));
				add(box[i][j]);
			}
			
		}
		
		box[0][0].setText("Username");
		box[0][1].setText("Score");
		box[0][0].setFont(new Font (Font.DIALOG, Font.BOLD, 18));
		box[0][1].setFont(new Font (Font.DIALOG, Font.BOLD, 18));
	}
	
	void load() throws IOException {
		File file = new File("rankdata.txt");
		if(!file.exists()) {
            file.createNewFile();
    	}
		
		int count = 0;
		int scores[] = new int[MAXSIZE];
		String usernames[]= new String[MAXSIZE];
		FileInputStream fis = new FileInputStream("rankdata.txt");
		BufferedReader br = new BufferedReader(new InputStreamReader(fis,"UTF-8"));
		String line = null;
		while((line = br.readLine()) != null) {
			String[] two = line.split(",",2);
			scores[count] = Integer.parseInt(two[1]);
			usernames[count] = two[0];
			count++;

		}
		fis.close();
		br.close();
		for(int i=0;i<count;i++) {
			for(int j=0;j<count-1-i;j++) {
				if(scores[j+1]>scores[j]) {
					int temp=scores[j+1];
					scores[j+1]=scores[j];
					scores[j]=temp;
					String stemp=usernames[j+1];
					usernames[j+1]=usernames[j];
					usernames[j]=stemp;				
				}
			}
		}
		for(int i=0;i<count;i++) {
			box[i+1][0].setText(usernames[i]);
			box[i+1][1].setText(scores[i]+"");
		}
	
	}
	
	void save(String username,int score) throws IOException {
		File file=new File("rankdata.txt");
		if(!file.exists()) {
            file.createNewFile();
    	}
		FileOutputStream os = new FileOutputStream("rankdata.txt",true);//append
		PrintWriter pw=new PrintWriter(new BufferedWriter(new OutputStreamWriter(os,"UTF-8")));
		pw.println(username+","+score);
		pw.close();
		os.close();	
	}

}
