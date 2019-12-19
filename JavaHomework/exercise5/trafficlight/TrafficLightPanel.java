
package trafficlight;

import java.awt.*;
import javax.swing.*;
public class TrafficLightPanel extends JPanel {

    private int currentState = 0;
    private int X = 50, Y = 10, WIDTH = 50, HEIGHT = 130;
    private int X_OFFSET = 10, Y_OFFSET = 10;


    public void TrafficLightPanel() {
        setPreferredSize(new Dimension(150, 230));
        setLayout(new BorderLayout());
    }

    public void paintComponent(Graphics page) {
        super.paintComponent(page);
        int status = currentState ;

        setBackground(Color.white);
        page.setColor(Color.BLACK);
        page.drawRect(X, Y, WIDTH, HEIGHT);

        switch (status) {
            case 0:
                page.setColor(Color.BLACK);
                page.drawOval((X+X_OFFSET),(Y+Y_OFFSET), 30, 30);
                page.setColor(Color.red);
                page.fillOval((X+X_OFFSET),(Y+Y_OFFSET), 30, 30);

                page.setColor(Color.BLACK);
                page.drawOval((X+X_OFFSET),60 , 30, 30);
                page.setColor(Color.black);
                page.drawOval((X+X_OFFSET),100, 30, 30);

                break;
            case 1:
                page.setColor(Color.black);
                page.drawOval((X+X_OFFSET),20, 30, 30);

                page.setColor(Color.black);
                page.drawOval((X+X_OFFSET),60 , 30, 30);
                page.setColor(Color.yellow);
                page.fillOval((X+X_OFFSET),60 , 30, 30);

                page.setColor(Color.black);
                page.drawOval((X+X_OFFSET),100, 30, 30);
                break;
            case 2 :
                page.setColor(Color.black);
                page.drawOval((X+X_OFFSET),(Y+Y_OFFSET), 30, 30);
                page.setColor(Color.black);
                page.drawOval((X+X_OFFSET),60 , 30, 30);

                page.setColor(Color.black);
                page.drawOval((X+X_OFFSET),100, 30, 30);
                page.setColor(Color.green);
                page.fillOval((X+X_OFFSET),100, 30, 30);
                break;

        }

    }

    public void change(int status ) {
        currentState = status ;
        repaint();
    }

}
